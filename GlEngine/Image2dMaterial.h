#pragma once

#include "Material.h"

namespace GlEngine
{
    class ENGINE_SHARED Image2dMaterial : public Material
    {
    public:
        Image2dMaterial();
        ~Image2dMaterial();

        void SetTexture(Texture *tex);

        void Push(bool instanced = false) override;
        void Pop(bool instanced = false) override;

        bool IsOpaque() override;
        TesselationType GetTesselationType() override;

        const char *name() override;
        operator bool() override;

    private:
        Texture *tex;
        Shader *singleShader;
    };
}
