#pragma once

#include "MatrixTransform.h"

namespace GlEngine
{
    struct ENGINE_SHARED Transform
    {
    public:
        Transform();
        ~Transform();

        virtual Vector<3> position();
        virtual Quaternion<> orientation();
        virtual Vector<3> scale();

        virtual Matrix<4, 4> matrix();
        virtual Matrix<4, 4> inverseMatrix();

        virtual void SetPosition(float x, float y, float z);
        virtual void SetPosition(Vector<3> pos);
        
        virtual void SetOrientation(Quaternion<> orientation);
        virtual void ComposeOrientation(Quaternion<> relative);
        
        virtual void SetScale(float x, float y, float z);
        virtual void SetScale(Vector<3> scale);

        virtual void Translate(float x, float y, float z);
        virtual void Translate(Vector<3> delta);

        virtual void Rotate(float radians, Vector<3> axis);

        virtual void RotateX(float radians);
        virtual void RotateY(float radians);
        virtual void RotateZ(float radians);

        virtual void RotateDegrees(float degrees, Vector<3> axis);
        virtual void RotateDegreesX(float degrees);
        virtual void RotateDegreesY(float degrees);
        virtual void RotateDegreesZ(float degrees);

        virtual void Scale(float amt);
        virtual void Scale(float x, float y, float z);
        virtual void Scale(Vector<3> amt);

    protected:
        Vector<3> _position;
        Vector<3> _scale;
        Quaternion<> _orientation;
    };
}
