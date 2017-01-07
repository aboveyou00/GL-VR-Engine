#include "stdafx.h"
#include "VbObjectAttribList.h"

namespace GlEngine
{
    VbObjectAttribList::VbObjectAttribList(VbObject vbo)
        : vbo(vbo), attribs(new std::vector<VbObjectAttrib>())
    {
    }
    VbObjectAttribList::VbObjectAttribList(VbObjectAttribList &other)
        : VbObjectAttribList(other.vbo)
    {
        for (size_t q = 0; q < other.attribs->size(); q++)
            attribs->push_back((*other.attribs)[q]);
    }
    VbObjectAttribList::~VbObjectAttribList()
    {
        SafeDelete(attribs);
    }

    void VbObjectAttribList::BuildVao(VaoFactory &vao)
    {
        vbo.MakeCurrent();
        for (size_t q = 0; q < attribs->size(); q++)
            (*attribs)[q].BuildVao(vao);
    }

    void VbObjectAttribList::AddAttrib(unsigned size, VboType type, bool normalized, unsigned stride, const void * start, bool instanced)
    {
        attribs->push_back(VbObjectAttrib(VbObjectAttribType::Normal, size, type, normalized, stride, start, instanced));
    }
    void VbObjectAttribList::AddAttribL(unsigned size, VboType type, unsigned stride, const void * start, bool instanced)
    {
        attribs->push_back(VbObjectAttrib(VbObjectAttribType::Long, size, type, false, stride, start, instanced));
    }
    void VbObjectAttribList::AddAttribI(unsigned size, VboType type, unsigned stride, const void * start, bool instanced)
    {
        attribs->push_back(VbObjectAttrib(VbObjectAttribType::Integer, size, type, false, stride, start, instanced));
    }

    void VbObjectAttribList::MakeCurrent()
    {
        vbo.MakeCurrent();
    }

    VbObjectAttribList::operator bool()
    {
        return !!vbo;
    }
}
