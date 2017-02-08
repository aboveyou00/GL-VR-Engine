#pragma once

#include "GameLoop.h"
#include "IGameComponent.h"

namespace GlEngine
{
    class Frame;
    class GraphicsContext;
    namespace Events
    {
        class Event;
    }

    class ENGINE_SHARED FrameStack : IGameComponent
    {
    public:
        FrameStack();
        ~FrameStack();

        virtual bool Initialize() override;
        virtual void Shutdown() override;
        virtual void Tick(float delta) override;

        virtual std::string name() override;

        template <typename T, typename... TArgs>
        void PushNewFrame(TArgs... args)
        {
            T *t = new T(args...);
            //TODO: Log helpful error messages, don't crash program
            assert(stackIdx < MAX_FRAME_STACK_SIZE - 1);
            _frameStack[++stackIdx] = t;
            if (stackIdx != 0) _frameStack[stackIdx - 1]->FrameMasked(*this);
            t->FramePushed(*this);
            if (initialized) assert(t->Initialize());
        }
        void PopFrame();
        Frame *CurrentFrame();

        void Update(GraphicsContext &ctx);

        virtual void HandleEvent(Events::Event &evt);

    private:
        static const int MAX_FRAME_STACK_SIZE = 32;
        Frame *_frameStack[MAX_FRAME_STACK_SIZE];
        int stackIdx = 0;
        bool initialized = false;
    };
}
