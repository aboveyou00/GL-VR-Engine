#include "stdafx.h"
#include "VaoFactory.h"
#include "VbObjectAttribList.h"
#include "OpenGl.h"

namespace GlEngine
{
    VaoFactory::VaoFactory()
        : _vao(0), _name(0), _vbos(new std::vector<VbObjectAttribList*>())
    {
    }
    VaoFactory::~VaoFactory()
    {
        SafeDeleteVector(_vbos);
    }

    VaoFactory *VaoFactory::Begin()
    {
        auto vao = new VaoFactory();
        glGenVertexArrays(1, &vao->_vao);
        checkForGlError();
        return vao;
    }

    void VaoFactory::makeCurrent()
    {
        glBindVertexArray(_vao);
        checkForGlError();
    }

    void VaoFactory::Add(VaObject vao)
    {
        auto attributes = vao.GetVboAttributes();
        assert(attributes != nullptr);

        makeCurrent();
        for (size_t q = 0; q < attributes->size(); q++)
        {
            auto &attribute = *(*attributes)[q];
            AddAttribs(new VbObjectAttribList(attribute));
        }
    }

    void VaoFactory::AddAttribs(VbObjectAttribList *attribs)
    {
        _vbos->push_back(attribs);
        attribs->BuildVao(*this);
    }
    void VaoFactory::AddAttrib(VbObjectAttrib *attrib)
    {
        attrib->BuildVao(*this);
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
