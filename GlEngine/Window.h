#pragma once

#include "IInitializable.h"

static const wchar_t *const WINDOW_CLASS_NAME = L"GlEngine::Window";
static const wchar_t *const WINDOW_INITIAL_TITLE = L"GlEngine";

static const unsigned DEFAULT_WINDOW_WIDTH = 800;
static const unsigned DEFAULT_WINDOW_HEIGHT = 600;

using time_point = std::chrono::high_resolution_clock::time_point;

namespace GlEngine
{
    class ENGINE_SHARED Window : public IInitializable
    {
    public:
        Window();
        ~Window();

        virtual bool Initialize() override;
        virtual void Shutdown() override;

        virtual std::string name() override;

        void CenterWindow();

        bool SetFullscreen(bool fullscreen, unsigned width = DEFAULT_WINDOW_WIDTH, unsigned height = DEFAULT_WINDOW_HEIGHT);
        void SetSize(unsigned width, unsigned height);
        void SetWidth(unsigned width);
        void SetHeight(unsigned height);
        void SetTargetFPS(unsigned targetFPS);
        void SetCenterCursor(bool centerCursor);

        bool GetFullscreen();
        unsigned GetWidth();
        unsigned GetHeight();
        unsigned GetTargetFPS();
        time_point GetLastResizeTime();
        bool GetCenterCursor();

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
        bool _centerCursor = false;
        unsigned _width = DEFAULT_WINDOW_WIDTH, _height = DEFAULT_WINDOW_HEIGHT;

        std::chrono::high_resolution_clock::time_point _lastResizeTime;

        void CenterCoords(unsigned &posX, unsigned &posY);
    };
}
