#include "stdafx.h"
#include "Engine.h"
#include "KeyboardEvent.h"
#include "MouseEvent.h"
#include "Environment.h"

namespace GlEngine
{
    int lastMouseX, lastMouseY;

    LRESULT CALLBACK Window::WndProc(unsigned message, WPARAM wParam, LPARAM lParam)
    {
        auto &events = Engine::GetInstance().GetEventQueue();
        unsigned vkCode;
        bool ctrl, shift, alt;
        Vector<2> size;

        if (GetFocus() != _windowHandle)
        {
            goto default_wnd_proc;
        }

        switch (message)
        {
        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        case WM_CLOSE:
            PostQuitMessage(0);
            break;

        case WM_SETCURSOR:
            if (LOWORD(lParam) == HTCLIENT)
            {
                SetCursor(nullptr);
                break;
            }
            goto default_wnd_proc;

        case WM_SIZE:
            size = Vector<2>(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
            if ((unsigned)size[0] != _width || (unsigned)size[1] != _height)
            {
                _width = (unsigned)size[0];
                _height = (unsigned)size[1];
                ShaderFactory::Environment::GetInstance().SetScreenDimensions({ _width, _height });
                _lastResizeTime = std::chrono::high_resolution_clock::now();
                // TODO events.PushEvents(new Events::SizeEvent(...));
            }
            goto default_wnd_proc;

        case WM_KEYDOWN:
            vkCode = (unsigned)wParam;
            if (vkCode == VK_F11)
            {
                SetFullscreen(!GetFullscreen());
                break;
            }
            ctrl = (GetKeyState(VK_CONTROL) & 0b10000000) != 0;
            shift = (GetKeyState(VK_SHIFT) & 0b10000000) != 0;
            alt = (GetKeyState(VK_ALT) & 0b10000000) != 0;
            if ((lParam & (1 << 30)) == 0) events.PushEvent(new Events::KeyboardEvent(vkCode, Events::KeyboardEventType::KeyPressed, ctrl, shift, alt));
            events.PushEvent(new Events::KeyboardEvent(vkCode, Events::KeyboardEventType::KeyTyped, ctrl, shift, alt));
            break;

        case WM_KEYUP:
            vkCode = (unsigned)wParam;
            ctrl = (GetKeyState(VK_CONTROL) & 0b10000000) != 0;
            shift = (GetKeyState(VK_SHIFT) & 0b10000000) != 0;
            alt = (GetKeyState(VK_ALT) & 0b10000000) != 0;
            events.PushEvent(new Events::KeyboardEvent(vkCode, Events::KeyboardEventType::KeyReleased, ctrl, shift, alt));
            break;

        case WM_MOUSEMOVE:
        case WM_LBUTTONDOWN:
        case WM_LBUTTONUP:
        case WM_MBUTTONDOWN:
        case WM_MBUTTONUP:
        case WM_RBUTTONDOWN:
        case WM_RBUTTONUP:
            {
                shift = (wParam & MK_SHIFT) > 0;
                ctrl = (wParam & MK_CONTROL) > 0;
                alt = (GetKeyState(VK_MENU) & ~1) > 0;
                Events::MouseButton btn = Events::MouseButton::None;
                if (message == WM_LBUTTONDOWN || message == WM_LBUTTONUP) btn |= Events::MouseButton::Left;
                if (message == WM_MBUTTONDOWN || message == WM_MBUTTONUP) btn |= Events::MouseButton::Middle;
                if (message == WM_RBUTTONDOWN || message == WM_RBUTTONUP) btn |= Events::MouseButton::Right;
                if (message == WM_XBUTTONDOWN || message == WM_XBUTTONUP) btn |= (HIWORD(wParam) == 0x0001) ? Events::MouseButton::X1 : Events::MouseButton::X2;
                auto type = (message == WM_LBUTTONDOWN || message == WM_MBUTTONDOWN || message == WM_RBUTTONDOWN) ? Events::MouseEventType::Pressed :
                                                                                        (message == WM_MOUSEMOVE)  ? Events::MouseEventType::Moved :
                                                                                                                    Events::MouseEventType::Released;
                auto mousePos = Vector<2>(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
                
                RECT rect = { NULL };
                GetWindowRect(_windowHandle, &rect);               
                POINT center = { (rect.left + rect.right) / 2, (rect.top + rect.bottom) / 2 };
                
                ScreenToClient(_windowHandle, &center);
                auto mouseRel = _centerCursor ? mousePos - Vector<2>(center.x, center.y) : Vector<2>(mousePos[0] - lastMouseX, mousePos[1] - lastMouseY);
            
                if (mouseRel[0] || mouseRel[1])
                    Util::Log("%f, %f, %f, %f", mousePos[0], mousePos[1], mouseRel[0], mouseRel[1]);

                events.PushEvent(new Events::MouseEvent(mousePos, mouseRel, ctrl, shift, alt, type, btn));
                
                if (type == Events::MouseEventType::Moved)
                {
                    lastMouseX = GET_X_LPARAM(lParam);
                    lastMouseY = GET_Y_LPARAM(lParam);
                }

                if (message == WM_MOUSEMOVE && _centerCursor)
                {
                    ClientToScreen(_windowHandle, &center);
                    SetCursorPos(center.x, center.y);
                }
            }
            break;

        //case WM_MOUSEWHEEL:

        //    break;

        default:
        default_wnd_proc:
            return DefWindowProc(_windowHandle, message, wParam, lParam);
        }
        return 0;
    }
}
