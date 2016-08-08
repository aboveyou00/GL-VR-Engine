#pragma once

#include "GameObject.h"

namespace TileRPG
{
    class World;
    class WorldLoader;

    class WorldEditorTargetObject : public GlEngine::GameObject
    {
    public:
        WorldEditorTargetObject(World *world);
        ~WorldEditorTargetObject();

        const char *name() override;

        void HandleEvent(GlEngine::Events::Event &evt) override;

        GlEngine::GraphicsObject *CreateGraphicsObject(GlEngine::GraphicsContext &ctx) override;
        
    private:
        World *world;
        WorldLoader *loader;
    };
}
