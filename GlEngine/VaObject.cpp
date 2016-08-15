#include "stdafx.h"
#include "VaObject.h"

#include "OpenGl.h"

namespace GlEngine
{
    VaObject::VaObject()
        : VaObject(0)
    {
    }
    VaObject::VaObject(unsigned vao)
        : VaObject(vao, nullptr)
    {
    }
    VaObject::VaObject(unsigned vao, std::vector<VbObject> *vbos)
        : _vao(vao), _vbos(vbos)
    {
    }
    VaObject::~VaObject()
    {
    }

    bool VaObject::Initialize()
    {
        if (_vbos == nullptr) return true;
        for (size_t q = 0; q < _vbos->size(); q++)
        {
            auto &vbo = (*_vbos)[q];
            if (!vbo.Initialize()) return false;
        }
        return true;
    }
    void VaObject::Shutdown()
    {
    }
    bool VaObject::InitializeGraphics()
    {
        if (!*this) return false;
        if (_vbos == nullptr) return true;
        for (size_t q = 0; q < _vbos->size(); q++)
        {
            auto &vbo = (*_vbos)[q];
            if (!vbo.InitializeGraphics()) return false;
        }
        return true;
    }
    void VaObject::ShutdownGraphics()
    {
        if (_vao != 0)
        {
            glDeleteVertexArrays(1, static_cast<GLuint*>(&_vao));
            _vao = 0;
        }
        if (_vbos != nullptr)
        {
            for (size_t q = 0; q < _vbos->size(); q++)
            {
                auto &vbo = (*_vbos)[q];
                vbo.ShutdownGraphics();
            }
            delete _vbos;
            _vbos = nullptr;
        }
    }

    VaObject::operator bool()
    {
        if (_vao == 0) return false;
        if (_vbos == nullptr) return true;
        for (size_t q = 0; q < _vbos->size(); q++)
        {
            auto &vbo = (*_vbos)[q];
            if (!vbo) return false;
        }
        return true;
    }

    const char *VaObject::name()
    {
        return "VaObject";
    }

    void VaObject::MakeCurrent()
    {
        assert(!!*this);
        glBindVertexArray(static_cast<GLuint>(_vao));

        if (_vbos == nullptr) return;
        for (size_t q = 0; q < _vbos->size(); q++)
        {
            auto &vbo = (*_vbos)[q];
            vbo.MakeCurrent(); //This does nothing for most vbos, but the element array and possibly others need it because it is not stored in the VAO
        }
    }
}
