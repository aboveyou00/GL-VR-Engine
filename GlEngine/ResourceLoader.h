#pragma once

#include "IService.h"
#include "IComponent.h"
#include "IGraphicsComponent.h"
#include <queue>
#include "GameLoop.h"

namespace GlEngine
{
    class ENGINE_SHARED ResourceLoader : public IService, public IComponent
    {
    public:
        ResourceLoader();
        ~ResourceLoader();

        bool Initialize() override;
        void Shutdown() override;

        const char *name() override;

        void QueueResource(IComponent *c);
        void QueueShutdown(IComponent *c);
        bool InitializeResourceGraphics();
        void ShutdownResourceGraphics();

    private:
        rt_mutex _mutex;
        std::deque<IComponent*> c_queue, complete_resources, c_shutdown_queue;
        std::deque<IGraphicsComponent*> graphics_queue, graphics_shutdown_queue;
        GameLoop _gameLoop;
        bool initLoop();
        void loop(float delta);
        void shutdownLoop();

        void clearShutdownGraphicsQueue();
        void clearShutdownQueue();
    };
}
