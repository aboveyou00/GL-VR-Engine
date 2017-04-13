#pragma once

#include "VboGraphicsObject.h"
#include "MeshComponent.h"

namespace GlEngine
{
    class ENGINE_SHARED MeshMaterialGraphicsObject : public VboGraphicsObject
    {
    public:
        MeshMaterialGraphicsObject(MeshComponent* mesh, Material* materail, CreateFactoryFn createFactory = [](Material*) { return nullptr; });
        ~MeshMaterialGraphicsObject();

        MeshComponent* mesh();
        Material* material();

        virtual bool InitializeAsync() override;

    private:
        MeshComponent* _mesh;
        Material* _material;
    };
}