#pragma once

#include "IComponent.h"
#include "RenderTarget.h"
#include "Texture.h"

namespace GlEngine
{
    class Window;

    namespace Impl
    {
        class RenderTargetImpl;
    }

    class Window;

    class ENGINE_SHARED TextureRenderTarget : public RenderTarget
    {
    public:
        TextureRenderTarget(unsigned width, unsigned height, bool hasAlphaChannel = false);
        ~TextureRenderTarget();
    };
}
