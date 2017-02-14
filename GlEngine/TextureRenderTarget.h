#pragma once

#include "IComponent.h"
#include "RenderTarget.h"
#include "Texture.h"

namespace GlEngine
{
    class ENGINE_SHARED TextureRenderTarget : virtual public Texture, virtual public RenderTarget
    {
    public:
        TextureRenderTarget(unsigned width, unsigned height, GlEngine::TextureFlag flags = TextureFlag::RenderTarget);
        ~TextureRenderTarget();

        virtual bool Initialize() override;
        virtual void Shutdown() override;
        virtual bool InitializeGraphics() override;
        virtual void ShutdownGraphics() override;

        virtual std::string name() override;
    };
}
