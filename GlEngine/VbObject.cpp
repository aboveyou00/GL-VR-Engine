#include "stdafx.h"
#include "VbObject.h"

#include "OpenGl.h"

namespace GlEngine
{
    VbObject::VbObject()
        : VbObject(0, BufferMode::Array)
    {
    }
    VbObject::VbObject(unsigned buff, BufferMode mode)
        : _buffer(buff), _mode(mode)
    {
    }
    VbObject::~VbObject()
    {
    }

    bool VbObject::InitializeAsync()
    {
        return true;
    }
    void VbObject::ShutdownAsync()
    {
    }
    bool VbObject::InitializeGraphics()
    {
        return isReady();
    }
    void VbObject::ShutdownGraphics()
    {
        if (_buffer != 0)
        {
            glDeleteBuffers(1, static_cast<GLuint*>(&_buffer));
            checkForGlError();
            _buffer = 0;
        }
    }

    bool VbObject::isReady()
    {
        return _buffer != 0;
    }

    std::string VbObject::name()
    {
        return "VbObject";
    }

    void VbObject::MakeCurrent()
    {
        assert(isReady());
        glBindBuffer(static_cast<GLenum>(_mode), static_cast<GLuint>(_buffer));
        checkForGlError();
    }
}
