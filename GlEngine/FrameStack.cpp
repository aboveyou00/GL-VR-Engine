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
        for (auto q = stackIdx; q >= 0; q--)
        {
            _frameStack[q]->Shutdown();
        }
    }
    void FrameStack::Tick(float delta)
    {
        if (stackIdx != -1) _frameStack[stackIdx]->Tick(delta);
    }

    const char *FrameStack::name()
    {
        return "FrameStack";
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

    void FrameStack::Update(GraphicsContext &ctx)
    {
        if (stackIdx == -1) return;
        _frameStack[stackIdx]->Update(ctx);
    }

    void FrameStack::HandleEvent(Events::Event &evt)
    {
        if (evt.IsHandled()) return;
        if (stackIdx == -1) return;
        _frameStack[stackIdx]->HandleEvent(evt);
    }
}
