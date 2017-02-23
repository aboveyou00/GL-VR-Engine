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
    gameObject()->transform.RotateX(_rot[0] * delta);
    gameObject()->transform.RotateY(_rot[1] * delta);
    gameObject()->transform.RotateZ(_rot[2] * delta);
}
