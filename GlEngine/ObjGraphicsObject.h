#pragma once

#include "VboGraphicsObject.h"

namespace GlEngine
{
    namespace ShaderFactory
    {
        class IPropertyProvider;
    }

    class ENGINE_SHARED ObjGraphicsObject : public VboGraphicsObject
    {
    public:
        ObjGraphicsObject(const char *const filename, std::function<ShaderFactory::ShaderFactory*(Material*)> createFactory = [](Material*) { return nullptr; });

        static ObjGraphicsObject *Create(const char *name, Material *mat, std::vector<ShaderFactory::IPropertyProvider*> providers);

        bool Initialize() override;

        const char *name() override;

    private:
        const char * filename;
    };
}
