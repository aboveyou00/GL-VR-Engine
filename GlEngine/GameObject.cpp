#include "stdafx.h"
#include "GameObject.h"

namespace GlEngine
{
    GameObject::GameObject(Vector<3> position, Matrix<4, 4> orientation)
        : position(position), orientation(orientation)
    {
        RequireTick(false);
    }
    GameObject::~GameObject()
	{
	}

    bool GameObject::Initialize()
    {
        return true;
    }
    void GameObject::Shutdown()
    {
    }
    void GameObject::Tick(float)
    {
    }

    void GameObject::HandleEvent(Events::Event&)
    {
    }
}
