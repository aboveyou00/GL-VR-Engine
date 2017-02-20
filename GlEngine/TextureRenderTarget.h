#pragma once

#include "RenderTarget.h"
#include "Texture.h"

namespace GlEngine
{
    class CameraComponent;

    class ENGINE_SHARED TextureRenderTarget : virtual public Texture, virtual public RenderTarget
    {
    public:
        TextureRenderTarget(unsigned width, unsigned height, CameraComponent *camera, GlEngine::TextureFlag flags = TextureFlag::RenderTarget);
        ~TextureRenderTarget();

        virtual bool InitializeAsync() override;
        virtual void ShutdownAsync() override;
        virtual bool InitializeGraphics() override;
        virtual void ShutdownGraphics() override;

        virtual std::string name() override;
    };
}
