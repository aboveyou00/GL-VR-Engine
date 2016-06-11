#include "stdafx.h"
#include "Window.h"

namespace GlEngine
{
    Window::Window()
    {
    }
    Window::~Window()
    {
    }

    bool Window::Initialize()
    {
        unsigned posX, posY;
        CenterCoords(posX, posY);

        _windowHandle = CreateWindowEx(WS_EX_APPWINDOW,
                                       WINDOW_CLASS_NAME,
                                       WINDOW_INITIAL_TITLE,
                                       WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP,
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
        //Show();
        ShowCursor(false);

        return true;
    }
    void Window::Shutdown()
    {
        if (_windowHandle == nullptr) return;

        ShowCursor(true);

        SetFullscreen(false);
        if (_fullscreen) ChangeDisplaySettings(nullptr, 0);

        DestroyWindow(_windowHandle);
        _windowHandle = nullptr;
    }

    void Window::CenterWindow()
    {
        unsigned posX, posY;
        CenterCoords(posX, posY);

        SetWindowPos(_windowHandle, nullptr, posX, posY, _width, _height, SWP_NOZORDER);
    }

    bool Window::SetFullscreen(bool fullscreen, unsigned width, unsigned height)
    {
        if (_windowHandle != nullptr)
        {
            if (_fullscreen != fullscreen)
            {
                if (fullscreen)
                {
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
                        width = (width == 0) ? _width : width;
                        height = (height == 0) ? _height : height;
                    }
                    else CenterWindow();
                }
                else ChangeDisplaySettings(nullptr, 0);
                _fullscreen = fullscreen;
            }

            if (!_fullscreen && (width != _width || height != _height))
            {
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
