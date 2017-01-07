#pragma once

#include "VboFactory.h"
#include "VaObject.h"

namespace GlEngine
{
    class VbObjectAttrib;

    class ENGINE_SHARED VaoFactory
    {
    private:
        VaoFactory();
        ~VaoFactory();

    public:
        static VaoFactory *Begin();

        template <VboType type, typename... TArgs>
        VaoFactory &Add(VboFactory<type, TArgs...> *factory)
        {
            makeCurrent();
            factory->Compile(this, false);
            return *this;
        }
        template <VboType type, typename... TArgs>
        VaoFactory &AddInstanced(VboFactory<type, TArgs...> *factory)
        {
            makeCurrent();
            factory->Compile(this, true);
            return *this;
        }

        void Add(VaObject vao);

        void AddAttribs(VbObjectAttribList *attribs);
        void AddAttrib(VbObjectAttrib *attrib);
        inline unsigned GetName()
        {
            return _name++;
        }

        VaObject Compile();

    private:
        unsigned _vao;
        std::vector<VbObjectAttribList*> *_vbos;
        unsigned _name;

        void makeCurrent();
    };
}
