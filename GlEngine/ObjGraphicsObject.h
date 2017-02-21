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
        ObjGraphicsObject(std::string name, const char *const filename, std::function<ShaderFactory::ShaderFactory*(Material*)> createFactory = [](Material*) { return nullptr; });

        static ObjGraphicsObject *Create(std::string name, const char *filename, Material *mat, std::vector<ShaderFactory::IPropertyProvider*> providers);

        virtual bool InitializeAsync() override;

    private:
        const char *filename;
    };
}
