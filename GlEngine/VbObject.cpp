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
        return _buffer != 0;
    }
    void VbObject::Shutdown()
    {
        glDeleteBuffers(1, static_cast<GLuint*>(&_buffer));
        _buffer = 0;
    }

    void VbObject::MakeCurrent()
    {
        assert(_buffer != 0);
        glBindBuffer(static_cast<GLenum>(_mode), static_cast<GLuint>(_buffer));
    }
}
