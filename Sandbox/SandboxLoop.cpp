#include "stdafx.h"
#include "SandboxLoop.h"
#include "Lab01_Diffuse/DiffuseSceneFrame.h"
#include "Lab02_Features/FeaturesSceneFrame.h"
#include "Lab03_LightsAndEffects/LightsAndEffectsSceneFrame.h"
#include "Lab04_Textures/TexturesSceneFrame.h"
#include "Lab05_Geometry/GeometrySceneFrame.h"
#include "Lab06_Distortion/DistortionSceneFrame.h"
#include "Lab07_Particles/ParticlesSceneFrame.h"
#include "Lab08_Slenderman/SlendermanStaticSceneFrame.h"
#include "Lab09_Spatpart/SpatpartSceneFrame.h"
#include "Terminal/TerminalSceneFrame.h"

#include "Engine.h"
#include "Event.h"
#include "AudioController.h"
#include "ServiceProvider.h"
#include "ILogger.h"
#include "PythonEvaluator.h"

SandboxLoop::SandboxLoop(unsigned targetFPS)
    : GlEngine::GameLoop(
        [&] { return this->initLoop(); },
        [&](float delta) { return this->loopBody(delta); },
        [&] { return this->shutdownLoop(); },
        targetFPS
      )
{
}
SandboxLoop::~SandboxLoop()
{
}

bool SandboxLoop::Initialize()
{
    RunLoop();
    return true;
}
void SandboxLoop::Shutdown()
{
    StopLoop();
    Join();
}

std::string SandboxLoop::name()
{
    return "SandboxLoop";
}

GlEngine::FrameStack *SandboxLoop::frames()
{
    return &_frames;
}

bool SandboxLoop::initLoop()
{
    this_thread_name() = "logic";
    this_thread_type() = ThreadType::Logic;

    auto logger = GlEngine::Engine::GetInstance().GetServiceProvider().GetService<GlEngine::ILogger>();
    logger->Log(GlEngine::LogType::Info, "Beginning logic thread");

    if (!_frames.Initialize()) return false;

    _frames.PushNewFrame<DiffuseSceneFrame>();
    auto terminal = _frames.PushNewFrame<TerminalSceneFrame>(_frames.CurrentFrame());
    terminal->CreateEvaluator<GlEngine::PythonEvaluator>();

    return true;
}
void SandboxLoop::loopBody(float delta)
{
    handleEvents();
    _frames.Tick(delta);
    GlEngine::Engine::GetInstance().GetAudioController().Tick(0); //We don't need a delta here, YSE worries about its own timing
}
void SandboxLoop::shutdownLoop()
{
    auto logger = GlEngine::Engine::GetInstance().GetServiceProvider().GetService<GlEngine::ILogger>();
    logger->Log(GlEngine::LogType::Info, "~Terminating logic thread");

    _frames.Shutdown();
    GlEngine::Engine::GetInstance().GetAudioController().Shutdown();
}

void SandboxLoop::copyRemoteQueue()
{
    auto &engine = GlEngine::Engine::GetInstance();
    ScopedLock _lock(engine.GetMutex());

    auto &remoteQueue = engine.GetEventQueue();
    GlEngine::Events::Event *evt;
    while ((evt = remoteQueue.RemoveEvent()) != nullptr)
        localQueue.PushEvent(evt);
}
void SandboxLoop::handleEvents()
{
    copyRemoteQueue();
    GlEngine::Events::Event *evt;
    while ((evt = localQueue.RemoveEvent()) != nullptr)
    {
        _frames.HandleEvent(*evt);
        delete evt;
    }
}
