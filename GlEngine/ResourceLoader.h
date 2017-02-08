#pragma once

#include "IService.h"
#include "IComponent.h"
#include "IGraphicsComponent.h"
#include "TaskType.h"
#include <queue>
#include "GameLoop.h"

namespace GlEngine
{
    class Task;

    class ENGINE_SHARED ResourceLoader : public IService, public IComponent
    {
    public:
        ResourceLoader();
        ~ResourceLoader();

        static const size_t THREAD_POOL_SIZE = 4;

        bool Initialize() override;
        void Shutdown() override;

        std::string name() override;

        void QueueInitialize(IComponent *c, bool reentrant = false);
        void QueueShutdown(IComponent *c);

        bool TickGraphics();
        void ShutdownGraphics();

    private:
        rt_mutex _mutex;
        std::vector<GameLoop*> thread_pool;
        int worker_count = 0;
        std::deque<Task*> task_queue;
        std::vector<IComponent*> complete_resources;

        void queueTask(TaskType type, IComponent *c);

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
