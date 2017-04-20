#pragma once

#include "GameLoop.h"
#include "IInitializable.h"
#include "EventQueue.h"

namespace GlEngine
{
    class FrameStack;

    class QuickLaunchLoop : public GlEngine::GameLoop, public GlEngine::IInitializable
    {
    public:
        QuickLaunchLoop(unsigned targetFPS = 200u);
        ~QuickLaunchLoop();

        void SetInitialFrame(Frame *frame);

        virtual bool Initialize() override;
        virtual void Shutdown() override;

        virtual std::string name() override;

        GlEngine::FrameStack *frames();

    private:
        bool initLoop();
        void loopBody(float delta);
        void shutdownLoop();

        GlEngine::Events::EventQueue localQueue;
        void copyRemoteQueue();
        void handleEvents();

        Frame *_initialFrame;
        FrameStack *_frames;
    };
}
