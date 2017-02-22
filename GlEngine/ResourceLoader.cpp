#include "stdafx.h"
#include "ResourceLoader.h"

#include "Engine.h"
#include "ServiceProvider.h"
#include "ILogger.h"
#include "Task.h"

namespace GlEngine
{
    ResourceLoader::ResourceLoader()
    {
    }
    ResourceLoader::~ResourceLoader()
    {
    }

    bool ResourceLoader::Initialize()
    {
        assert(!isInitialized);
        isInitialized = true;
        for (size_t q = 0; q < THREAD_POOL_SIZE; q++)
        {
            auto loop = new GameLoop {
                [&]() { return this->initLoop(); },
                [&](float delta) { this->loop(delta); },
                [&]() { this->shutdownLoop(); },
                15
            };
            thread_pool.push_back(loop);
            loop->RunLoop();
        }
        return true;
    }
    void ResourceLoader::Shutdown()
    {
        if (!isInitialized || isShuttingDown) return;
        isShuttingDown = true;

        cancelInitializeTasks();
        waitForShutdown();

        for (size_t q = 0; q < THREAD_POOL_SIZE; q++)
        {
            auto loop = thread_pool[q];
            loop->StopLoop(true);
        }
        for (size_t q = 0; q < THREAD_POOL_SIZE; q++)
        {
            auto loop = thread_pool[q];
            loop->Join();
            delete loop;
        }
        thread_pool.clear();

        isInitialized = false;
        isShuttingDown = false;
    }

    std::string ResourceLoader::name()
    {
        return "ResourceLoader";
    }

    void ResourceLoader::cancelInitializeTasks()
    {
        ScopedLock _lock(_mutex);
        for (size_t q = 0; q < task_queue.size(); q++)
        {
            auto &task = *task_queue[q];
            if (task.state == TaskState::Working || task.state == TaskState::ThrowAway) continue;
            switch (task.type)
            {
            case TaskType::Initialize:
                task_queue.erase(task_queue.begin() + q--);
                delete &task;
                break;

            case TaskType::InitializeGraphics:
                task.type = TaskType::Shutdown;
                break;
            }
        }
        for (size_t q = 0; q < complete_resources.size(); q++)
        {
            auto c = complete_resources[q];
            if (c->needsGraphics()) queueTask(TaskType::ShutdownGraphics, c);
            queueTask(TaskType::Shutdown, c);
        }
        complete_resources.clear();
    }
    void ResourceLoader::waitForShutdown()
    {
        while (true)
        {
            {
                ScopedLock _lock(_mutex);
                if (task_queue.size() == 0) break;
            }
            std::this_thread::sleep_for(15ms);
        }
    }

    void ResourceLoader::QueueInitialize(IAsyncInitializable *c, bool reentrant)
    {
        assert(c != nullptr);

        ScopedLock _lock(_mutex);

        auto find_complete = std::find(complete_resources.begin(), complete_resources.end(), c);
        if (!reentrant) assert(find_complete == complete_resources.end());
        if (find_complete != complete_resources.end()) complete_resources.erase(find_complete);
        
        for (size_t q = 0; q < task_queue.size(); q++)
        {
            auto &task = *task_queue[q];
            if (&task.component() != c) continue;

            if (task.state != TaskState::ThrowAway) assert(reentrant);
            if (task.state == TaskState::Unassigned)
            {
                task_queue.erase(task_queue.begin() + q--);
                delete &task;
            }
            else task.state = TaskState::ThrowAway;
        }

        queueTask(TaskType::Initialize, c);
    }
    void ResourceLoader::QueueShutdown(IAsyncInitializable *c)
    {
        assert(c != nullptr);

        ScopedLock _lock(_mutex);

        for (size_t q = 0; q < task_queue.size(); q++)
        {
            auto &task = *task_queue[q];
            if (&task.component() != c) continue;
            assert(task.state == TaskState::ThrowAway);
        }

        auto find_complete = std::find(complete_resources.begin(), complete_resources.end(), c);
        assert(find_complete != complete_resources.end());
        complete_resources.erase(find_complete);

        if (c->needsGraphics()) queueTask(TaskType::ShutdownGraphics, c);
        else queueTask(TaskType::Shutdown, c);
    }
    void ResourceLoader::queueTask(TaskType type, IAsyncInitializable *c)
    {
        assert(c != nullptr);

        ScopedLock _lock(_mutex);
        task_queue.push_back(new Task(type, c));
    }

    bool ResourceLoader::TickGraphics()
    {
        bool worked = true;
        auto logger = Engine::GetInstance().GetServiceProvider().GetService<ILogger>();

        for (;;)
        {
            auto task = nextGraphicsTask();
            if (task == nullptr) break;

            IAsyncInitializable &c = task->component();

            switch (task->type)
            {
            case TaskType::InitializeGraphics:
                logger->Log(LogType::Info, "Asynchronous resource loader initializing graphics for %s...", c.name().c_str());
                if (!c.InitializeGraphics())
                {
                    logger->Log(LogType::ErrorC, "Asynchronous resource loader failed to initialize graphics for %s.", c.name().c_str());
                    worked = false;

                    ScopedLock _lock(_mutex);
                    if (task->state == TaskState::ThrowAway) removeTask(task);
                    else
                    {
                        task->type = TaskType::Shutdown;
                        task->state = TaskState::Unassigned;
                    }
                }
                else
                {
                    logger->Log(LogType::Info, "Asynchronous resource loader initialized graphics for %s.", c.name().c_str());
                    ScopedLock _lock(_mutex);
                    if (task->state == TaskState::ThrowAway) removeTask(task);
                    else if (isShuttingDown)
                    {
                        task->state = TaskState::Unassigned;
                        task->type = TaskType::ShutdownGraphics;
                    }
                    else
                    {
                        removeTask(task);
                        complete_resources.push_back(&c);
                    }
                }
                break;

            case TaskType::ShutdownGraphics:
                logger->Log(LogType::Info, "Asynchronous resource loader shutting down graphics for %s...", c.name().c_str());
                c.ShutdownGraphics();
                {
                    logger->Log(LogType::Info, "Asynchronous resource loader shut down graphics for %s.", c.name().c_str());
                    ScopedLock _lock(_mutex);
                    if (task->state == TaskState::ThrowAway) removeTask(task);
                    else
                    {
                        task->type = TaskType::Shutdown;
                        task->state = TaskState::Unassigned;
                    }
                }
                break;

            default:
                assert(false);
            }
            
        }
        return worked;
    }
    void ResourceLoader::ShutdownGraphics()
    {
        cancelInitializeTasks();
        TickGraphics();
    }

    bool ResourceLoader::initLoop()
    {
        ScopedLock _lock(_mutex);
        this_thread_name() = "rscld"s + std::to_string(++worker_count);
        this_thread_type() = ThreadType::ResourceLoader;

        auto logger = Engine::GetInstance().GetServiceProvider().GetService<ILogger>();
        logger->Log(LogType::Info, "Beginning resource loader worker...");
        return true;
    }
    void ResourceLoader::loop(float)
    {
        Task *task = nextWorkerTask();
        if (task == nullptr) return;
        IAsyncInitializable &c = task->component();

        auto logger = Engine::GetInstance().GetServiceProvider().GetService<ILogger>();

        switch (task->type)
        {
        case TaskType::Initialize:
            logger->Log(LogType::Info, "Asynchronous resource loader initializing %s...", c.name().c_str());
            if (!c.InitializeAsync())
            {
                logger->Log(LogType::ErrorC, "Asynchronous resource loader failed to initialize %s.", c.name().c_str());
                removeTask(task);
            }
            else
            {
                logger->Log(LogType::Info, "Asynchronous resource loader initialized %s.", c.name().c_str());
                ScopedLock _lock(_mutex);
                if (task->state == TaskState::ThrowAway || !c.needsGraphics()) removeTask(task);
                else
                {
                    task->type = TaskType::InitializeGraphics;
                    task->state = TaskState::Unassigned;
                }
            }
            break;

        case TaskType::Shutdown:
            logger->Log(LogType::Info, "Asynchronous resource loader shutting down %s...", c.name().c_str());
            c.ShutdownAsync();
            logger->Log(LogType::Info, "Asynchronous resource loader shut down %s.", c.name().c_str());
            removeTask(task);
            break;

        default:
            assert(false);
        }
    }
    Task *ResourceLoader::nextWorkerTask()
    {
        ScopedLock _lock(_mutex);

        Task *task = nullptr;
        auto count = task_queue.size();
        for (int q = count; q > 0; q--)
        {
            task = task_queue.at(0);
            task_queue.pop_front();

            if (task->state == TaskState::Unassigned && (task->type == TaskType::Initialize || task->type == TaskType::Shutdown)) break;
            task_queue.push_back(task);
            task = nullptr;
        }
        if (task != nullptr)
        {
            task->state = TaskState::Working;
            task_queue.push_back(task);
        }
        return task;
    }
    void ResourceLoader::shutdownLoop()
    {
        auto logger = Engine::GetInstance().GetServiceProvider().GetService<ILogger>();
        logger->Log(LogType::Info, "~Terminating resource loader worker...");
    }

    Task *ResourceLoader::nextGraphicsTask()
    {
        ScopedLock _lock(_mutex);

        Task *task = nullptr;
        auto count = task_queue.size();
        for (int q = count; q > 0; q--)
        {
            task = task_queue.at(0);
            task_queue.pop_front();

            if (task->state == TaskState::Unassigned && (task->type == TaskType::InitializeGraphics || task->type == TaskType::ShutdownGraphics)) break;
            task_queue.push_back(task);
            task = nullptr;
        }
        if (task != nullptr)
        {
            task->state = TaskState::Working;
            task_queue.push_back(task);
        }
        return task;
    }

    void ResourceLoader::removeTask(Task *task)
    {
        ScopedLock _lock(_mutex);
        collection_remove(task_queue, task);
    }
}
