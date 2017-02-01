#pragma once

#include "CubeGameObject.h"

namespace GlEngine
{
    class TextureRenderTarget;
    class GraphicsObject;
    class GraphicsContext;
}

class FrameBufferCubeGameObject : public GlEngine::CubeGameObject
{
public:
    FrameBufferCubeGameObject(Vector<3> size);
    ~FrameBufferCubeGameObject();

    virtual bool Initialize() override;

    virtual void Tick(float delta) override;

    virtual GlEngine::GraphicsObject *CreateGraphicsObject(GlEngine::GraphicsContext *ctx) override;

private:
    GlEngine::TextureRenderTarget *texRenderTarget;
    GlEngine::GraphicsContext *myCtx;
};
