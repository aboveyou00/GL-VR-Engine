#pragma once

#include "VbObject.h"
#include "VbObjectAttrib.h"

namespace GlEngine
{
    class ENGINE_SHARED VbObjectAttribList
    {
    public:
        VbObjectAttribList(VbObject vbo);
        VbObjectAttribList(VbObjectAttribList &other);
        ~VbObjectAttribList();

        inline VbObject GetVbObject()
        {
            return vbo;
        }

        void BuildVao(VaoFactory &vao);

        void AddAttrib(unsigned size, VboType type, bool normalized, unsigned stride, const void *start, bool instanced);
        void AddAttribL(unsigned size, VboType type, unsigned stride, const void *start, bool instanced);
        void AddAttribI(unsigned size, VboType type, unsigned stride, const void *start, bool instanced);

        void MakeCurrent();

        bool isReady();

    private:
        VbObject vbo;
        std::vector<VbObjectAttrib> *attribs;
    };
}
