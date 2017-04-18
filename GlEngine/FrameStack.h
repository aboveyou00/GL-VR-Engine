#pragma once

#include "GameLoop.h"
#include "IInitializable.h"
#include "ICamera.h"
#include "RenderPipeline.h"

namespace GlEngine
{
    class Frame;
    namespace Events
    {
        class Event;
    }

    class ENGINE_SHARED FrameStack : public IInitializable, public RenderPipeline
    {
    public:
        FrameStack();
        ~FrameStack();

        friend class Frame;

        virtual bool Initialize() override;
        virtual void Shutdown() override;

        virtual std::string name() override;

        void Tick(float delta);

        template <typename T, typename... TArgs>
        void PushNewFrame(TArgs... args)
        {
            T *t = new T(args...);
            //TODO: Log helpful error messages, don't crash program
            assert(stackIdx < MAX_FRAME_STACK_SIZE - 1);
            _frameStack[++stackIdx] = t;
            if (stackIdx != 0) _frameStack[stackIdx - 1]->FrameMasked(*this);
            t->FramePushed(*this);
            if (initialized)
            {
                bool result = t->Initialize();
                assert(result);
            }
        }
        void PopFrame();
        Frame *CurrentFrame();

        virtual void HandleEvent(Events::Event &evt);

        virtual std::vector<std::pair<RenderStage*, ICamera*>> renderStages() override;

        virtual Vector<3> clearColor() override;
        virtual void SetClearColor(Vector<3> color) override;

        virtual Frame *frame() override;

    private:
        static const int MAX_FRAME_STACK_SIZE = 32;
        Frame *_frameStack[MAX_FRAME_STACK_SIZE];
        int stackIdx = 0;
        bool initialized = false;
    };
}
