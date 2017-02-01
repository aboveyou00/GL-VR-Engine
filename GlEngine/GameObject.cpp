#include "stdafx.h"
#include "GameObject.h"

#include "MathUtils.h"

namespace GlEngine
{
    GameObject::GameObject(Vector<3> position, Matrix<4, 4> orientation)
        : position(position), orientation(orientation), _frame(nullptr), _requiresUniqueGfx(false), _requiresTick(false), _requiresGraphicsTick(false)
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
        auto body = actor()->body;
        if (body != nullptr)
        {
            if (body->position[1] < -10) body->position += {0, 20, 0};
            position = body->position;
        }
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

    void GameObject::UpdateGraphicsObject(GraphicsContext*, GraphicsObject*)
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
        orientation *= Matrix<4, 4>::RotateMatrix(radians, axis);
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

    void GameObject::Scale(float amt)
    {
        orientation *= Matrix<4, 4>::ScaleMatrix(amt);
    }
    void GameObject::Scale(float x, float y, float z)
    {
        Scale(Vector<3> { x, y, z });
    }
    void GameObject::Scale(Vector<3> amt)
    {
        orientation *= Matrix<4, 4>::ScaleMatrix(amt);
    }

    void GameObject::Activate()
    {
        _active = true;
        actor()->Activate();
    }
    void GameObject::Deactivate()
    {
        _active = false;
        actor()->Deactivate();
    }
    bool GameObject::active() const
    {
        return _active;
    }

    GameObjectType GameObject::type() const
    {
        return GameObjectType::Object3d;
    }
    Frame *GameObject::frame() const
    {
        return _frame;
    }
    Actor *GameObject::actor()
    {
        return &_actor;
    }
}
