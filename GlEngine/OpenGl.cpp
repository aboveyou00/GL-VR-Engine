#include "stdafx.h"
#include "OpenGl.h"
#include "LogUtils.h"
#include <sstream>

void checkForGlError()
{
    while (true)
    {
        auto err = glGetError();
        if (!err) return;
        std::stringstream stream;
        switch (err)
        {
        case GL_INVALID_ENUM:                  stream << "INVALID_ENUM"; break;
        case GL_INVALID_VALUE:                 stream << "INVALID_VALUE"; break;
        case GL_INVALID_OPERATION:             stream << "INVALID_OPERATION"; break;
        case GL_STACK_OVERFLOW:                stream << "STACK_OVERFLOW"; break;
        case GL_STACK_UNDERFLOW:               stream << "STACK_UNDERFLOW"; break;
        case GL_OUT_OF_MEMORY:                 stream << "OUT_OF_MEMORY"; break;
        case GL_INVALID_FRAMEBUFFER_OPERATION: stream << "INVALID_FRAMEBUFFER_OPERATION"; break;
        }
        stream << ": " << glewGetErrorString(err);
        GlEngine::Util::Log(GlEngine::LogType::ErrorC, "An OpenGL error was produced: %s", stream.str().c_str());
        assert(false);
    }
}
