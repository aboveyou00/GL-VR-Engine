#include "stdafx.h"
#include "PlayerControlsComponent.h"
#include "GameObject.h"

#include "KeyboardEvent.h"
#include "MouseEvent.h"
#include "Matrix.h"
#include "MathUtils.h"
#include <sstream>
#include "AudioSourceComponent.h"
#include "IAudioSource.h"
#include "StringUtils.h"

PlayerControlsComponent::PlayerControlsComponent(float *static_amount, float movementSpeed, float rotateSpeed)
    : AudioListenerComponent("CameraTargetComponent"), static_amount(*static_amount), movementSpeed(movementSpeed), rotateSpeed(rotateSpeed), mouseDelta(Vector<2>(0, 0)), renderText("Pages: 0 of 8")
{
    music = new GlEngine::AudioSourceComponent("Music");
    UpdateMusic();

    footsteps = new GlEngine::AudioSourceComponent("Footsteps");
    panting = new GlEngine::AudioSourceComponent("Panting");
    footsteps->source()->SetVolume(2.f);

    staticsfx = new GlEngine::AudioSourceComponent("Static");
    staticsfx->source()->SetSource("Audio/static.wav");
}
PlayerControlsComponent::~PlayerControlsComponent()
{
}

void PlayerControlsComponent::Tick(float delta)
{
    float static_change = -.075f;
    if (this->keysDown[VK_ALPHANUMERIC<'q'>()]) static_change -= 1;
    if (this->keysDown[VK_ALPHANUMERIC<'e'>()]) static_change += 1;
    static_change *= delta;
    static_amount = max(0.f, min(1.f, static_amount + static_change));
    if (static_amount == 0) staticsfx->source()->Stop();
    else
    {
        if (!staticsfx->source()->IsPlaying()) staticsfx->source()->Play(true);
        staticsfx->source()->SetVolume(static_amount * .5f);
    }

    Vector<3> translation = { 0, 0, 0 };
    if (this->keysDown[VK_ALPHANUMERIC<'w'>()]) translation += { 0, 0, -1 };
    if (this->keysDown[VK_ALPHANUMERIC<'s'>()]) translation += { 0, 0, 1 };
    if (this->keysDown[VK_ALPHANUMERIC<'a'>()]) translation += { -1, 0, 0 };
    if (this->keysDown[VK_ALPHANUMERIC<'d'>()]) translation += { 1, 0, 0 };

    translation *= delta * movementSpeed;
    bool isSprinting = (GetKeyState(VK_SHIFT) & 0b10000000) != 0;
    if (isSprinting) translation *= 2;
    
    auto transform = gameObject()->localTransform();
    transform->Translate(gameObject()->localTransform()->orientation().Inverse().Apply(translation));
    transform->SetPosition({ transform->position()[0], 1, transform->position()[2] });

    footsteps->source()->SetSource(isSprinting ? "Audio/footstep-grass-clipped.wav"s : "Audio/footstep-grass.wav");
    panting->source()->SetSource(isSprinting ? "Audio/panting-clipped.wav"s : "Audio/panting.wav"s);
    bool playFootsteps = translation.LengthSquared() > .2f * delta;
    if (playFootsteps)
    {
        if (!footsteps->source()->IsPlaying()) footsteps->source()->Play(true);
        if (!panting->source()->IsPlaying()) panting->source()->Play(true);
    }
    else if (!playFootsteps)
    {
        if (footsteps->source()->IsPlaying()) footsteps->source()->SetLoop(false);
        if (panting->source()->IsPlaying()) panting->source()->SetLoop(false);
    }

    age += delta;
}

void PlayerControlsComponent::UpdateGraphics()
{
    gameObject()->localTransform()->SetOrientation(Quaternion<>(mouseDelta[1] * rotateSpeed, { 1, 0, 0 }));
    gameObject()->localTransform()->Rotate(mouseDelta[0] * rotateSpeed, { 0, 1, 0 });
}

void PlayerControlsComponent::HandleEvent(GlEngine::Events::Event &evt)
{
    auto kbEvt = dynamic_cast<GlEngine::Events::KeyboardEvent*>(&evt);
    if (kbEvt != nullptr)
    {
        if (kbEvt->type() == GlEngine::Events::KeyboardEventType::KeyPressed)
        {
            this->keysDown[kbEvt->GetVirtualKeyCode()] = true;
            if (kbEvt->GetVirtualKeyCode() == VK_SPACE) FindPage();
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
}

void PlayerControlsComponent::Render(GlEngine::RenderStage *stage)
{
    GameComponent::Render(stage);
    std::string text;
    if (age < 5000)
    {
        text = "Collect all 8 pages"s;
        //TODO: Render text in center of screen
    }
    else
    {
        text = renderText;
        //TODO: Render text at bottom left corner of screen
    }
}

void PlayerControlsComponent::GameObjectChanged()
{
    if (music->gameObject() != nullptr) music->gameObject()->RemoveComponent(music);
    if (gameObject() != nullptr)
    {
        gameObject()->AddComponent(music);
        gameObject()->AddComponent(footsteps);
        gameObject()->AddComponent(panting);
        gameObject()->AddComponent(staticsfx);
    }
}

void PlayerControlsComponent::FindPage()
{
    pagesFound++;
    std::stringstream stream;
    stream << "Pages: " << pagesFound << " of 8";
    renderText = stream.str();
    UpdateMusic();
}
void PlayerControlsComponent::UpdateMusic()
{
    std::string source;
    switch (pagesFound)
    {
    case 0:
    default:
        source = ""s;
        break;
    case 1:
    case 2:
        source = "Audio/slender01.wav";
        break;
    case 3:
    case 4:
        source = "Audio/slender02.wav";
        break;
    case 5:
    case 6:
        source = "Audio/slender03.wav";
        break;
    case 7:
        source = "Audio/slender04.wav";
        break;
    }
    music->source()->SetSource(source);
    if (!GlEngine::Util::is_empty_or_ws(source)) music->source()->Play(true);
}
