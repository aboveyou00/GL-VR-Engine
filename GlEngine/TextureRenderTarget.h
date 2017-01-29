#pragma once

#include "IComponent.h"
#include "RenderTarget.h"
#include "Texture.h"

namespace GlEngine
{
    class ENGINE_SHARED TextureRenderTarget : public RenderTarget
    {
    public:
        TextureRenderTarget(unsigned width, unsigned height, bool hasAlphaChannel = false);
        ~TextureRenderTarget();

        virtual const char *name() override;
    };
}
