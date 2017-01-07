#pragma once

#include "VboType.h"
#include "VbObjectAttribType.h"

namespace GlEngine
{
    class VaoFactory;

    class VbObjectAttrib
    {
    public:
        VbObjectAttrib(VbObjectAttribType type, unsigned size, VboType vbotype, bool normalized, unsigned stride, const void *start, bool instanced);
        ~VbObjectAttrib();

        void BuildVao(VaoFactory &vao);

        inline VbObjectAttribType GetAttribType()
        {
            return type;
        }
        inline unsigned GetSize()
        {
            return size;
        }
        inline unsigned GetStride()
        {
            return stride;
        }
        inline VboType GetVboType()
        {
            return vbotype;
        }
        inline bool IsNormalized()
        {
            return normalized;
        }
        inline bool IsInstanced()
        {
            return instanced;
        }
        inline const void *GetStart()
        {
            return start;
        }

    private:
        VbObjectAttribType type;
        unsigned size, stride;
        VboType vbotype;
        bool normalized, instanced;
        const void *start;
    };
}
