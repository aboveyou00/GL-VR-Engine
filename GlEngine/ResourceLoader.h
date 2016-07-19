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
        bool InitializeResourceGraphics();
        void ShutdownResourceGraphics();

    private:
        rt_mutex _mutex;
        std::deque<IComponent*> c_queue;
        std::deque<IGraphicsComponent*> graphics_queue;
        std::vector<IComponent*> complete_resources;
        GameLoop _gameLoop;
        void loop(float delta);
    };
}
