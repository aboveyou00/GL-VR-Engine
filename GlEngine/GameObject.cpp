#include "stdafx.h"
#include "GameObject.h"

namespace GlEngine
{
    GameObject::GameObject(Vector<3> position, Matrix<4, 4> orientation)
        : position(position), orientation(orientation), _frame(nullptr)
    {
        RequireTick(false);
    }
    GameObject::~GameObject()
	{
	}

    bool GameObject::Initialize()
    {
        assert(_frame != nullptr);
        return true;
    }
    void GameObject::Shutdown()
    {
    }
    void GameObject::Tick(float)
    {
    }

    void GameObject::AddToFrame(Frame *frame)
    {
        assert(frame != nullptr);
        assert(_frame == nullptr);
        _frame = frame;
    }
    void GameObject::RemoveFromFrame(Frame *frame)
    {
        assert(frame != nullptr);
        assert(_frame == frame);
        _frame = nullptr;
    }

    void GameObject::HandleEvent(Events::Event&)
    {
    }

    void GameObject::UpdateGraphicsObject(GraphicsContext&, GraphicsObject*)
    {
    }
}
