#pragma once

#include "Material.h"

namespace GlEngine
{
    class ENGINE_SHARED BlinnMaterial : public Material
    {
    public:
        static BlinnMaterial *Create(Texture *texture);

    private:
        BlinnMaterial(Texture *texture);
        ~BlinnMaterial();

    public:
        void Push(bool instanced = false) override;
        void Pop(bool instanced = false) override;

        bool IsOpaque() override;
        TesselationType GetTesselationType() override;

        virtual std::vector<ShaderFactory::ShaderProp*> properties() override;
        virtual std::vector<ShaderFactory::Attribute*> attributes() override;

        const char *name() override;
        operator bool() override;

    private:
        Texture *texture;
        //ShaderFactory *instancedShader, *singleShader;
    };
}
