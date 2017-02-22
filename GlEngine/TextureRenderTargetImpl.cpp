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

    bool TextureRenderTargetImpl::InitializeAsync()
    {
        if (!RenderTargetImpl::InitializeAsync()) return false;

        return true;
    }
    void TextureRenderTargetImpl::ShutdownAsync()
    {
        RenderTargetImpl::ShutdownAsync();
    }
    bool TextureRenderTargetImpl::InitializeGraphics()
    {
        if (!RenderTargetImpl::InitializeGraphics()) return false;

        frameBuffer = 0;
        glGenFramebuffers(1, &frameBuffer);
        checkForGlError();
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
        checkForGlError();

        glGenRenderbuffers(1, &depthRenderBuffer);
        checkForGlError();
        glBindRenderbuffer(GL_RENDERBUFFER, depthRenderBuffer);
        checkForGlError();
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, texture->GetWidth(), texture->GetHeight());
        checkForGlError();
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthRenderBuffer);
        checkForGlError();

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture->glslTextureId(), 0);
        checkForGlError();

        // Set the list of draw buffers.    
        GLenum drawBuffers[1] = { GL_COLOR_ATTACHMENT0 };
        glDrawBuffers(1, drawBuffers);
        checkForGlError();

        // Check that the frame buffer was created successfully
        auto status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
        checkForGlError();
        if (status != GL_FRAMEBUFFER_COMPLETE)
        {
            Util::Log(LogType::ErrorC, "Failed to create framebuffer.");
            return false;
        }

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        checkForGlError();
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
        checkForGlError();
        glViewport(0, 0, texture->GetWidth(), texture->GetHeight());
        checkForGlError();

        RenderTargetImpl::PrePush();
    }
    void TextureRenderTargetImpl::PostPop()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        checkForGlError();

        RenderTargetImpl::PostPop();
    }

    void TextureRenderTargetImpl::Flip()
    {
    }

    bool TextureRenderTargetImpl::isReady()
    {
        return true;
    }
}
