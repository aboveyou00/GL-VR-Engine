#include "stdafx.h"
#include "FrameStack.h"
#include "Frame.h"
#include "Event.h"

namespace GlEngine
{
    FrameStack::FrameStack()
    {
        stackIdx = -1;
    }
    FrameStack::~FrameStack()
    {
    }

    bool FrameStack::Initialize()
    {
        if (initialized) return true;
        initialized = true;
        for (auto q = 0; q <= stackIdx; q++)
        {
            if (!_frameStack[q]->Initialize()) return false;
        }
        return true;
    }
    void FrameStack::Shutdown()
    {
        if (!initialized) return;
        initialized = false;
        for (auto q = stackIdx; q >= 0; q--)
        {
            _frameStack[q]->Shutdown();
        }
    }

    std::string FrameStack::name()
    {
        return "FrameStack";
    }

    void FrameStack::Tick(float delta)
    {
        if (stackIdx != -1) _frameStack[stackIdx]->Tick(delta);
    }

    void FrameStack::PushFrame(Frame *frame)
    {
        //TODO: Log helpful error messages, don't crash program
        assert(stackIdx < MAX_FRAME_STACK_SIZE - 1);
        _frameStack[++stackIdx] = frame;
        if (stackIdx != 0) _frameStack[stackIdx - 1]->FrameMasked(*this);
        frame->FramePushed(*this);
        if (initialized)
        {
            bool result = frame->Initialize();
            assert(result);
        }
    }
    void FrameStack::PopFrame()
    {
        //TODO: Log helpful error messages, don't crash program
        assert(stackIdx > -1);
        auto popped = _frameStack[stackIdx--];
        popped->FramePopped(*this);
        popped->Shutdown();
        if (stackIdx == -1) _frameStack[stackIdx]->FrameUnmasked(*this);
        if (initialized) popped->Shutdown();
    }
    Frame *FrameStack::CurrentFrame()
    {
        if (stackIdx == -1) return nullptr;
        return _frameStack[stackIdx];
    }

    void FrameStack::HandleEvent(Events::Event &evt)
    {
        if (evt.IsHandled()) return;
        if (stackIdx == -1) return;
        _frameStack[stackIdx]->HandleEvent(evt);
    }
    std::vector<std::pair<RenderStage*, ICamera*>> FrameStack::renderStages()
    {
        if (CurrentFrame() == nullptr) return { };
        return CurrentFrame()->renderStages();
    }

    Vector<3> FrameStack::clearColor()
    {
        if (CurrentFrame() == nullptr) return { 0, 0, 0 };
        return CurrentFrame()->clearColor();
    }
    void FrameStack::SetClearColor(Vector<3> color)
    {
        assert(false);
    }

    Frame *FrameStack::frame()
    {
        return CurrentFrame();
    }
}
