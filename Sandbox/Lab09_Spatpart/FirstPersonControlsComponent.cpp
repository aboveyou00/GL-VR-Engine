#include "stdafx.h"
#include "FirstPersonControlsComponent.h"
#include "GameObject.h"

#include "KeyboardEvent.h"
#include "MouseEvent.h"
#include "Matrix.h"
#include "MathUtils.h"
#include "AudioSourceComponent.h"
#include "IAudioSource.h"

#include "Frame.h"

FirstPersonControlsComponent::FirstPersonControlsComponent(float movementSpeed, float rotateSpeed)
    : AudioListenerComponent("CameraTargetComponent"), movementSpeed(movementSpeed), rotateSpeed(rotateSpeed), mouseDelta(Vector<2>(0, 0))
{
    footsteps = new GlEngine::AudioSourceComponent("Footsteps");
    footsteps->source()->SetVolume(2.f);
}
FirstPersonControlsComponent::~FirstPersonControlsComponent()
{
}

void FirstPersonControlsComponent::Tick(float delta)
{
    AudioListenerComponent::Tick(delta);

    float static_change = -.075f;
    if (this->keysDown[VK_ALPHANUMERIC<'q'>()]) static_change -= 1;
    if (this->keysDown[VK_ALPHANUMERIC<'e'>()]) static_change += 1;
    static_change *= delta;

    Vector<3> translation = { 0, 0, 0 };
    if (this->keysDown[VK_ALPHANUMERIC<'w'>()]) translation += { 0, 0, -1 };
    if (this->keysDown[VK_ALPHANUMERIC<'s'>()]) translation += { 0, 0, 1 };
    if (this->keysDown[VK_ALPHANUMERIC<'a'>()]) translation += { -1, 0, 0 };
    if (this->keysDown[VK_ALPHANUMERIC<'d'>()]) translation += { 1, 0, 0 };

    translation *= delta * movementSpeed;
    bool isSprinting = (GetKeyState(VK_SHIFT) & 0b10000000) != 0;
    if (isSprinting) translation *= 2;

    auto transform = gameObject()->localTransform();
    transform->Translate(transform->orientation().Apply(translation));
    transform->SetPosition({ transform->position()[0], 1, transform->position()[2] });

    footsteps->source()->SetSource(isSprinting ? "Audio/footstep-grass-clipped.wav"s : "Audio/footstep-grass.wav");
    bool playFootsteps = translation.LengthSquared() > .2f * delta;
    if (playFootsteps)
    {
        if (!footsteps->source()->IsPlaying()) footsteps->source()->Play(true);
    }
    else if (!playFootsteps)
    {
        if (footsteps->source()->IsPlaying()) footsteps->source()->SetLoop(false);
    }
}

void FirstPersonControlsComponent::UpdateGraphics()
{
    gameObject()->localTransform()->SetOrientation(Quaternion<>(-mouseDelta[0] * rotateSpeed, { 0, 1, 0 }));
    gameObject()->localTransform()->Rotate(-mouseDelta[1] * rotateSpeed, { 1, 0, 0 });
}

void FirstPersonControlsComponent::HandleEvent(GlEngine::Events::Event &evt)
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
    if (!evt.IsHandled()) GameComponent::HandleEvent(evt);
}

void FirstPersonControlsComponent::GameObjectChanged()
{
    if (gameObject() != nullptr) gameObject()->AddComponent(footsteps);
}
