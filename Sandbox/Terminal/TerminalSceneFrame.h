#pragma once

#include "Frame.h"
#include "FrameStack.h"
#include "Event.h"

namespace FIG
{
    class FontRenderer;
}

class TerminalSceneFrame : public GlEngine::Frame
{
public:
    TerminalSceneFrame(Frame *wrapFrame);
    ~TerminalSceneFrame();

    virtual bool Initialize() override;

    virtual void Tick(float delta) override;

    virtual void HandleEvent(GlEngine::Events::Event &evt) override;

    virtual void TickGraphics(float delta);
    virtual void UpdateGraphics();
    virtual void Render(GlEngine::RenderStage* stage);

    virtual Vector<3> clearColor() override;

private:
    Frame *wrappedFrame;
    bool showTerminal, pauseWhenVisible;

    std::vector<std::string> *lines;
    std::string currentLine;
    unsigned cursorPos;
    float cursorBlinkDelta;

    FIG::FontRenderer* renderer;
};
