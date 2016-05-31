#include "stdafx.h"
#include "GameLoop.h"

namespace GlEngine
{
    GameLoop::GameLoop(std::function<void(float)> updateFn, unsigned targetFPS)
    {
        this->updateFn = updateFn;
        this->targetFPS = targetFPS;
    }
    GameLoop::~GameLoop()
    {
    }

    void GameLoop::RunLoop()
    {
        if (!TestSetLock(running, mutex, [&] { stopping = false; })) return; //The loop is already running on a different thread
        loopThread = std::thread(GetThreadEntryPoint());
    }
    void GameLoop::StopLoop()
    {
        LockSet(stopping, true, mutex);
    }

    bool GameLoop::IsRunning()
    {
        return LockGet(running, mutex);
    }
    bool GameLoop::IsStopping()
    {
        return LockGet(stopping, mutex);
    }
    bool GameLoop::IsStopped()
    {
        return !IsRunning();
    }

    unsigned GameLoop::GetTargetFPS()
    {
        return LockGet(targetFPS, mutex);
    }
    void GameLoop::SetTargetFPS(unsigned target)
    {
        return LockSet(targetFPS, target, mutex);
    }

    std::function<void()> GameLoop::GetThreadEntryPoint()
    {
        return [this] { this->Loop(); };
    }
    void GameLoop::Loop()
    {
        unsigned target_fps;
        auto lastTickStart = std::chrono::high_resolution_clock::now();
        auto deltaCorrection = 0ns;

        while (!LockGet(stopping, mutex))
        {
            auto thisTickStart = std::chrono::high_resolution_clock::now();
            auto delta = std::chrono::duration_cast<std::chrono::duration<float>>(thisTickStart - lastTickStart).count();

            this->updateFn(delta);

            target_fps = LockGet(targetFPS, mutex);
            if (target_fps > 0)
            {
                auto sleepTo = thisTickStart + (1000ms / target_fps) - deltaCorrection;
                std::this_thread::sleep_until(sleepTo);
                deltaCorrection = std::chrono::high_resolution_clock::now() - sleepTo;
            }
            lastTickStart = thisTickStart;
        }

        ReleaseLock(running, mutex);
    }
}
