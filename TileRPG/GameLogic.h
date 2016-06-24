#pragma once

#include "World.h"
#include "IGameComponent.h"

#include "Event.h"

#include "GameObject.h"
#include <vector>

namespace GlEngine
{
    class GameLoop;
}

namespace TileRPG
{
    class TileManager;

    class GameLogic : public GlEngine::IGameComponent
    {
    public:
        GameLogic();
        ~GameLogic();

        bool Initialize();
        void Tick(float delta);
        void Shutdown();

        void AddGameObject(GlEngine::GameObject *obj);
        void RemoveGameObject(GlEngine::GameObject *obj);

        void DispatchEvent(GlEngine::Events::Event *evt);

    private:
        World world;
        TileManager *tiles;
        GlEngine::GameLoop *loop;
        std::vector<GlEngine::GameObject*> _gameObjects;
    };
}
