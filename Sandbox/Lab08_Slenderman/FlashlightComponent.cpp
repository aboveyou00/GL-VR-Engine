#include "stdafx.h"
#include "FlashlightComponent.h"
#include "GameObject.h"
#include "SpotlightSource.h"

FlashlightComponent::FlashlightComponent()
    : _spotlight(new GlEngine::SpotlightSource()), GlEngine::GameComponent("FlashlightComponent")
{
}
FlashlightComponent::~FlashlightComponent()
{
}

GlEngine::GameObject *FlashlightComponent::Create(GlEngine::Frame *frame)
{
    auto gobj = new GlEngine::GameObject(frame, "Flashlight");
    gobj->AddComponent(new FlashlightComponent());
    return gobj;
}

bool FlashlightComponent::InitializeAsync()
{
    if (!GameComponent::InitializeAsync()) return false;

    return false;
}
void FlashlightComponent::ShutdownAsync()
{
    GameComponent::ShutdownAsync();
}

void FlashlightComponent::Tick(float delta)
{
    GameComponent::Tick(delta);

    spotlight()->SetPosition(gameObject()->globalTransform()->position());
    spotlight()->SetDirection(gameObject()->globalTransform()->orientation().Apply({ 0, 0, -1 }));
}

GlEngine::SpotlightSource *FlashlightComponent::spotlight()
{
    return _spotlight;
}
