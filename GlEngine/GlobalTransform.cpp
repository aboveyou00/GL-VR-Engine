#include "stdafx.h"
#include "GlobalTransform.h"

namespace GlEngine
{
    GlobalTransform::GlobalTransform(Transform* transform, GlobalTransform* parent)
        : transform(transform), parent(parent)
    {
    }
    GlobalTransform::~GlobalTransform()
    {
    }
    
    // TODO: cache for efficiency
    Vector<3> GlobalTransform::position()
    {
        Vector<3> result = _position;
        if (parent != nullptr)
            _position *= parent->matrix();
        return result;
    }

    Quaternion<> GlobalTransform::orientation()
    {
        Quaternion<> result = _orientation;
        if (parent != nullptr)
            result *= parent->orientation();
        return result;
    }

    Vector<3> GlobalTransform::scale()
    {
        // Can't really handle this in the general case, maybe do something more intelligent later
        return transform->scale();
    }

    Matrix<4, 4> GlobalTransform::matrix()
    {
        Matrix<4, 4> result = transform->matrix();
        if (parent != nullptr)
            result = parent->matrix() * result;
        return result;
    }

    Matrix<4, 4> GlobalTransform::inverseMatrix()
    {
        Matrix<4, 4> result = transform->inverseMatrix();
        if (parent != nullptr)
            result *= parent->inverseMatrix();
        return result;
    }

    void GlobalTransform::SetPosition(Vector<3> pos)
    {
        if (parent != nullptr)
            pos = parent->inverseMatrix() * pos;
        transform->SetPosition(pos);
    }

    void GlobalTransform::SetOrientation(Quaternion<> orientation)
    {
        if (parent != nullptr)
            orientation = parent->orientation().Inverse() * orientation;
        transform->SetOrientation(orientation);
    }
    void GlobalTransform::ComposeOrientation(Quaternion<> relative)
    {
        transform->ComposeOrientation(relative);
    }

    void GlobalTransform::SetScale(float x, float y, float z)
    {
        transform->SetScale(x, y, z);
    }
    void GlobalTransform::SetScale(Vector<3> scale)
    {
        transform->SetScale(scale);
    }

    void GlobalTransform::Translate(float x, float y, float z)
    {
        SetPosition(position() + Vector<3>(x, y, z));
    }
    void GlobalTransform::Translate(Vector<3> delta)
    {
        SetPosition(position() + delta);
    }

    void GlobalTransform::Rotate(float radians, Vector<3> axis)
    {
        transform->Rotate(radians, axis);
    }
    void GlobalTransform::RotateX(float radians)
    {
        transform->RotateX(radians);
    }
    void GlobalTransform::RotateY(float radians)
    {
        transform->RotateY(radians);
    }
    void GlobalTransform::RotateZ(float radians)
    {
        transform->RotateZ(radians);
    }

    void GlobalTransform::RotateDegrees(float degrees, Vector<3> axis)
    {
        transform->RotateDegrees(degrees, axis);
    }
    void GlobalTransform::RotateDegreesX(float degrees)
    {
        transform->RotateDegreesX(degrees);
    }
    void GlobalTransform::RotateDegreesY(float degrees)
    {
        transform->RotateDegreesY(degrees);
    }
    void GlobalTransform::RotateDegreesZ(float degrees)
    {
        transform->RotateDegreesZ(degrees);
    }

    void GlobalTransform::Scale(float amt)
    {
        transform->Scale(amt);
    }
    void GlobalTransform::Scale(float x, float y, float z)
    {
        transform->Scale(x, y, z);
    }
    void GlobalTransform::Scale(Vector<3> amt)
    {
        transform->Scale(amt);
    }
}