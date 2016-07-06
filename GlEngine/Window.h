#pragma once

#include "IComponent.h"

static const wchar_t *const WINDOW_CLASS_NAME = L"GlEngine::Window";
static const wchar_t *const WINDOW_INITIAL_TITLE = L"GlEngine";

static const unsigned DEFAULT_WINDOW_WIDTH = 800;
static const unsigned DEFAULT_WINDOW_HEIGHT = 600;

using time_point = std::chrono::high_resolution_clock::time_point;

namespace GlEngine
{
    class ENGINE_SHARED Window : public IComponent
    {
    public:
        Window();
        ~Window();

        bool Initialize() override;
        void Shutdown() override;

        void CenterWindow();

        bool SetFullscreen(bool fullscreen, unsigned width = DEFAULT_WINDOW_WIDTH, unsigned height = DEFAULT_WINDOW_HEIGHT);
        void SetSize(unsigned width, unsigned height);
        void SetWidth(unsigned width);
        void SetHeight(unsigned height);
        void SetTargetFPS(unsigned targetFPS);

        bool GetFullscreen();
        unsigned GetWidth();
        unsigned GetHeight();
        unsigned GetTargetFPS();
        time_point GetLastResizeTime();

        bool GetVisible();
        void SetVisible(bool visible);
        void Show();
        void Hide();

        HWND GetHandle();
		HDC GetDeviceContext();
        LRESULT CALLBACK WndProc(unsigned message, WPARAM wParam, LPARAM lParam);

    private:
        HWND _windowHandle;
        unsigned _targetFPS;
        bool _visible;

        bool _fullscreen = false;
        unsigned _width = DEFAULT_WINDOW_WIDTH, _height = DEFAULT_WINDOW_HEIGHT;

        std::chrono::high_resolution_clock::time_point _lastResizeTime;

        void CenterCoords(unsigned &posX, unsigned &posY);
    };
}
