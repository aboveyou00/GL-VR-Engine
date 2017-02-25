#include "stdafx.h"
#include "CameraComponent.h"
#include "GameObject.h"
#include "MatrixStack.h"
#include "Environment.h"

namespace GlEngine
{
    CameraComponent::CameraComponent()
        : GameComponent("Camera"),
          eye({ 0, 0, 0 }),
          forward({ 0, 0, 1 }),
          up({ 0, 1, 0 }),
          _clearColor({ 0, 0, 0 })
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
        Vector<3> side, forwardN;
        //TODO: set the camera position to a global postion, not a local one
        ShaderFactory::Environment::GetInstance().SetCameraPosition(gameObject()->localTransform()->position());

        eye = gameObject()->localTransform()->position();
        forwardN = gameObject()->localTransform()->orientation() * Vector<3>{ 0, 0, 1 };
        side = gameObject()->localTransform()->orientation() * Vector<3>{ 1, 0, 0 };
        up = gameObject()->localTransform()->orientation() * Vector<3>{ 0, 1, 0 };

        view = Matrix<3, 3>::FromCols(side, up, forwardN).ToTransformMatrix();

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

    //TODO: find a better place to put this
    //void CameraComponent::SetPosition(Vector<3> pos)
    //{
    //    //...
    //    if (target != nullptr)
    //        relativePosition = target->position - position;
    //    //...
    //}
}
