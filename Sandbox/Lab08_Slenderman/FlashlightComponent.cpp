#include "stdafx.h"
#include "FlashlightComponent.h"
#include "GameObject.h"
#include "SpotlightSource.h"

FlashlightComponent::FlashlightComponent()
    : _spotlight(new GlEngine::SpotlightSource({ 0, 0, 0 }, { 1.0, 1.0, 0.9 }, 5.0f, { 0, 0, 0 }, 20deg)), GlEngine::GameComponent("FlashlightComponent")
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

    Vector<3> relativePos = gameObject()->parent()->localTransform()->orientation().Inverse().Apply(Vector<3>{ 0.2, -0.5, 0.2 });
    spotlight()->SetPosition(gameObject()->parent()->localTransform()->position() + relativePos);
    spotlight()->SetDirection(gameObject()->parent()->localTransform()->orientation().Inverse().Apply({ 0, 0, -1 }));
    
    //spotlight()->SetPosition(gameObject()->globalTransform()->position());
    //spotlight()->SetDirection(gameObject()->globalTransform()->orientation().Apply({ 0, 0, -1 }));
}

GlEngine::SpotlightSource *FlashlightComponent::spotlight()
{
    return _spotlight;
}
