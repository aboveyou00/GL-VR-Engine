#include "stdafx.h"
#include "TextureRenderTargetImpl.h"
#include "TextureFlag.h"
#include "LogUtils.h"

namespace GlEngine::Impl
{
    TextureRenderTargetImpl::TextureRenderTargetImpl(Texture *texture)
        : RenderTargetImpl(), texture(texture)
    {
    }
    TextureRenderTargetImpl::~TextureRenderTargetImpl()
    {
    }

    bool TextureRenderTargetImpl::Initialize()
    {
        if (!RenderTargetImpl::Initialize()) return false;

        return true;
    }
    void TextureRenderTargetImpl::Shutdown()
    {
        RenderTargetImpl::Shutdown();
    }
    bool TextureRenderTargetImpl::InitializeGraphics()
    {
        if (!RenderTargetImpl::InitializeGraphics()) return false;

        frameBuffer = 0;
        glGenFramebuffers(1, &frameBuffer);
        if (frameBuffer == 0)
        {
            GLenum err = glGetError();
            if (err != GL_NO_ERROR)
            {
                Util::Log(LogType::ErrorC, "GL Error: %d", err);
            }
            Util::Log(LogType::ErrorC, "Failed to create framebuffer.");
            return false;
        }
        glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);

        glGenRenderbuffers(1, &depthRenderBuffer);
        glBindRenderbuffer(GL_RENDERBUFFER, depthRenderBuffer);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, texture->GetWidth(), texture->GetHeight());
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthRenderBuffer);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture->glslTextureId(), 0);

        // Set the list of draw buffers.    
        GLenum drawBuffers[1] = { GL_COLOR_ATTACHMENT0 };
        glDrawBuffers(1, drawBuffers);

        // Check that the frame buffer was created successfully
        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        {
            Util::Log(LogType::ErrorC, "Failed to create framebuffer.");
            return false;
        }

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        return true;
    }
    void TextureRenderTargetImpl::ShutdownGraphics()
    {
        RenderTargetImpl::ShutdownGraphics();
    }

    std::string TextureRenderTargetImpl::name()
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
    void TextureRenderTargetImpl::PostPop()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        RenderTargetImpl::PostPop();
    }

    void TextureRenderTargetImpl::Flip()
    {
    }

    TextureRenderTargetImpl::operator bool()
    {
        return true;
    }
}
