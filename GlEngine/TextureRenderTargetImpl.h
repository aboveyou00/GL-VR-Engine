#pragma once

#include "RenderTargetImpl.h"
#include "Texture.h"

namespace GlEngine::Impl
{
    class TextureRenderTargetImpl : public RenderTargetImpl
    {
    public:
        TextureRenderTargetImpl(unsigned width, unsigned height, bool hasAlphaChannel = false);
        ~TextureRenderTargetImpl();

        virtual bool Initialize() override;
        virtual void Shutdown() override;
        virtual bool InitializeGraphics() override;
        virtual void ShutdownGraphics() override;

        virtual const char *name() override;

        bool alive = true;

        virtual void MakeCurrentTarget() override;

        virtual void Prepare() override;
        virtual void Push(RenderTargetLayer layer) override;
        virtual void Pop(RenderTargetLayer layer) override;

        virtual void Flip() override;

        virtual operator bool() override;

    protected:
        Texture *texture;
        GLuint frameBuffer, depthRenderBuffer;
    };
}
