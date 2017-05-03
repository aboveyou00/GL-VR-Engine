#include "stdafx.h"
#include "CameraTargetComponent.h"
#include "GameObject.h"

#include "KeyboardEvent.h"
#include "MouseEvent.h"
#include "Matrix.h"

CameraTargetComponent::CameraTargetComponent(float movementSpeed, float rotateSpeed)
    : GameComponent("CameraTargetComponent"), movementSpeed(movementSpeed), rotateSpeed(rotateSpeed), mouseDelta(Vector<2>(0, 0))
{
}
CameraTargetComponent::~CameraTargetComponent()
{
}

void CameraTargetComponent::Tick(float delta)
{
    Vector<3> translation = { 0, 0, 0 };
    if (this->keysDown[VK_ALPHANUMERIC<'w'>()]) translation += { 0, 0, -1 };
    if (this->keysDown[VK_ALPHANUMERIC<'s'>()]) translation += { 0, 0, 1 };
    if (this->keysDown[VK_ALPHANUMERIC<'a'>()]) translation += { -1, 0, 0 };
    if (this->keysDown[VK_ALPHANUMERIC<'d'>()]) translation += { 1, 0, 0 };
    if (this->keysDown[VK_ALPHANUMERIC<'q'>()]) translation += { 0, -1, 0 };
    if (this->keysDown[VK_ALPHANUMERIC<'e'>()]) translation += { 0, 1, 0 };

    translation *= delta * movementSpeed;
    if ((GetKeyState(VK_SHIFT) & 0b10000000) != 0) translation *= 5;
    gameObject()->localTransform()->Translate(gameObject()->localTransform()->orientation().Apply(translation));
}

void CameraTargetComponent::UpdateGraphics()
{
    gameObject()->localTransform()->SetOrientation(Quaternion<>(-mouseDelta[0] * rotateSpeed, { 0, 1, 0 }));
    gameObject()->localTransform()->Rotate(-mouseDelta[1] * rotateSpeed, { 1, 0, 0 });
}

void CameraTargetComponent::HandleEvent(GlEngine::Events::Event &evt)
{
    auto kbEvt = dynamic_cast<GlEngine::Events::KeyboardEvent*>(&evt);
    if (kbEvt != nullptr)
    {
        if (kbEvt->type() == GlEngine::Events::KeyboardEventType::KeyPressed)
        {
            this->keysDown[kbEvt->GetVirtualKeyCode()] = true;
        }
        if (kbEvt->type() == GlEngine::Events::KeyboardEventType::KeyReleased)
        {
            this->keysDown[kbEvt->GetVirtualKeyCode()] = false;
        }
    }
    auto mouseEvt = dynamic_cast<GlEngine::Events::MouseEvent*>(&evt);
    if (mouseEvt != nullptr)
    {
        if (mouseEvt->type() == GlEngine::Events::MouseEventType::Moved)
        {
            mouseDelta += mouseEvt->positionChange();
            //GlEngine::Util::Log("%f, %f", mouseEvt->positionChange()[0], mouseEvt->positionChange()[1]);
        }
    }
}
