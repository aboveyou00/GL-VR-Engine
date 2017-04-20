#include "stdafx.h"
#include "QuickLaunchLoop.h"
#include "FrameStack.h"

#include "Engine.h"
#include "Event.h"
#include "AudioController.h"
#include "ServiceProvider.h"
#include "ILogger.h"
//#include "PythonEvaluator.h"

namespace GlEngine
{
    QuickLaunchLoop::QuickLaunchLoop(unsigned targetFPS)
        : GameLoop(
            [&] { return this->initLoop(); },
            [&](float delta) { return this->loopBody(delta); },
            [&] { return this->shutdownLoop(); },
            targetFPS
          ),
          _initialFrame(nullptr),
          _frames(new FrameStack())
    {
    }
    QuickLaunchLoop::~QuickLaunchLoop()
    {
    }

    void QuickLaunchLoop::SetInitialFrame(Frame *frame)
    {
        _initialFrame = frame;
    }

    bool QuickLaunchLoop::Initialize()
    {
        RunLoop();
        return true;
    }
    void QuickLaunchLoop::Shutdown()
    {
        StopLoop();
        Join();
    }

    std::string QuickLaunchLoop::name()
    {
        return "QuickLaunchLoop";
    }

    GlEngine::FrameStack *QuickLaunchLoop::frames()
    {
        return _frames;
    }

    bool QuickLaunchLoop::initLoop()
    {
        this_thread_name() = "logic";
        this_thread_type() = ThreadType::Logic;

        auto logger = GlEngine::Engine::GetInstance().GetServiceProvider().GetService<GlEngine::ILogger>();
        logger->Log(GlEngine::LogType::Info, "Beginning logic thread");

        if (!_frames->Initialize()) return false;

        _frames->PushFrame(_initialFrame);
        //auto terminal = _frames->PushNewFrame<TerminalSceneFrame>(_frames.CurrentFrame());
        //terminal->CreateEvaluator<GlEngine::PythonEvaluator>();

        return true;
    }
    void QuickLaunchLoop::loopBody(float delta)
    {
        handleEvents();
        _frames->Tick(delta);
        GlEngine::Engine::GetInstance().GetAudioController().Tick(0); //We don't need a delta here, YSE worries about its own timing
    }
    void QuickLaunchLoop::shutdownLoop()
    {
        auto logger = GlEngine::Engine::GetInstance().GetServiceProvider().GetService<GlEngine::ILogger>();
        logger->Log(GlEngine::LogType::Info, "~Terminating logic thread");

        _frames->Shutdown();
        GlEngine::Engine::GetInstance().GetAudioController().Shutdown();
    }

    void QuickLaunchLoop::copyRemoteQueue()
    {
        auto &engine = GlEngine::Engine::GetInstance();
        ScopedLock _lock(engine.GetMutex());

        auto &remoteQueue = engine.GetEventQueue();
        GlEngine::Events::Event *evt;
        while ((evt = remoteQueue.RemoveEvent()) != nullptr)
            localQueue.PushEvent(evt);
    }
    void QuickLaunchLoop::handleEvents()
    {
        copyRemoteQueue();
        GlEngine::Events::Event *evt;
        while ((evt = localQueue.RemoveEvent()) != nullptr)
        {
            _frames->HandleEvent(*evt);
            delete evt;
        }
    }
}
