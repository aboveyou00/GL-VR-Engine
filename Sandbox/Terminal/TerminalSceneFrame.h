#pragma once

#include "Frame.h"
#include "FrameStack.h"
#include "Event.h"
#include "ScriptEvaluator.h"

namespace FIG
{
    class FontRenderer;
}

class TerminalSceneFrame : public GlEngine::Frame
{
public:
    TerminalSceneFrame(Frame *wrapFrame, GlEngine::ScriptEvaluator* evaluator = nullptr);
    ~TerminalSceneFrame();

    virtual bool Initialize() override;

    virtual void Tick(float delta) override;

    virtual void HandleEvent(GlEngine::Events::Event &evt) override;

    virtual void TickGraphics(float delta);
    virtual void UpdateGraphics();
    virtual void Render(GlEngine::RenderStage* stage);

    virtual Vector<3> clearColor() override;

    template<typename EvaluatorT>
    void CreateEvaluator()
    {
        static_assert(std::is_base_of<GlEngine::ScriptEvaluator, EvaluatorT>::value, "EvaluatorT not derived from ScriptEvaluator");
        evaluator = new EvaluatorT(wrappedFrame);
    }

private:
    Frame *wrappedFrame;
    bool showTerminal, pauseWhenVisible;

    std::vector<std::string> *lines;
    std::string currentLine;
    unsigned cursorPos, selectionStartPos;
    float cursorBlinkDelta;

    FIG::FontRenderer* renderer;

    void deleteSelection(std::string replace = ""s);
    std::string getSelection();

    std::string getClipboardContents();
    void setClipboardContents(std::string contents);

    GlEngine::ScriptEvaluator* evaluator;
    void Execute(std::string line);
};
