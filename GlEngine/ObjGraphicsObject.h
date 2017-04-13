#pragma once

#include "VboGraphicsObject.h"
#include "MeshComponent.h"

namespace GlEngine
{
    namespace ShaderFactory
    {
        class IPropertyProvider;
    }

    class ENGINE_SHARED ObjGraphicsObject : public VboGraphicsObject
    {
    public:
        ObjGraphicsObject(std::string name, std::string filename, std::function<ShaderFactory::ShaderFactory*(Material*)> createFactory = [](Material*) { return nullptr; });

        static ObjGraphicsObject *Create(std::string name, std::string filename, Material *mat, std::vector<ShaderFactory::IPropertyProvider*> providers);

        //virtual bool InitializeAsync() override;

    private:
        std::string filename;
    };
}
