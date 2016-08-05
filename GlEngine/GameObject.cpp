#include "stdafx.h"
#include "GameObject.h"

#include "MathUtils.h"

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

	void GameObject::SetPosition(Vector<3> pos)
	{
		position = pos;
	}
	void GameObject::SetOrientation(Matrix<4, 4> orientation)
	{
		orientation = orientation;
	}
	void GameObject::ApplyOrientation(Matrix<4, 4> relative)
	{
		orientation *= relative;
	}

	void GameObject::Rotate(float radians, Vector<3> axis)
	{
		orientation *= Matrix<4, 4>::Rotate3dMatrix(radians, axis);
	}

	void GameObject::RotateX(float radians)
	{
		orientation *= Matrix<4, 4>::PitchMatrix(radians);
	}
	void GameObject::RotateY(float radians)
	{
		orientation *= Matrix<4, 4>::YawMatrix(radians);
	}
	void GameObject::RotateZ(float radians)
	{
		orientation *= Matrix<4, 4>::RollMatrix(radians);
	}

	void GameObject::RotateDegrees(float degrees, Vector<3> axis)
	{
		Rotate((float)Util::degToRad(degrees), axis);
	}
	void GameObject::RotateDegreesX(float degrees)
	{
		RotateX((float)Util::degToRad(degrees));
	}
	void GameObject::RotateDegreesY(float degrees)
	{
		RotateY((float)Util::degToRad(degrees));
	}
	void GameObject::RotateDegreesZ(float degrees)
	{
		RotateZ((float)Util::degToRad(degrees));
	}

	const char * GameObject::type()
	{
		return "Object3d";
	}
}
