#include "stdafx.h"
#include "PlayerControlsComponent.h"
#include "GameObject.h"

#include "KeyboardEvent.h"
#include "MouseEvent.h"
#include "Matrix.h"
#include "MathUtils.h"

PlayerControlsComponent::PlayerControlsComponent(float movementSpeed, float rotateSpeed)
    : GameComponent("CameraTargetComponent"), movementSpeed(movementSpeed), rotateSpeed(rotateSpeed), mouseDelta(Vector<2>(0, 0))
{
}
PlayerControlsComponent::~PlayerControlsComponent()
{
}

void PlayerControlsComponent::Tick(float delta)
{
    Vector<3> translation = { 0, 0, 0 };
    if (this->keysDown[VK_ALPHANUMERIC<'w'>()]) translation += { 0, 0, -1 };
    if (this->keysDown[VK_ALPHANUMERIC<'s'>()]) translation += { 0, 0, 1 };
    if (this->keysDown[VK_ALPHANUMERIC<'a'>()]) translation += { -1, 0, 0 };
    if (this->keysDown[VK_ALPHANUMERIC<'d'>()]) translation += { 1, 0, 0 };

    translation *= delta * movementSpeed;
    if ((GetKeyState(VK_SHIFT) & 0b10000000) != 0) translation *= 5;
    auto transform = gameObject()->localTransform();
    transform->Translate(gameObject()->localTransform()->orientation().Inverse().Apply(translation));
    transform->SetPosition({ transform->position()[0], 1, transform->position()[2] });
}

void PlayerControlsComponent::UpdateGraphics()
{
    gameObject()->localTransform()->SetOrientation(Quaternion<>(mouseDelta[1] * rotateSpeed, { 1, 0, 0 }));
    gameObject()->localTransform()->Rotate(mouseDelta[0] * rotateSpeed, { 0, 1, 0 });
}

void PlayerControlsComponent::HandleEvent(GlEngine::Events::Event & evt)
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
            if (mouseDelta[1] < -90deg / rotateSpeed) mouseDelta = { mouseDelta[0], -90deg / rotateSpeed };
            if (mouseDelta[1] > 90deg / rotateSpeed) mouseDelta = { mouseDelta[0], 90deg / rotateSpeed };
            //GlEngine::Util::Log("%f, %f", mouseEvt->positionChange()[0], mouseEvt->positionChange()[1]);
        }
    }
}
