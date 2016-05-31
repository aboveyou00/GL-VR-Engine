#include "stdafx.h"
#include "Engine.h"

namespace GlEngine
{
    LRESULT CALLBACK Window::WndProc(unsigned message, WPARAM wParam, LPARAM lParam)
    {
        switch (message)
        {
        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        case WM_CLOSE:
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProc(_windowHandle, message, wParam, lParam);
        }
        return 0;
    }
}
