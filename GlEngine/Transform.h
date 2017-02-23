#pragma once

#include "MatrixTransform.h"

namespace GlEngine
{
    struct ENGINE_SHARED Transform
    {
    public:
        Transform();
        ~Transform();

        Vector<3> position;
        //Vector<3> scale;
        Matrix<4, 4> orientation;

        virtual void SetPosition(Vector<3> pos);
        virtual void SetOrientation(Matrix<4, 4> orientation);
        virtual void ApplyOrientation(Matrix<4, 4> relative);

        virtual void Rotate(float radians, Vector<3> axis);

        virtual void RotateX(float radians);
        virtual void RotateY(float radians);
        virtual void RotateZ(float radians);

        void RotateDegrees(float degrees, Vector<3> axis);
        void RotateDegreesX(float degrees);
        void RotateDegreesY(float degrees);
        void RotateDegreesZ(float degrees);

        void Scale(float amt);
        void Scale(float x, float y, float z);
        void Scale(Vector<3> amt);
    };
}
