#pragma once

#include "GameObject.h"

namespace TileRPG
{
    class CompassObject : public GlEngine::GameObject
    {
    public:
        CompassObject();
        ~CompassObject();
        
        void Tick(float delta) override;

        const char *name() override;

        GlEngine::GraphicsObject *CreateGraphicsObject(GlEngine::GraphicsContext &ctx) override;
        void UpdateGraphicsObject(GlEngine::GraphicsContext &ctx, GlEngine::GraphicsObject *object) override;

    private:
        float rotation;
    };
}
