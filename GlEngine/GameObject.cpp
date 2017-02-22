#include "stdafx.h"
#include "GameObject.h"

#include "MathUtils.h"
#include "Frame.h"
#include "Event.h"

namespace GlEngine
{
    GameObject::GameObject(Frame *frame, std::string name)
        : _frame(frame), _name(name), _parent(nullptr)
    {
        assert(_frame != nullptr);
        _frame->_children.push_back(this);
    }
    GameObject::~GameObject()
    {
    }

    Frame *GameObject::frame() const
    {
        return _frame;
    }
    std::string GameObject::name() const
    {
        return _name;
    }

    GameObject *GameObject::parent() const
    {
        return _parent;
    }
    void GameObject::SetParent(GameObject *parent)
    {
        auto oldParent = _parent;
        if (oldParent == parent) return;
        if (oldParent != nullptr) collection_remove(oldParent->_children, this);
        else collection_remove(_frame->_children, this);
        if (parent != nullptr) parent->_children.push_back(this);
        else _frame->_children.push_back(this);
    }
    const std::vector<GameObject*> &GameObject::children()
    {
        return _children;
    }

    void GameObject::AddComponent(GameComponent *c)
    {
        assert(c->_gameObject == nullptr);
        this->_components.push_back(c);
        c->_gameObject = this;
    }
    void GameObject::RemoveComponent(GameComponent *c)
    {
        assert(c->_gameObject == this);
        collection_remove(this->_components, c);
        c->_gameObject = nullptr;
    }
    const std::vector<GameComponent*> &GameObject::components()
    {
        return _components;
    }

    void GameObject::Activate()
    {
        _active = true;
    }
    void GameObject::Deactivate()
    {
        _active = false;
    }
    bool GameObject::active() const
    {
        return _active;
    }

    void GameObject::Tick(float delta)
    {
        if (!active()) return;
        for (size_t q = 0; q < _components.size(); q++)
        {
            auto c = _components[q];
            if (c->_active) c->Tick(delta);
        }
        for (size_t q = 0; q < _children.size(); q++)
        {
            auto c = _children[q];
            if (c->_active) c->Tick(delta);
        }
    }

    void GameObject::HandleEvent(Events::Event &evt)
    {
        if (!active()) return;
        for (size_t q = 0; q < _components.size(); q++)
        {
            auto c = _components[q];
            if (c->_active)
            {
                c->HandleEvent(evt);
                if (evt.IsHandled())
                    return;
            }
        }
        for (size_t q = 0; q < _children.size(); q++)
        {
            auto c = _children[q];
            if (c->_active)
            {
                c->HandleEvent(evt);
                if (evt.IsHandled())
                    return;
            }
        }
    }

    void GameObject::TickGraphics(float delta)
    {
        if (!active()) return;
        for (size_t q = 0; q < _components.size(); q++)
        {
            auto c = _components[q];
            if (c->_active) c->TickGraphics(delta);
        }
        for (size_t q = 0; q < _children.size(); q++)
        {
            auto c = _children[q];
            if (c->_active) c->TickGraphics(delta);
        }
    }
    void GameObject::UpdateGraphics()
    {
        if (!active()) return;
        for (size_t q = 0; q < _components.size(); q++)
        {
            auto c = _components[q];
            if (c->_active) c->UpdateGraphics();
        }
        for (size_t q = 0; q < _children.size(); q++)
        {
            auto c = _children[q];
            if (c->_active) c->UpdateGraphics();
        }
    }
    void GameObject::Render(RenderTargetLayer layer)
    {
        if (!active()) return;
        auto _t = MatrixTransform(MatrixStack::Model, transform);
        for (size_t q = 0; q < _components.size(); q++)
        {
            auto c = _components[q];
            if (c->_active) c->Render(layer);
        }
        for (size_t q = 0; q < _children.size(); q++)
        {
            auto c = _children[q];
            if (c->_active) c->Render(layer);
        }
    }
}
