#include "stdafx.h"
#include "GameComponent.h"
#include "GameObject.h"

namespace GlEngine
{
    GameComponent::GameComponent(std::string name)
        : _active(true), _gameObject(nullptr), _name(name)
    {
    }
    GameComponent::~GameComponent()
    {
    }

    GameObject *GameComponent::gameObject() const
    {
        return _gameObject;
    }
    Frame *GameComponent::frame() const
    {
        if (_gameObject == nullptr) return nullptr;
        return _gameObject->frame();
    }

    bool GameComponent::InitializeAsync()
    {
        return true;
    }
    void GameComponent::ShutdownAsync()
    {
    }
    bool GameComponent::InitializeGraphics()
    {
        return true;
    }
    void GameComponent::ShutdownGraphics()
    {
    }

    bool GameComponent::isReady()
    {
        return true;
    }

    std::string GameComponent::name()
    {
        return _name;
    }

    void GameComponent::Deactivate()
    {
        _active = false;
    }
    void GameComponent::Activate()
    {
        _active = true;
    }
    bool GameComponent::active() const
    {
        return _active;
    }

    void GameComponent::Tick(float)
    {
    }
    
    void GameComponent::HandleEvent(Events::Event&)
    {
    }

    void GameComponent::TickGraphics(float)
    {
    }
    void GameComponent::UpdateGraphics()
    {
    }
    void GameComponent::Render(RenderStage*)
    {
    }
    
    void GameComponent::GameObjectChanged()
    {
    }
}
