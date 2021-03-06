#pragma once

#include "GameObject.h"

namespace TileRPG
{
    class CompassObject : public GlEngine::GameObject
    {
    public:
        CompassObject(Vector<3> position = { 0, 0, 0 }, Matrix<4, 4> orientation = Matrix<4, 4>::Identity());
        ~CompassObject();
        
        virtual void Tick(float delta) override;

        virtual std::string name() override;

        GlEngine::GraphicsObject *CreateGraphicsObject(GlEngine::GraphicsContext *ctx) override;
        void UpdateGraphicsObject(GlEngine::GraphicsContext *ctx, GlEngine::GraphicsObject *object) override;

    private:
        float rotation;
    };
}
