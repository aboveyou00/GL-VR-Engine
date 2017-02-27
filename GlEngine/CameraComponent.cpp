#include "stdafx.h"
#include "CameraComponent.h"
#include "GameObject.h"
#include "MatrixStack.h"
#include "Environment.h"

namespace GlEngine
{
    CameraComponent::CameraComponent()
        : GameComponent("Camera"), _clearColor({ 0, 0, 0 })
    {
    }
    CameraComponent::~CameraComponent()
    {
    }

    Vector<3> CameraComponent::clearColor()
    {
        return _clearColor;
    }
    void CameraComponent::SetClearColor(Vector<3> color)
    {
        _clearColor = color;
    }

    GameObject *CameraComponent::Create(Frame *frame, std::string name)
    {
        auto gobj = new GameObject(frame, name);
        gobj->AddComponent(new CameraComponent());
        return gobj;
    }

    std::string CameraComponent::name()
    {
        return "CameraComponent";
    }

    void CameraComponent::Tick(float)
    {
    }

    //void CameraComponent::FindOrientation()
    //{
    //    auto diff = target->transform.position - gameObject()->transform.position;
    //    float angleLat = atan2(diff[1], Vector<2>{diff[0], diff[2]}.Length());
    //    float angleLong = atan2(diff[0], diff[2]);

    //    gameObject()->transform.orientation = Quaternion<>(angleLat, { 1, 0, 0 }) * Quaternion<>(angleLong, { 0, 1, 0 });
    //}

    void CameraComponent::Push()
    {
        ShaderFactory::Environment::GetInstance().SetCameraPosition(gameObject()->globalTransform()->position());

        eye = gameObject()->localTransform()->position();
        forward = gameObject()->localTransform()->orientation().Apply(Vector<3>{ 0, 0, -1 });
        right = gameObject()->localTransform()->orientation().Apply(Vector<3>{ 1, 0, 0 });
        up = gameObject()->localTransform()->orientation().Apply(Vector<3>{ 0, 1, 0 });

        view = Matrix<3, 3>::FromCols(right, up, -forward).ToTransformMatrix();

        MatrixStack::View.mult(Mat3T<float>::TranslateMatrix(-eye) * view);
    }
    void CameraComponent::Pop()
    {
        MatrixStack::View.pop();
    }

    Frame *CameraComponent::frame()
    {
        return GameComponent::frame();
    }
}
