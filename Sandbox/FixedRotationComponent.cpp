#include "stdafx.h"
#include "FixedRotationComponent.h"
#include "GameObject.h"

FixedRotationComponent::FixedRotationComponent(Vector<3> rot)
    : GameComponent("FixedRotation"), _rot(rot)
{
}
FixedRotationComponent::~FixedRotationComponent()
{
}

void FixedRotationComponent::Tick(float delta)
{
    gameObject()->localTransform()->RotateX(_rot[0] * delta);
    gameObject()->localTransform()->RotateY(_rot[1] * delta);
    gameObject()->localTransform()->RotateZ(_rot[2] * delta);
}
