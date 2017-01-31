#include "stdafx.h"
#include "TextureRenderTargetImpl.h"
#include "TextureFlag.h"

namespace GlEngine
{
    namespace Impl
    {
        TextureRenderTargetImpl::TextureRenderTargetImpl(unsigned width, unsigned height)
            : texture(new Texture(width, height, TextureFlag::RenderTarget))
        {
        }
        TextureRenderTargetImpl::~TextureRenderTargetImpl()
        {
        }

        bool TextureRenderTargetImpl::Initialize()
        {
            return true;
        }
        void TextureRenderTargetImpl::Shutdown()
        {
        }
        bool TextureRenderTargetImpl::InitializeGraphics()
        {
            frameBuffer = 0;
            glGenFramebuffers(1, &frameBuffer);
            glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);

            glGenRenderbuffers(1, &depthRenderBuffer);
            glBindRenderbuffer(GL_RENDERBUFFER, depthRenderBuffer);
            glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, texture->GetWidth(), texture->GetHeight());
            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthRenderBuffer);

            glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, texture->glslTextureId(), 0);

            // Set the list of draw buffers.    
            GLenum DrawBuffers[1] = { GL_COLOR_ATTACHMENT0 };
            glDrawBuffers(1, DrawBuffers);

            // Check that the frame buffer was created successfully
            if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
                return false;

            return true;
        }
        void TextureRenderTargetImpl::ShutdownGraphics()
        {
        }

        const char *TextureRenderTargetImpl::name()
        {
            return "TextureRenderTargetImpl";
        }

        void TextureRenderTargetImpl::MakeCurrentTarget()
        {
            assert(false);
        }

        void TextureRenderTargetImpl::Prepare()
        {
        }
        void TextureRenderTargetImpl::PrePush()
        {
            glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
            glViewport(0, 0, texture->GetWidth(), texture->GetHeight());

            RenderTargetImpl::PrePush();
        }

        void TextureRenderTargetImpl::Flip()
        {
        }

        TextureRenderTargetImpl::operator bool()
        {
            return true;
        }
    }
}
