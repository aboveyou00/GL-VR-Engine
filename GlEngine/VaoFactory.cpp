#include "stdafx.h"
#include "VaoFactory.h"

#include "OpenGl.h"

namespace GlEngine
{
    VaoFactory::VaoFactory()
        : _vao(0), _name(0), _vbos(new std::vector<VbObject>())
    {
    }
    VaoFactory::~VaoFactory()
    {
        SafeDelete(_vbos);
    }

    VaoFactory *VaoFactory::Begin()
    {
        auto vao = new VaoFactory();
        glGenVertexArrays(1, &vao->_vao);
        return vao;
    }

    void VaoFactory::makeCurrent()
    {
        glBindVertexArray(_vao);
    }

    void VaoFactory::AddAttrib(unsigned size, VboType type, bool normalized, unsigned stride, const void *start, bool instanced)
    {
        glVertexAttribPointer(_name, size, static_cast<GLenum>(type), normalized ? GL_TRUE : GL_FALSE, stride, start);
        glEnableVertexAttribArray(_name);
        glVertexAttribDivisor(_name, instanced ? 1 : 0);
        _name++;
    }
    void VaoFactory::AddAttribL(unsigned size, VboType type, unsigned stride, const void *start, bool instanced)
    {
        glVertexAttribLPointer(_name, size, static_cast<GLenum>(type), stride, start);
        glEnableVertexAttribArray(_name);
        glVertexAttribDivisor(_name, instanced ? 1 : 0);
        _name++;
    }
    void VaoFactory::AddAttribI(unsigned size, VboType type, unsigned stride, const void *start, bool instanced)
    {
        glVertexAttribIPointer(_name, size, static_cast<GLenum>(type), stride, start);
        glEnableVertexAttribArray(_name);
        glVertexAttribDivisor(_name, instanced ? 1 : 0);
        _name++;
    }

    VaObject VaoFactory::Compile()
    {
        unsigned vao = _vao;
        auto vbos = _vbos;
        _vbos = nullptr;
        delete this;
        return VaObject(vao, vbos);
    }
}
