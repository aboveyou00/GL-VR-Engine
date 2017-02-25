#include "stdafx.h"
#include "CameraTargetComponent.h"
#include "GameObject.h"

#include "KeyboardEvent.h"
#include "MouseEvent.h"
#include "Matrix.h"

CameraTargetComponent::CameraTargetComponent(float movementSpeed)
    : GameComponent("CameraTargetComponent"), movementSpeed(movementSpeed), mouseDelta(Vector<2>(0, 0))
{
}
CameraTargetComponent::~CameraTargetComponent()
{
}

void CameraTargetComponent::Tick(float delta)
{
    Vector<3> translation = { 0, 0, 0 };
    if (this->keysDown[VK_UP]) translation += { 0, 0, 1 };
    if (this->keysDown[VK_DOWN]) translation += { 0, 0, -1 };
    if (this->keysDown[VK_LEFT]) translation += { -1, 0, 0 };
    if (this->keysDown[VK_RIGHT]) translation += { 1, 0, 0 };
    if (this->keysDown[VK_LETTER<'l'>()]) translation += { 0, -1, 0 };
    if (this->keysDown[VK_LETTER<'o'>()]) translation += { 0, 1, 0 };
    translation *= delta * movementSpeed;
    if ((GetKeyState(VK_SHIFT) & 0b10000000) != 0) translation *= 4;
    gameObject()->localTransform()->Translate(translation);
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
            //mouseDelta += mouseEvt->Get
        }
    }
}
