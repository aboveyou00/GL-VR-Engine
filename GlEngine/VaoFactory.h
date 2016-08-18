#pragma once

#include "VboFactory.h"
#include "VaObject.h"

namespace GlEngine
{
    class ENGINE_SHARED VaoFactory
    {
    private:
        VaoFactory();
        ~VaoFactory();

    public:
        static VaoFactory *Begin();

        template <VboType type, typename... TArgs>
        VaoFactory *Add(VboFactory<type, TArgs...> *factory)
        {
            makeCurrent();
            _vbos->push_back(factory->Compile(this, false));
            return this;
        }
        template <VboType type, typename... TArgs>
        VaoFactory *AddInstanced(VboFactory<type, TArgs...> *factory)
        {
            makeCurrent();
            _vbos->push_back(factory->Compile(this, true));
            return this;
        }

        void AddAttrib(unsigned size, VboType type, bool normalized, unsigned stride, const void *start, bool instanced = false);
        void AddAttribL(unsigned size, VboType type, unsigned stride, const void *start, bool instanced = false);
        void AddAttribI(unsigned size, VboType type, unsigned stride, const void *start, bool instanced = false);

        VaObject Compile();

    private:
        unsigned _vao;
        std::vector<VbObject> *_vbos;
        unsigned _name;

        void makeCurrent();
    };
}
