#include "stdafx.h"
#include "FlashlightComponent.h"
#include "GameObject.h"
#include "SpotlightSource.h"

#include "MouseEvent.h"
#include "IAudioSource.h"

FlashlightComponent::FlashlightComponent()
    : AudioSourceComponent("Flashlight", "Audio/flashlight.wav"s),
      _spotlight(new GlEngine::SpotlightSource({ 0, 0, 0 }, { 1.0, 1.0, 0.9 }, 5.0f, { 0, 0, 0 }, 20deg)),
      _isOn(true),
      _power(1.f)
{
    source()->Play(false);
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

void FlashlightComponent::Tick(float delta)
{
    GameComponent::Tick(delta);

    //Vector<3> relativePos = gameObject()->parent()->localTransform()->orientation().Inverse().Apply(Vector<3>{ 0.2, -0.5, 0.2 });
    //spotlight()->SetPosition(gameObject()->parent()->localTransform()->position() + relativePos);
    //spotlight()->SetDirection(gameObject()->parent()->localTransform()->orientation().Inverse().Apply({ 0, 0, -1 }));
    spotlight()->SetPosition(gameObject()->globalTransform()->position());
    spotlight()->SetDirection(gameObject()->globalTransform()->orientation().Apply({ 0, 0, 1 }));

    //spotlight()->SetPosition(gameObject()->globalTransform()->position());
    //spotlight()->SetDirection(gameObject()->globalTransform()->orientation().Apply({ 0, 0, -1 }));

    if (_isOn)
    {
        _power -= delta / 500;
        _spotlight->SetColor(Vector<3> { 1.f, 1.f, .9f } *_power);
    }
    else
    {
        _spotlight->SetColor({ 0, 0, 0 });
    }
}

void FlashlightComponent::HandleEvent(GlEngine::Events::Event &evt)
{
    auto mouseEvt = dynamic_cast<GlEngine::Events::MouseEvent*>(&evt);
    if (mouseEvt != nullptr)
    {
        if (mouseEvt->type() == GlEngine::Events::MouseEventType::Pressed && mouseEvt->button() == GlEngine::Events::MouseButton::Right)
        {
            _isOn = !_isOn;
            source()->Play(false);
            mouseEvt->Handle();
        }
    }
    if (!evt.IsHandled()) GameComponent::HandleEvent(evt);
}

GlEngine::SpotlightSource *FlashlightComponent::spotlight()
{
    return _spotlight;
}
