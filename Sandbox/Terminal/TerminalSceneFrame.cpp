#include "stdafx.h"
#include "TerminalSceneFrame.h"
#include "KeyboardEvent.h"
#include "CharEvent.h"
#include "SimpleRenderPipeline.h"
#include "RenderStage.h"
#include "RenderTarget.h"
#include "FontRenderer.h"

typedef GlEngine::Events::KeyboardEvent KeyboardEvent;
typedef GlEngine::Events::KeyboardEventType KeyboardEventType;
typedef GlEngine::Events::CharEvent CharEvent;

TerminalSceneFrame::TerminalSceneFrame(Frame *wrapFrame)
    : wrappedFrame(wrapFrame), showTerminal(false), pauseWhenVisible(true), lines(new std::vector<std::string>()), currentLine(""s), cursorPos(0)
{
    lines->push_back("Hello, World!"s);
    lines->push_back("I like chocolate milk!"s);
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
    auto charevt = dynamic_cast<CharEvent*>(&evt);
    if (charevt != nullptr)
    {
        if (charevt->chr() == '`')
        {
            showTerminal = !showTerminal;
            charevt->Handle();
            return;
        }
    }

    if (showTerminal)
    {
        auto old = currentLine;
        auto kbdevt = dynamic_cast<KeyboardEvent*>(&evt);
        if (kbdevt != nullptr && kbdevt->type() == KeyboardEventType::KeyTyped)
        {
            auto vk_code = kbdevt->GetVirtualKeyCode();
            switch (vk_code)
            {
            case VK_UP:
            case VK_DOWN:
                //Ignore
                break;

            case VK_SHIFT:
                break;
            case VK_RETURN:
                lines->push_back(currentLine);
                currentLine = "";
                cursorPos = 0;
                break;
            case VK_DELETE:
                if (cursorPos < currentLine.length()) currentLine = currentLine.substr(0, cursorPos) + currentLine.substr(cursorPos + 1);
                break;

            case VK_HOME:
                cursorPos = 0;
                break;
            case VK_END:
                cursorPos = currentLine.length();
                break;
            case VK_RIGHT:
                cursorPos = min(currentLine.length(), cursorPos + 1);
                break;
            case VK_LEFT:
                cursorPos = max(0u, cursorPos - 1);
                break;
            }
        }
        else if (charevt != nullptr)
        {
            auto chr = charevt->chr();
            switch (chr)
            {
            case '\x08': //Backspace
                if (cursorPos > 0)
                {
                    currentLine = currentLine.substr(0, cursorPos - 1) + currentLine.substr(cursorPos);
                    cursorPos--;
                }
                break;

            default:
                currentLine = currentLine.substr(0, cursorPos) + std::string(1, chr) + currentLine.substr(cursorPos);
                cursorPos++;
            }
        }
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
    if (renderer != nullptr) return;
    renderer = new FIG::FontRenderer(new FIG::Font("/Windows/Fonts/consola.ttf"), FIG::FontRendererSettings(12));
}
void TerminalSceneFrame::Render(GlEngine::RenderStage *stage)
{
    if (stage == GlEngine::renderStage_opaque) this->currentRenderTarget->Render(wrappedFrame);
    if (showTerminal)
    {
        Frame::Render(stage);
        auto renderText = "> " + currentLine;
        Vector<4> color = { 0, 0, 0, 1 };
        Vector<4> bgColor = { 1, 1, 1, 1 };
        renderer->DrawDirect(10, 200, color.getAddr(), renderText.c_str());
    }
}

Vector<3> TerminalSceneFrame::clearColor()
{
    return wrappedFrame->clearColor();
}
