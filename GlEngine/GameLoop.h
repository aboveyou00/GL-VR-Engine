#pragma once

namespace GlEngine
{
    class ENGINE_SHARED GameLoop
    {
    public:
        GameLoop(std::function<void(float)> updateFn, unsigned targetFPS = 60u);
        GameLoop(std::function<bool()> initializeFn, std::function<void(float)> updateFn, std::function<void()> shutdownFn = nullptr, unsigned targetFPS = 60u);
        ~GameLoop();

        void RunLoop();
        void StopLoop(bool async = true);

        bool IsRunning();
        bool IsStopping();
        bool IsStopped();

        void Join();

        unsigned GetTargetFPS();
        void SetTargetFPS(unsigned target);

    private:
        std::function<bool()> initializeFn;
        std::function<void(float)> updateFn;
        std::function<void()> shutdownFn;
        unsigned targetFPS = 60;
        bool running = false, stopping = false;
        rt_mutex mutex;
        std::thread loopThread;

        std::function<void()> GetThreadEntryPoint();
        void Loop();
    };
}
