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

    bool VbObject::Initialize()
    {
        return true;
    }
    void VbObject::Shutdown()
    {
    }
    bool VbObject::InitializeGraphics()
    {
        return !!*this;
    }
    void VbObject::ShutdownGraphics()
    {
        if (_buffer != 0)
        {
            glDeleteBuffers(1, static_cast<GLuint*>(&_buffer));
            _buffer = 0;
        }
    }

    VbObject::operator bool()
    {
        return _buffer != 0;
    }

    std::string VbObject::name()
    {
        return "VbObject";
    }

    void VbObject::MakeCurrent()
    {
        assert(!!*this);
        glBindBuffer(static_cast<GLenum>(_mode), static_cast<GLuint>(_buffer));
    }
}
