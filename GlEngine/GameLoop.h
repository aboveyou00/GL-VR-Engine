#pragma once

namespace GlEngine
{
    class ENGINE_SHARED GameLoop
    {
    public:
        GameLoop(std::function<void(float)> updateFn, unsigned targetFPS = 60u);
        ~GameLoop();

        void RunLoop();
        void StopLoop();

        bool IsRunning();
        bool IsStopping();
        bool IsStopped();

        unsigned GetTargetFPS();
        void SetTargetFPS(unsigned target);

    private:
        std::function<void(float)> updateFn;
        unsigned targetFPS = 60;
        bool running = false, stopping = false;
        std::mutex mutex;
        std::thread loopThread;

        std::function<void()> GetThreadEntryPoint();
        void Loop();
    };
}
