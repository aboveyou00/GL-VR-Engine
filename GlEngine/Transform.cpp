#include "stdafx.h"
#include "Transform.h"
#include "MathUtils.h"

namespace GlEngine
{
    Transform::Transform()
        : position({ 0, 0, 0 }), orientation(Matrix<4, 4>::Identity())
    {
    }
    Transform::~Transform()
    {
    }

    void Transform::SetPosition(Vector<3> pos)
    {
        position = pos;
    }
    void Transform::SetOrientation(Matrix<4, 4> orientation)
    {
        orientation = orientation;
    }
    void Transform::ApplyOrientation(Matrix<4, 4> relative)
    {
        orientation *= relative;
    }

    void Transform::Rotate(float radians, Vector<3> axis)
    {
        orientation *= Matrix<4, 4>::RotateMatrix(radians, axis);
    }

    void Transform::RotateX(float radians)
    {
        orientation *= Matrix<4, 4>::PitchMatrix(radians);
    }
    void Transform::RotateY(float radians)
    {
        orientation *= Matrix<4, 4>::YawMatrix(radians);
    }
    void Transform::RotateZ(float radians)
    {
        orientation *= Matrix<4, 4>::RollMatrix(radians);
    }

    void Transform::RotateDegrees(float degrees, Vector<3> axis)
    {
        Rotate((float)Util::degToRad(degrees), axis);
    }
    void Transform::RotateDegreesX(float degrees)
    {
        RotateX((float)Util::degToRad(degrees));
    }
    void Transform::RotateDegreesY(float degrees)
    {
        RotateY((float)Util::degToRad(degrees));
    }
    void Transform::RotateDegreesZ(float degrees)
    {
        RotateZ((float)Util::degToRad(degrees));
    }

    void Transform::Scale(float amt)
    {
        orientation *= Matrix<4, 4>::ScaleMatrix(amt);
    }
    void Transform::Scale(float x, float y, float z)
    {
        Scale(Vector<3> { x, y, z });
    }
    void Transform::Scale(Vector<3> amt)
    {
        orientation *= Matrix<4, 4>::ScaleMatrix(amt);
    }
}
