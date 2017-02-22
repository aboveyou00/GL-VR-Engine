#include "stdafx.h"
#include "OpenGl.h"
#include "LogUtils.h"

void checkForGlError()
{
    while (true)
    {
        auto err = glGetError();
        std::string errString;
        switch (err)
        {
        case GL_INVALID_ENUM:                  errString = "INVALID_ENUM"; break;
        case GL_INVALID_VALUE:                 errString = "INVALID_VALUE"; break;
        case GL_INVALID_OPERATION:             errString = "INVALID_OPERATION"; break;
        case GL_STACK_OVERFLOW:                errString = "STACK_OVERFLOW"; break;
        case GL_STACK_UNDERFLOW:               errString = "STACK_UNDERFLOW"; break;
        case GL_OUT_OF_MEMORY:                 errString = "OUT_OF_MEMORY"; break;
        case GL_INVALID_FRAMEBUFFER_OPERATION: errString = "INVALID_FRAMEBUFFER_OPERATION"; break;
        case 0: return;
        }
        GlEngine::Util::Log(GlEngine::LogType::ErrorC, "An OpenGL error was produced: %s", errString.c_str());
    }
    //assert(err == GL_NO_ERROR);
}
