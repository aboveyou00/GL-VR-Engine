#include "stdafx.h"
#include "CameraTargetObject.h"
#include "CameraGameObject.h"
#include "KeyboardEvent.h"
#include "Matrix.h"
#include "MathUtils.h"

#include "LightSourceGraphicsObject.h"

CameraTargetObject::CameraTargetObject(GlEngine::CameraGameObject *camera, float movementSpeed)
    : camera(camera), movementSpeed(movementSpeed), facingAngle(0), elevationAngle(0)
{
    assert(camera != nullptr);
    RequireTick(true);
    camera->SetTargetObject(this);
}
CameraTargetObject::~CameraTargetObject()
{
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
    if ((GetKeyState(VK_SHIFT) & 0b10000000) != 0) translation *= 4;
    position += translation;

    facingAngle += 15deg * delta;
    Vector<3> cameraFromDir = { cos(facingAngle), 0, sin(facingAngle) };

    camera->SetPosition(position + (cameraFromDir * 15));
}

void CameraTargetObject::HandleEvent(GlEngine::Events::Event &evt)
{
    auto kbevt = dynamic_cast<GlEngine::Events::KeyboardEvent*>(&evt);
    if (kbevt == nullptr) return;
    if (kbevt->GetEventType() == GlEngine::Events::KeyboardEventType::KeyPressed) this->keysDown[kbevt->GetVirtualKeyCode()] = true;
    if (kbevt->GetEventType() == GlEngine::Events::KeyboardEventType::KeyReleased) this->keysDown[kbevt->GetVirtualKeyCode()] = false;
}

std::string CameraTargetObject::name()
{
    return "CameraTargetObject";
}

GlEngine::GraphicsObject *CameraTargetObject::CreateGraphicsObject(GlEngine::GraphicsContext*)
{
    return new LightSourceGraphicsObject();
    //return nullptr;
}
