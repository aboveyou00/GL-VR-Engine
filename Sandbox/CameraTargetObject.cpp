#include "stdafx.h"
#include "CameraTargetObject.h"

#include "KeyboardEvent.h"
#include "Matrix.h"

CameraTargetObject::CameraTargetObject(float movementSpeed)
    : movementSpeed(movementSpeed)
{
    RequireTick(true);
}
CameraTargetObject::~CameraTargetObject()
{
}

const char *CameraTargetObject::name()
{
    return "CameraTargetObject";
}

void CameraTargetObject::Tick(float delta)
{
    Vector<3> translation = { 0, 0, 0 };
    if (this->keysDown[VK_UP]) translation += { 0, 0, 1 };
    if (this->keysDown[VK_DOWN]) translation += { 0, 0, -1 };
    if (this->keysDown[VK_LEFT]) translation += { -1, 0, 0 };
    if (this->keysDown[VK_RIGHT]) translation += { 1, 0, 0 };
    if (this->keysDown[VK_LETTER<'l'>()]) translation += { 0, -1, 0 };
    if (this->keysDown[VK_LETTER<'o'>()]) translation += { 0, 1, 0 };
    translation *= delta * movementSpeed;
    position += translation;
}

void CameraTargetObject::HandleEvent(GlEngine::Events::Event &evt)
{
    auto kbevt = dynamic_cast<GlEngine::Events::KeyboardEvent*>(&evt);
    if (kbevt == nullptr) return;
    if (kbevt->GetEventType() == GlEngine::Events::KeyboardEventType::KeyPressed) this->keysDown[kbevt->GetVirtualKeyCode()] = true;
    if (kbevt->GetEventType() == GlEngine::Events::KeyboardEventType::KeyReleased) this->keysDown[kbevt->GetVirtualKeyCode()] = false;
}

GlEngine::GraphicsObject *CameraTargetObject::CreateGraphicsObject(GlEngine::GraphicsContext&)
{
    return nullptr;
}
