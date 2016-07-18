#pragma once

#include "IComponent.h"
#include "Threading.h"

namespace GlEngine
{
    class Window;

    class ENGINE_SHARED WindowManager : public IComponent
    {
    private:
        WindowManager();
        ~WindowManager();

        static WindowManager _instance;

    public:
        static constexpr WindowManager &GetInstance()
        {
            return _instance;
        }

        bool Initialize();
        void Shutdown();

        const char *name() override;

        Window *Create(unsigned targetFPS = 60u);
        Window *Find(HWND handle);
        void Destroy(Window *window);
        void Destroy(HWND handle);

        inline rt_mutex &GetMutex()
        {
            return _mutex;
        }

    private:
        rt_mutex _mutex;
    };
}
