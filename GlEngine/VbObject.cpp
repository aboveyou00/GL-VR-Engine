#include "stdafx.h"
#include "VbObject.h"

#include "OpenGl.h"

namespace GlEngine
{
    VbObject::VbObject()
        : VbObject(0, 0, BufferMode::Array)
    {
    }
    VbObject::VbObject(unsigned buff, BufferMode mode)
        : VbObject(0, buff, mode)
    {
    }
    VbObject::VbObject(unsigned vao, unsigned buff)
        : VbObject(vao, buff, BufferMode::Array)
    {
    }
    VbObject::VbObject(unsigned vao, unsigned buff, BufferMode mode)
        : _vao(vao), _buffer(buff), _mode(mode)
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
        if (_mode == BufferMode::Array && _vao != 0)
        {
            glDeleteVertexArrays(1, static_cast<GLuint*>(&_vao));
            _vao = 0;
        }
        if (_buffer != 0)
        {            glDeleteBuffers(1, static_cast<GLuint*>(&_buffer));            _buffer = 0;        }
    }

    VbObject::operator bool()
    {
        if (_mode == BufferMode::Array) return _vao != 0 && _buffer != 0;
        else return _buffer != 0;
    }

    const char *VbObject::name()
    {
        return "VbObject";
    }

    void VbObject::MakeCurrent()
    {
        assert(!!*this);
        if (_mode == BufferMode::Array) glBindVertexArray(static_cast<GLuint>(_vao));
        glBindBuffer(static_cast<GLenum>(_mode), static_cast<GLuint>(_buffer));
    }
}
