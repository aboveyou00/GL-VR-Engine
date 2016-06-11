#pragma once

#include "IComponent.h"

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

        Window *Create(unsigned targetFPS = 60u);
        Window *Find(HWND handle);
        void Destroy(Window *window);
        void Destroy(HWND handle);
    };
}
