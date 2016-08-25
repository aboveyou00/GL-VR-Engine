#pragma once

#include "ImageGraphicsObject.h"

namespace GlEngine
{
    class Texture;
}

namespace TileRPG
{
    class DialogBoxMaterial;

    class DialogBoxGraphicsObject : public GlEngine::ImageGraphicsObject
    {
    public:
        DialogBoxGraphicsObject();
        ~DialogBoxGraphicsObject();

        void PreRender(GlEngine::RenderTargetLayer layer) override;
        void RenderImpl(GlEngine::RenderTargetLayer layer) override;
        void PostRender(GlEngine::RenderTargetLayer layer) override;

        void SetTexture(GlEngine::Texture *tex);

    private:
        GlEngine::Texture *tex;
        DialogBoxMaterial *mat;
    };
}
