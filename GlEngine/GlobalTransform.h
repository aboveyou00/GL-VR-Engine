#pragma once

#include "Transform.h"

namespace GlEngine
{
    class ENGINE_SHARED GlobalTransform : public Transform
    {
    public:
        GlobalTransform(Transform* transform, GlobalTransform* parent = nullptr);
        ~GlobalTransform();

        virtual Vector<3> position() override;
        virtual Quaternion<> orientation() override;
        virtual Vector<3> scale() override;

        virtual Matrix<4, 4> matrix() override;
        virtual Matrix<4, 4> inverseMatrix() override;

        virtual void SetPosition(Vector<3> pos) override;
        virtual void SetOrientation(Quaternion<> orientation) override;
        virtual void ComposeOrientation(Quaternion<> relative) override;
        virtual void SetScale(float x, float y, float z) override;
        virtual void SetScale(Vector<3> scale) override;

        virtual void Translate(float x, float y, float z) override;
        virtual void Translate(Vector<3> delta) override;
        
        virtual void Rotate(float radians, Vector<3> axis) override;

        virtual void RotateX(float radians) override;
        virtual void RotateY(float radians) override;
        virtual void RotateZ(float radians) override;

        virtual void RotateDegrees(float degrees, Vector<3> axis) override;
        virtual void RotateDegreesX(float degrees) override;
        virtual void RotateDegreesY(float degrees) override;
        virtual void RotateDegreesZ(float degrees) override;

        virtual void Scale(float amt) override;
        virtual void Scale(float x, float y, float z) override;
        virtual void Scale(Vector<3> amt) override;

    private:
        Transform* transform;
        GlobalTransform* parent;
    };
}