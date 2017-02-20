#pragma once

#include "IService.h"
#include "IInitializable.h"
#include "TaskType.h"
#include <queue>
#include "GameLoop.h"

namespace GlEngine
{
    class Task;

    class ENGINE_SHARED ResourceLoader : public IService, public IInitializable
    {
    public:
        ResourceLoader();
        ~ResourceLoader();

        static const size_t THREAD_POOL_SIZE = 4;

        bool Initialize() override;
        void Shutdown() override;

        std::string name() override;

        void QueueInitialize(IAsyncInitializable *c, bool reentrant = false);
        void QueueShutdown(IAsyncInitializable *c);

        bool TickGraphics();
        void ShutdownGraphics();

    private:
        rt_mutex _mutex;
        std::vector<GameLoop*> thread_pool;
        int worker_count = 0;
        std::deque<Task*> task_queue;
        std::vector<IAsyncInitializable*> complete_resources;

        void queueTask(TaskType type, IAsyncInitializable *c);

        bool isInitialized = false, isShuttingDown = false;
        void cancelInitializeTasks();
        void waitForShutdown();

        bool initLoop();
        void loop(float delta);
        Task *nextWorkerTask();
        void shutdownLoop();

        Task *nextGraphicsTask();

        void removeTask(Task *task);
    };
}
