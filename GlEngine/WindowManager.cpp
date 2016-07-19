#include "stdafx.h"
#include "WindowManager.h"
#include "Engine.h"

namespace GlEngine
{
    WindowManager::WindowManager()
    {
    }
    WindowManager::~WindowManager()
    {
    }

    WindowManager WindowManager::_instance;

    LRESULT CALLBACK __WndProc(HWND windowHandle, unsigned message, WPARAM wParam, LPARAM lParam)
    {
        auto window = Engine::GetInstance().GetWindowManager().Find(windowHandle);
        if (!window) return DefWindowProc(windowHandle, message, wParam, lParam);
        return window->WndProc(message, wParam, lParam);
    }

    static const int MAX_WINDOWS = 12;
    static Window windows[MAX_WINDOWS];

    bool WindowManager::Initialize()
    {
        WNDCLASSEXW wcex;

        wcex.cbSize = sizeof(WNDCLASSEX);

        wcex.style          = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
        wcex.lpfnWndProc    = __WndProc;
        wcex.cbClsExtra     = 0;
        wcex.cbWndExtra     = 0;
        wcex.hInstance      = GetModuleHandle(nullptr);
        wcex.hIcon          = nullptr;
        wcex.hCursor        = nullptr;
        wcex.hbrBackground  = (HBRUSH)GetStockObject(BLACK_BRUSH);
        wcex.lpszMenuName   = nullptr;
        wcex.lpszClassName  = WINDOW_CLASS_NAME;
        wcex.hIconSm        = nullptr;

        if (!RegisterClassExW(&wcex)) return false;
        return true;
    }
    void WindowManager::Shutdown()
    {
        for (auto q = 0; q < MAX_WINDOWS; q++)
            Destroy(&windows[q]);
        UnregisterClass(WINDOW_CLASS_NAME, GetModuleHandle(nullptr));
    }

    const char *WindowManager::name()
    {
        return "WindowManager";
    }

    Window *WindowManager::Create(unsigned targetFPS)
    {
        for (auto q = 0; q < MAX_WINDOWS; q++)
            if (windows[q].GetHandle() == nullptr)
            {
                auto window = &windows[q];
                window->SetTargetFPS(targetFPS);
                if (!window->Initialize()) return nullptr;
                return window;
            }
        return nullptr;
    }
    Window *WindowManager::Find(HWND handle)
    {
        if (handle == nullptr) return nullptr;
        for (auto q = 0; q < MAX_WINDOWS; q++)
            if (windows[q].GetHandle() == handle) return &windows[q];
        return nullptr;
    }
    void WindowManager::Destroy(GlEngine::Window *window)
    {
        if (window == nullptr) return;
        if (window < windows || window >= windows + MAX_WINDOWS) return;
        window->Shutdown();
    }
    void WindowManager::Destroy(HWND handle)
    {
        Destroy(Find(handle));
    }
}
