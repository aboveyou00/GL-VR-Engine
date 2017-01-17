#include "stdafx.h"
#include "ResourceLoader.h"

#include "Engine.h"
#include "ServiceProvider.h"
#include "ILogger.h"

namespace GlEngine
{
    ResourceLoader::ResourceLoader()
        : _gameLoop(
            [&]() { return this->initLoop(); },
            [&](float delta) { this->loop(delta); },
            [&]() { this->shutdownLoop(); },
            15
          )
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

        for (size_t q = 0; q < graphics_queue.size(); q++)
            graphics_queue[q]->Shutdown();
        graphics_queue.clear();

        c_queue.clear();
    }

    const char *ResourceLoader::name()
    {
        return "ResourceLoader";
    }

    void ResourceLoader::QueueResource(IComponent *c, bool reentrant)
    {
        assert(c != nullptr);

        ScopedLock _lock(_mutex);
        auto find_c = std::find(c_queue.begin(), c_queue.end(), c);
        auto find_g = std::find(graphics_queue.begin(), graphics_queue.end(), c);
        auto find_complete = std::find(complete_resources.begin(), complete_resources.end(), c);

        if (!reentrant) assert(find_c == c_queue.end() && find_g == graphics_queue.end() && find_complete == complete_resources.end());
        if (find_c == c_queue.end()) c_queue.push_back(c);

        if (find_g != graphics_queue.end()) graphics_queue.erase(find_g);
        if (find_complete != complete_resources.end()) complete_resources.erase(find_complete);
    }
    void ResourceLoader::QueueShutdown(IComponent *c)
    {
        assert(c != nullptr);

        ScopedLock _lock(_mutex);
        auto gfx = dynamic_cast<IGraphicsComponent*>(c);
        if (gfx != nullptr)
        {
            graphics_shutdown_queue.push_back(gfx);
            collection_remove(graphics_queue, gfx);
        }
        else c_shutdown_queue.push_back(c);

        collection_remove(c_queue, c);
        collection_remove(complete_resources, c);
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
        clearShutdownGraphicsQueue();
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
        clearShutdownGraphicsQueue();
    }
    void ResourceLoader::clearShutdownGraphicsQueue()
    {
        for (;;)
        {
            IGraphicsComponent *c;
            {
                ScopedLock _lock(_mutex);
                if (graphics_shutdown_queue.size() == 0) break;
                c = graphics_shutdown_queue.at(0);
                graphics_shutdown_queue.pop_front();
            }
            c->ShutdownGraphics();
            {
                ScopedLock _lock(_mutex);
                c_shutdown_queue.push_back(c);
            }
        }
    }

    bool ResourceLoader::initLoop()
    {
        this_thread_name() = "rscloadr";
        this_thread_type() = ThreadType::ResourceLoader;
        auto logger = Engine::GetInstance().GetServiceProvider().GetService<ILogger>();
        logger->Log(LogType::Info, "Beginning resource loader thread...");
        return true;
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
                logger->Log(LogType::ErrorC, "Asynchronous resource loader failed to initialize %s (IComponent)", c->name());
                continue;
            }
            {
                ScopedLock _lock(_mutex);
                IGraphicsComponent *g = dynamic_cast<IGraphicsComponent*>(c);
                if (g != nullptr) graphics_queue.push_back(g);
                else complete_resources.push_back(c);
            }
        }
        clearShutdownQueue();
    }
    void ResourceLoader::shutdownLoop()
    {
        auto logger = Engine::GetInstance().GetServiceProvider().GetService<ILogger>();
        logger->Log(LogType::Info, "~Terminating resource loader thread...");
    }

    void ResourceLoader::clearShutdownQueue()
    {
        IComponent *c;
        for (;;)
        {
            {
                ScopedLock _lock(_mutex);
                if (c_shutdown_queue.size() == 0) break;
                c = c_shutdown_queue.at(0);
                c_shutdown_queue.pop_front();
            }
            c->Shutdown();
        }
    }
}
