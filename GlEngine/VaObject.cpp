#include "stdafx.h"
#include "VaObject.h"
#include "VbObjectAttribList.h"
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
    VaObject::VaObject(unsigned vao, std::vector<VbObjectAttribList*> *vbo_attribs)
        : _vao(vao), _vbos(vbo_attribs)
    {
    }
    VaObject::~VaObject()
    {
    }

    bool VaObject::InitializeAsync()
    {
        return true;
    }
    void VaObject::ShutdownAsync()
    {
    }
    bool VaObject::InitializeGraphics()
    {
        if (!this->isReady()) return false;
        if (_vbos == nullptr) return true;
        for (size_t q = 0; q < _vbos->size(); q++)
        {
            auto &vbo_attribs = (*_vbos)[q];
            if (!vbo_attribs->GetVbObject().InitializeGraphics()) return false;
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
                //auto &vbo_attribs = (*_vbos)[q];
                //vbo_attribs->GetVbObject().ShutdownGraphics();
            }
            delete _vbos;
            _vbos = nullptr;
        }
    }

    bool VaObject::isReady()
    {
        if (_vao == 0) return false;
        if (_vbos == nullptr) return true;
        for (size_t q = 0; q < _vbos->size(); q++)
        {
            auto &vbo_attribs = (*_vbos)[q];
            if (!vbo_attribs) return false;
        }
        return true;
    }

    std::string VaObject::name()
    {
        return "VaObject";
    }

    void VaObject::MakeCurrent()
    {
        assert(this->isReady());
        glBindVertexArray(static_cast<GLuint>(_vao));

        if (_vbos == nullptr) return;
        for (size_t q = 0; q < _vbos->size(); q++)
        {
            auto &vbo_attribs = *(*_vbos)[q];
            vbo_attribs.MakeCurrent(); //This does nothing for most vbos, but the element array and possibly others need it because it is not stored in the VAO
        }
    }
}
