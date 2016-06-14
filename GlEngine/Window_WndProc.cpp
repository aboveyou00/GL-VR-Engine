#include "stdafx.h"
#include "Engine.h"
#include "KeyboardEvent.h"
#include "MouseEvent.h"

namespace GlEngine
{
    LRESULT CALLBACK Window::WndProc(unsigned message, WPARAM wParam, LPARAM lParam)
    {
        auto &events = Engine::GetInstance().GetEventQueue();
        unsigned vkCode;
        switch (message)
        {
        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        case WM_CLOSE:
            PostQuitMessage(0);
            break;

        case WM_KEYDOWN:
            vkCode = (unsigned)wParam;
            if (lParam & (1 << 30)) events.PushEvent(new Events::KeyboardEvent(vkCode, Events::KeyboardEventType::KeyPressed));
            events.PushEvent(new Events::KeyboardEvent(vkCode, Events::KeyboardEventType::KeyTyped));
            break;

        case WM_KEYUP:
            vkCode = (unsigned)wParam;
            events.PushEvent(new Events::KeyboardEvent(vkCode, Events::KeyboardEventType::KeyReleased));
            break;

        case WM_MBUTTONDOWN:
        case WM_MBUTTONUP:
            {
                auto mousePos = Vector<2>(LOWORD(lParam), HIWORD(lParam));
                bool shift = (wParam & MK_SHIFT) > 0,
                    control = (wParam & MK_CONTROL) > 0,
                    alt = (GetKeyState(VK_MENU) & ~1) > 0;
                Events::MouseButton btn = Events::MouseButton::None;
                if ((wParam & MK_LBUTTON) > 0) btn |= Events::MouseButton::Left;
                if ((wParam & MK_RBUTTON) > 0) btn |= Events::MouseButton::Right;
                if ((wParam & MK_MBUTTON) > 0) btn |= Events::MouseButton::Middle;
                if ((wParam & MK_XBUTTON1) > 0) btn |= Events::MouseButton::X1;
                if ((wParam & MK_XBUTTON2) > 0) btn |= Events::MouseButton::X2;
                auto type = (message == WM_MBUTTONDOWN) ? Events::MouseEventType::Pressed : Events::MouseEventType::Released;
                events.PushEvent(new Events::MouseEvent(mousePos, control, shift, alt, type, btn));
            }
            break;

        case WM_MOUSEMOVE:

            break;

        //case WM_MBUTTONDBLCLK:

        //    break;

        //case WM_MOUSEWHEEL:

        //    break;

        default:
            return DefWindowProc(_windowHandle, message, wParam, lParam);
        }
        return 0;
    }
}
