#include "stdafx.h"
#include "OpenGlGraphicsAdapter.h"
#include "OpenGl.h"
#include "WindowsUtils.h"

namespace GlEngine::Adapters
{
    static bool LoadGlewExtensions();

    bool OpenGlGraphicsAdapter::MakeDefaultContext(HDC hdc)
    {
        auto _hglrc = wglCreateContext(hdc);
        if (_hglrc == nullptr)
        {
            Util::Log(LogType::ErrorC, "wglCreateContext failed: %s", Util::GetLastErrorAsString().c_str());
        }

        wglMakeCurrent(hdc, _hglrc);

        if (!LoadGlewExtensions()) return false;
        //wglMakeCurrent(nullptr, nullptr);
        return true;
    }

    static bool LoadGlewExtensions()
    {
        glewExperimental = TRUE;
        GLenum err = glewInit();
        if (err != GLEW_OK)
        {
            Util::Log(LogType::ErrorC, "Error in glewInit: %s", glewGetErrorString(err));
            return false;
        }
        checkForGlError();

        //TODO: Load any glew extensions
        //glewGetExtension();

        return true;
    }
}
