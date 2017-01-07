#pragma once

#include "GameObject.h"

namespace GlEngine
{
    class Texture;
    class Material;
}

namespace TileRPG
{
    class DialogBoxObject : public GlEngine::GameObject
    {
    public:
        DialogBoxObject();
        DialogBoxObject(const char *textureSrc);
        DialogBoxObject(GlEngine::Texture *tex);
        ~DialogBoxObject();

        virtual const char *name() override;

        void SetTextureSource(const char *textureSrc);
        void SetTexture(GlEngine::Texture *tex);

        virtual GlEngine::GraphicsObject *CreateGraphicsObject(GlEngine::GraphicsContext &ctx) override;
        virtual void UpdateGraphicsObject(GlEngine::GraphicsContext &ctx, GlEngine::GraphicsObject *object) override;

    private:
        GlEngine::Texture *tex;
    };
}
