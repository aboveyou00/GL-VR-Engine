#include "stdafx.h"
#include "GameLogic.h"
#include "GameLoop.h"
#include "TileManager.h"

namespace TileRPG
{
    GameLogic::GameLogic()
        : loop(new GlEngine::GameLoop([&](float delta) { this->Tick(delta); }, 60)),
          tiles(new TileManager())
    {
    }
    GameLogic::~GameLogic()
    {
        Shutdown();
        if (loop != nullptr)
        {
            delete loop;
            loop = nullptr;
        }
        if (tiles != nullptr)
        {
            delete tiles;
            tiles = nullptr;
        }
    }

    bool GameLogic::Initialize()
    {
        if (!tiles->Initialize()) return false;

        loop->RunLoop();
        return true;
    }
    void GameLogic::Tick(float delta)
    {
        for (size_t q = 0; q < _gameObjects.size(); q++)
            if (_gameObjects[q]->RequiresTick()) _gameObjects[q]->Tick(delta);
    }
    void GameLogic::Shutdown()
    {
        loop->StopLoop(false);
        tiles->Shutdown();
    }

    void GameLogic::AddGameObject(GlEngine::GameObject *obj)
    {
        for (size_t q = 0; q < _gameObjects.size(); q++)
            if (_gameObjects[q] == obj) return;
        _gameObjects.push_back(obj);
    }
    void GameLogic::RemoveGameObject(GlEngine::GameObject *obj)
    {
        auto idx = std::find(_gameObjects.begin(), _gameObjects.end(), obj);
        if (idx != _gameObjects.end()) _gameObjects.erase(idx);
    }

    void GameLogic::DispatchEvent(GlEngine::Events::Event *evt)
    {
        for (size_t q = 0; q < _gameObjects.size(); q++)
            _gameObjects[q]->HandleEvent(*evt);
    }
}
