#include "stdafx.h"
#include "Window.h"
#include "Environment.h"

namespace GlEngine
{
    Window::Window()
        : _lastResizeTime(std::chrono::high_resolution_clock::now())
    {
    }
    Window::~Window()
    {
    }

    bool Window::Initialize()
    {
        unsigned posX, posY;
        CenterCoords(posX, posY);

        DWORD style = WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP;
        if (!_fullscreen) style |= WS_OVERLAPPEDWINDOW;

        _windowHandle = CreateWindowEx(WS_EX_APPWINDOW,
                                       WINDOW_CLASS_NAME,
                                       WINDOW_INITIAL_TITLE,
                                       style,
                                       posX,
                                       posY,
                                       _width,
                                       _height,
                                       nullptr,
                                       nullptr,
                                       GetModuleHandle(nullptr),
                                       nullptr);

        if (!_windowHandle)
        {
            if (_fullscreen) ChangeDisplaySettings(nullptr, 0);
            return false;
        }

        _visible = false;

        ShaderFactory::Environment::GetInstance().SetScreenDimensions({ _width, _height });
        return true;
    }
    void Window::Shutdown()
    {
        if (_windowHandle == nullptr) return;

        SetFullscreen(false);
        if (_fullscreen) ChangeDisplaySettings(nullptr, 0);

        DestroyWindow(_windowHandle);
        _windowHandle = nullptr;
    }

    std::string Window::name()
    {
        return "Window";
    }

    void Window::CenterWindow()
    {
        unsigned posX, posY;
        CenterCoords(posX, posY);

        SetWindowPos(_windowHandle, nullptr, posX, posY, _width, _height, SWP_NOZORDER | SWP_FRAMECHANGED);
    }

    bool Window::SetFullscreen(bool fullscreen, unsigned width, unsigned height)
    {
        auto origWidth = _width,
             origHeight = _height;
        if (_windowHandle != nullptr)
        {
            if (_fullscreen != fullscreen)
            {
                auto style = GetWindowLong(_windowHandle, GWL_STYLE);
                if (fullscreen)
                {
                    SetWindowLong(_windowHandle, GWL_STYLE, style & ~WS_OVERLAPPEDWINDOW);

                    auto screenWidth = GetSystemMetrics(SM_CXSCREEN);
                    auto screenHeight = GetSystemMetrics(SM_CYSCREEN);

                    DEVMODE screenSettings;
                    memset(&screenSettings, 0, sizeof(screenSettings));
                    screenSettings.dmSize = sizeof(screenSettings);

                    screenSettings.dmBitsPerPel = 32;
                    screenSettings.dmPelsWidth = _width = (DWORD)screenWidth;
                    screenSettings.dmPelsHeight = _height = (DWORD)screenHeight;

                    screenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

                    if (ChangeDisplaySettings(&screenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
                    {
                        fullscreen = false;
                    }
                    else CenterWindow();
                }
                if (!fullscreen)
                {
                    ChangeDisplaySettings(nullptr, 0);
                    SetWindowLong(_windowHandle, GWL_STYLE, style | WS_OVERLAPPEDWINDOW);
                    SetWindowPos(_windowHandle, nullptr, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER);
                    width = (width == 0) ? _width : width;
                    height = (height == 0) ? _height : height;
                }
                _fullscreen = fullscreen;
            }

            if (!_fullscreen && (width != origWidth || height != origHeight))
            {
                _lastResizeTime = std::chrono::high_resolution_clock::now();
                SetWindowPos(_windowHandle, nullptr, 0, 0, width, height, SWP_NOMOVE | SWP_NOZORDER);
            }
        }
        else
        {
            _fullscreen = fullscreen;
            _width = width;
            _height = height;
        }
        return true;
    }
    void Window::SetSize(unsigned width, unsigned height)
    {
        SetFullscreen(false, width, height);
    }
    void Window::SetWidth(unsigned width)
    {
        SetFullscreen(false, width, _height);
    }
    void Window::SetHeight(unsigned height)
    {
        SetFullscreen(false, _width, height);
    }
    void Window::SetTargetFPS(unsigned targetFPS)
    {
        _targetFPS = targetFPS;
    }

    bool Window::GetFullscreen()
    {
        return _fullscreen;
    }
    unsigned Window::GetWidth()
    {
        return _width;
    }
    unsigned Window::GetHeight()
    {
        return _height;
    }
    unsigned Window::GetTargetFPS()
    {
        return _targetFPS;
    }

    time_point Window::GetLastResizeTime()
    {
        return _lastResizeTime;
    }

    bool Window::GetVisible()
    {
        return _visible;
    }
    void Window::SetVisible(bool visible)
    {
        if (_visible != visible)
        {
            ShowWindow(_windowHandle, visible ? SW_SHOW : SW_HIDE);
            _visible = visible;
        }
    }
    void Window::Show()
    {
        SetVisible(true);
        SetForegroundWindow(_windowHandle);
        SetFocus(_windowHandle);
    }
    void Window::Hide()
    {
        SetVisible(false);
    }

    HWND Window::GetHandle()
    {
        return _windowHandle;
    }

    HDC Window::GetDeviceContext()
    {
        return GetDC(GetHandle());
    }

    void Window::CenterCoords(unsigned &posX, unsigned &posY)
    {
        auto screenWidth = GetSystemMetrics(SM_CXSCREEN);
        auto screenHeight = GetSystemMetrics(SM_CYSCREEN);

        posX = (screenWidth / 2) - (_width / 2);
        posY = (screenHeight / 2) - (_height / 2);
    }
}
