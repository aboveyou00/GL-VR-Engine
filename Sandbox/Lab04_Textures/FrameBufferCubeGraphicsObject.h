#pragma once

#include "CubeGraphicsObject.h"

namespace GlEngine
{
    class TextureRenderTarget;
}

class FrameBufferCubeGraphicsObject : public GlEngine::CubeGraphicsObject
{
public:
    FrameBufferCubeGraphicsObject(std::string name, GlEngine::Material *mat, Vector<3> size);
    ~FrameBufferCubeGraphicsObject();

    virtual bool InitializeAsync() override;

    virtual void Tick(float delta) override;

private:
    GlEngine::TextureRenderTarget *texRenderTarget;
};
