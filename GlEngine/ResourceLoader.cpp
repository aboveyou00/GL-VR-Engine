#include "stdafx.h"
#include "ResourceLoader.h"

#include "Engine.h"
#include "ServiceProvider.h"
#include "ILogger.h"

namespace GlEngine
{
    ResourceLoader::ResourceLoader()
        : _gameLoop([&](float delta) { this->loop(delta); }, 15)
    {
    }
    ResourceLoader::~ResourceLoader()
    {
    }

    bool ResourceLoader::Initialize()
    {
        _gameLoop.RunLoop();
        return true;
    }
    void ResourceLoader::Shutdown()
    {
        _gameLoop.StopLoop();
        for (size_t q = 0; q < complete_resources.size(); q++)
            complete_resources[q]->Shutdown();
        complete_resources.clear();
    }

    const char *ResourceLoader::name()
    {
        return "ResourceLoader";
    }

    void ResourceLoader::QueueResource(IComponent *c)
    {
        ScopedLock _lock(_mutex);
        c_queue.push_back(c);
    }
    bool ResourceLoader::InitializeResourceGraphics()
    {
        bool worked = true;
        for (;;)
        {
            IGraphicsComponent *c;
            {
                ScopedLock _lock(_mutex);
                if (graphics_queue.size() == 0) break;
                c = graphics_queue.at(0);
                graphics_queue.pop_front();
            }
            if (!c->InitializeGraphics())
            {
                auto logger = Engine::GetInstance().GetServiceProvider().GetService<ILogger>();
                logger->Log(LogType::ErrorC, "Asynchronous resource loader failed to initialize %s (IGraphicsComponent)", c->name());
                worked = false;
                continue;
            }
            {
                ScopedLock _lock(_mutex);
                complete_resources.push_back(c);
            }
        }
        return worked;
    }
    void ResourceLoader::ShutdownResourceGraphics()
    {
        ScopedLock _lock(_mutex);
        for (size_t q = 0; q < complete_resources.size(); q++)
        {
            IComponent *c;
            IGraphicsComponent *g;
            c = complete_resources.at(q);
            if ((g = dynamic_cast<IGraphicsComponent*>(c)) != nullptr) g->ShutdownGraphics();
        }
    }

    void ResourceLoader::loop(float)
    {
        IComponent *c;
        for (;;)
        {
            {
                ScopedLock _lock(_mutex);
                if (c_queue.size() == 0) break;
                c = c_queue.at(0);
                c_queue.pop_front();
            }
            if (!c->Initialize())
            {
                auto logger = Engine::GetInstance().GetServiceProvider().GetService<ILogger>();
                logger->Log(LogType::ErrorC, "Asynchronous resource loader failed to initialize %s (IComponent)", c);
                continue;
            }
            {
                ScopedLock _lock(_mutex);
                IGraphicsComponent *g = dynamic_cast<IGraphicsComponent*>(c);
                if (g != nullptr) graphics_queue.push_back(g);
                else complete_resources.push_back(c);
            }
        }
    }
}
