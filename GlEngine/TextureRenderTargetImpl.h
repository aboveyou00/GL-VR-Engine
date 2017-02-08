#pragma once

#include "RenderTargetImpl.h"
#include "Texture.h"

namespace GlEngine::Impl
{
    class TextureRenderTargetImpl : public RenderTargetImpl
    {
    public:
        TextureRenderTargetImpl(Texture *texture);
        ~TextureRenderTargetImpl();

        virtual bool Initialize() override;
        virtual void Shutdown() override;
        virtual bool InitializeGraphics() override;
        virtual void ShutdownGraphics() override;

        virtual std::string name() override;

        bool alive = true;

        virtual void MakeCurrentTarget() override;

        virtual void Prepare() override;
        virtual void PrePush() override;
        virtual void PostPop() override;

        virtual void Flip() override;

        virtual operator bool() override;

    protected:
        Texture *texture;
        GLuint frameBuffer, depthRenderBuffer;
    };
}
