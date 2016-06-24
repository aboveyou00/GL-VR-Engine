#include "stdafx.h"
#include "GameObject.h"

namespace GlEngine
{
    GameObject::GameObject(Vector<3> position, Matrix<4, 4> orientation)
        : position(position), orientation(orientation)
    {
    }
    GameObject::~GameObject()
	{
	}


}
