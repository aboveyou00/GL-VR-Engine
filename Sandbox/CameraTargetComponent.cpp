#include "stdafx.h"
#include "CameraTargetComponent.h"
#include "GameObject.h"

#include "KeyboardEvent.h"
#include "Matrix.h"

CameraTargetComponent::CameraTargetComponent(float movementSpeed)
    : GameComponent("CameraTargetComponent"), movementSpeed(movementSpeed)
{
}
CameraTargetComponent::~CameraTargetComponent()
{
}

GlEngine::GameObject *CameraTargetComponent::Create(GlEngine::Frame *frame, std::string name, float movementSpeed)
{
    auto gobj = new GlEngine::GameObject(frame, name);
    gobj->AddComponent(new CameraTargetComponent(movementSpeed));
    return gobj;
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
    gameObject()->transform.position += translation;
}

void CameraTargetComponent::HandleEvent(GlEngine::Events::Event &evt)
{
    auto kbevt = dynamic_cast<GlEngine::Events::KeyboardEvent*>(&evt);
    if (kbevt == nullptr) return;
    if (kbevt->GetEventType() == GlEngine::Events::KeyboardEventType::KeyPressed) this->keysDown[kbevt->GetVirtualKeyCode()] = true;
    if (kbevt->GetEventType() == GlEngine::Events::KeyboardEventType::KeyReleased) this->keysDown[kbevt->GetVirtualKeyCode()] = false;
}
