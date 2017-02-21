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
          relativeOrientation(Matrix<4, 4>::Identity())
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
        if (lockRelativePosition)
            gameObject()->transform.position = target->transform.position + relativePosition;
        //if (lockRelativeOrientation)
        //    orientation = target->orientation * relativeOrientation;
        FindOrientation();
    }

    void CameraComponent::SetTargetObject(GameObject *obj)
    {
        target = obj;
        FindOrientation();
    }

    void CameraComponent::FindOrientation()
    {
        if (target == nullptr)
            return;
        if (gameObject() == nullptr) return;
        auto diff = target->transform.position - gameObject()->transform.position;
        float angleLat = atan2(diff[1], Vector<2>{diff[0], diff[2]}.Length());
        float angleLong = atan2(diff[0], diff[2]);
        gameObject()->transform.orientation = Matrix<4, 4>::RollMatrix(angleLat) * Matrix<4, 4>::YawMatrix(angleLong);
    }

    void CameraComponent::SetLock(int lockFlags)
    {
        lockRelativePosition    = (lockFlags & CameraLock::RELATIVE_POSITION) != 0;
        lockRelativeOrientation = (lockFlags & CameraLock::RELATIVE_ORIENTATION) != 0;
        lockAbsolutePosition    = (lockFlags & CameraLock::ABSOLUTE_POSITION) != 0;
        lockAbsoluteOrientation = (lockFlags & CameraLock::ABSOLUTE_ORIENTATION) != 0;
    }
    
    void CameraComponent::Lock(int lockFlags)
    {
        lockRelativePosition    |= ((lockFlags & CameraLock::RELATIVE_POSITION) != 0);
        lockRelativeOrientation |= ((lockFlags & CameraLock::RELATIVE_ORIENTATION) != 0);
        lockAbsolutePosition    |= ((lockFlags & CameraLock::ABSOLUTE_POSITION) != 0);
        lockAbsoluteOrientation |= ((lockFlags & CameraLock::ABSOLUTE_ORIENTATION) != 0);
    }

    void CameraComponent::Push()
    {
        Vector<3> side, forwardN;
        ShaderFactory::Environment::GetInstance().SetCameraPosition(gameObject()->transform.position);

        eye = gameObject()->transform.position;
        forwardN = gameObject()->transform.orientation * Vector<3>{ 0, 0, 1 };
        side = gameObject()->transform.orientation * Vector<3>{ 1, 0, 0 };
        up = gameObject()->transform.orientation * Vector<3>{ 0, 1, 0 };

        view = Matrix<3, 3>::FromCols(-side, up, forwardN).ToTransformMatrix();

        MatrixStack::View.mult(Mat3T<float>::TranslateMatrix(-eye) * view);
    }
    void CameraComponent::Pop()
    {
        MatrixStack::View.pop();
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
