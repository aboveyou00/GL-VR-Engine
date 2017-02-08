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

        virtual std::string name() override;

        virtual void HandleEvent(GlEngine::Events::Event &evt) override;

        virtual GlEngine::GraphicsObject *CreateGraphicsObject(GlEngine::GraphicsContext *ctx) override;
        
    private:
        World *world;
        WorldLoader *loader;
    };
}
