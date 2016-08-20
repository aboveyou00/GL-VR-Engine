#include "stdafx.h"
#include "VbObjectAttrib.h"
#include "VaoFactory.h"
#include "OpenGl.h"

namespace GlEngine
{
    VbObjectAttrib::VbObjectAttrib(VbObjectAttribType type, unsigned size, VboType vbotype, bool normalized, unsigned stride, const void * start, bool instanced)
        : type(type),
          size(size),
          stride(stride),
          vbotype(vbotype),
          normalized(normalized),
          instanced(instanced),
          start(start)
    {
    }
    VbObjectAttrib::~VbObjectAttrib()
    {
    }

    void VbObjectAttrib::BuildVao(VaoFactory &vao)
    {
        unsigned name = vao.GetName();

        switch (type)
        {
        case GlEngine::VbObjectAttribType::Normal:
            glVertexAttribPointer(name, size, static_cast<GLenum>(vbotype), normalized ? GL_TRUE : GL_FALSE, stride, start);
            break;

        case GlEngine::VbObjectAttribType::Long:
            glVertexAttribLPointer(name, size, static_cast<GLenum>(vbotype), stride, start);
            break;

        case GlEngine::VbObjectAttribType::Integer:
            glVertexAttribIPointer(name, size, static_cast<GLenum>(vbotype), stride, start);
            break;

        default:
            assert(false);
            break;
        }

        glEnableVertexAttribArray(name);
        glVertexAttribDivisor(name, instanced ? 1 : 0);
    }
}
