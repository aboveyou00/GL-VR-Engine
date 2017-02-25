#include "stdafx.h"
#include "Transform.h"
#include "MathUtils.h"

namespace GlEngine
{
    Transform::Transform()
        : _position({ 0, 0, 0 }), _orientation(Quaternion<>(0, { 1, 0, 0 })), _scale({1, 1, 1})
    {
    }
    Transform::~Transform()
    {
    }

    Vector<3> Transform::position()
    {
        return _position;
    }

    Quaternion<> Transform::orientation()
    {
        return _orientation;
    }

    Vector<3> Transform::scale()
    {
        return _scale;
    }

    Matrix<4, 4> Transform::matrix()
    {
        return Matrix<4, 4>::TranslateMatrix(_position) * _orientation.ToMatrix() * Matrix<4, 4>::ScaleMatrix(_scale);
    }

    Matrix<4, 4> Transform::inverseMatrix()
    {
        return Matrix<4, 4>::ScaleMatrix(_scale) * _orientation.ToMatrix() * Matrix<4, 4>::TranslateMatrix(_position);
    }

    void Transform::SetPosition(float x, float y, float z)
    {
        _position = Vector<3>(x, y, z);
    }
    void Transform::SetPosition(Vector<3> pos)
    {
        _position = pos;
    }

    void Transform::SetOrientation(Quaternion<> orientation)
    {
        _orientation = orientation;
    }
    void Transform::ComposeOrientation(Quaternion<> relative)
    {
        _orientation *= relative;
    }

    void Transform::SetScale(float x, float y, float z)
    {
        this->_scale = Vector<3>(x, y, z);
    }

    void Transform::SetScale(Vector<3> scale)
    {
        this->_scale = scale;
    }

    void Transform::Translate(float x, float y, float z)
    {
        _position += Vector<3>(x, y, z);
    }
    void Transform::Translate(Vector<3> delta)
    {
        _position += delta;
    }

    void Transform::Rotate(float radians, Vector<3> axis)
    {
        _orientation *= Quaternion<>(radians, axis);
    }

    void Transform::RotateX(float radians)
    {
        _orientation *= Quaternion<>(radians, { 0, 0, 1 });
    }
    void Transform::RotateY(float radians)
    {
        _orientation *= Quaternion<>(radians, { 0, 1, 0 });
    }
    void Transform::RotateZ(float radians)
    {
        _orientation *= Quaternion<>(radians, { 0, 0, 1 });
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
        _scale *= Matrix<4, 4>::ScaleMatrix(amt);
    }
    void Transform::Scale(float x, float y, float z)
    {
        Scale(Vector<3> { x, y, z });
    }
    void Transform::Scale(Vector<3> amt)
    {
        _scale *= Matrix<4, 4>::ScaleMatrix(amt);
    }
}
