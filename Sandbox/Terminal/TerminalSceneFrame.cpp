#include "stdafx.h"
#include "TerminalSceneFrame.h"
#include "KeyboardEvent.h"
#include "SimpleRenderPipeline.h"
#include "RenderStage.h"
#include "RenderTarget.h"

typedef GlEngine::Events::KeyboardEvent KeyboardEvent;
typedef GlEngine::Events::KeyboardEventType KeyboardEventType;

TerminalSceneFrame::TerminalSceneFrame(Frame *wrapFrame)
    : wrappedFrame(wrapFrame), showTerminal(false), pauseWhenVisible(true)
{
}
TerminalSceneFrame::~TerminalSceneFrame()
{
}

bool TerminalSceneFrame::Initialize()
{
    if (!Frame::Initialize()) return false;

    auto pipeline = new GlEngine::SimpleRenderPipeline(this, { { GlEngine::renderStage_opaque, nullptr } });
    SetMainPipeline(pipeline);

    return true;
}

void TerminalSceneFrame::Tick(float delta)
{
    if (!showTerminal || !pauseWhenVisible) wrappedFrame->Tick(delta);
    Frame::Tick(delta);
}

void TerminalSceneFrame::HandleEvent(GlEngine::Events::Event &evt)
{
    Frame::HandleEvent(evt);
    if (evt.IsHandled()) return;
    auto kbdevt = dynamic_cast<KeyboardEvent*>(&evt);
    if (kbdevt != nullptr)
    {
        if (kbdevt->type() == KeyboardEventType::KeyTyped && kbdevt->GetVirtualKeyCode() == VK_OEM_3) showTerminal = !showTerminal;
    }

    if (showTerminal)
    {

        evt.Handle();
    }
    else
    {
        wrappedFrame->HandleEvent(evt);
    }
}

void TerminalSceneFrame::TickGraphics(float delta)
{
    wrappedFrame->TickGraphics(delta);
    Frame::TickGraphics(delta);
}
void TerminalSceneFrame::UpdateGraphics()
{
    wrappedFrame->UpdateGraphics();
    Frame::UpdateGraphics();
}
void TerminalSceneFrame::Render(GlEngine::RenderStage *stage)
{
    if (stage == GlEngine::renderStage_opaque) this->currentRenderTarget->Render(wrappedFrame);
    if (showTerminal) Frame::Render(stage);
}

Vector<3> TerminalSceneFrame::clearColor()
{
    return wrappedFrame->clearColor();
}
