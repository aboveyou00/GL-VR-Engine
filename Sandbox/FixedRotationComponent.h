#pragma once

#include "GameComponent.h"

class FixedRotationComponent : public GlEngine::GameComponent
{
public:
    FixedRotationComponent(Vector<3> rot);
    ~FixedRotationComponent();

    virtual void Tick(float delta) override;

private:
    Vector<3> _rot;
};
