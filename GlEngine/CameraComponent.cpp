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
        ShaderFactory::Environment::GetInstance().SetCameraPosition(gameObject()->localTransform()->position());

        eye = gameObject()->localTransform()->position();
        forward = gameObject()->localTransform()->orientation().Apply(Vector<3>{ 0, 0, -1 });
        right = gameObject()->localTransform()->orientation().Apply(Vector<3>{ 1, 0, 0 });
        up = gameObject()->localTransform()->orientation().Apply(Vector<3>{ 0, 1, 0 });

        view = Matrix<3, 3>::FromCols(right, up, -forward).ToTransformMatrix();

        MatrixStack::View.mult(Matrix<4, 4>::TranslateMatrix(-eye) * view);
    }
    void CameraComponent::Pop(RenderStage*)
    {
        MatrixStack::View.pop();
    }

    Frame* CameraComponent::frame()
    {
        return GameComponent::frame();
    }
}
