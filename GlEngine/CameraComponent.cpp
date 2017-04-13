#include "stdafx.h"
#include "CameraComponent.h"
#include "GameObject.h"
#include "MatrixStack.h"
#include "Environment.h"
#include "ViewPort.h"
#include "RenderStage.h"

namespace GlEngine
{
    CameraComponent::CameraComponent()
        : GameComponent("Camera"), _clearColor({ 0, 0, 0 }), _renderPipeline(nullptr)
    {
    }
    CameraComponent::~CameraComponent()
    {
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

    void CameraComponent::Push(RenderStage*)
    {
        ShaderFactory::Environment::GetInstance().SetCameraPosition(gameObject()->globalTransform()->position());

        eye = gameObject()->globalTransform()->position();
        forward = gameObject()->globalTransform()->orientation().Apply(Vector<3>{ 0, 0, -1 });
        right = gameObject()->globalTransform()->orientation().Apply(Vector<3>{ 1, 0, 0 });
        up = gameObject()->globalTransform()->orientation().Apply(Vector<3>{ 0, 1, 0 });

        view = Matrix<3, 3>::FromCols(right, up, -forward).ToTransformMatrix();
        MatrixStack::View.mult(view * Matrix<4, 4>::TranslateMatrix(-eye));
    }
    void CameraComponent::Pop(RenderStage*)
    {
        MatrixStack::View.pop();
    }

    Frame* CameraComponent::frame()
    {
        return GameComponent::frame();
    }
    Ray CameraComponent::centerRay()
    {
        return Ray { eye, forward };
    }
    Ray CameraComponent::rayToPoint(Vector<3> point)
    {
        return Ray { eye, (point - eye).Normalized() };
    }
}
