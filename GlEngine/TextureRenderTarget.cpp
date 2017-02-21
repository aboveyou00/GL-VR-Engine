#include "stdafx.h"
#include "TextureRenderTarget.h"
#include "TextureRenderTargetImpl.h"
#include "Engine.h"
#include "ResourceLoader.h"

namespace GlEngine
{
    TextureRenderTarget::TextureRenderTarget(unsigned width, unsigned height, GlEngine::TextureFlag flags)
        : RenderTarget(nullptr),
          Texture(width, height, TextureFlag::RenderTarget | flags)
    {
        pimpl = new Impl::TextureRenderTargetImpl(this);
        auto resources = Engine::GetInstance().GetServiceProvider().GetService<ResourceLoader>();
        resources->QueueInitialize(static_cast<Texture*>(this));
        //resources->QueueInitialize(this);
    }
    TextureRenderTarget::~TextureRenderTarget()
    {
    }

    bool TextureRenderTarget::InitializeAsync()
    {
        if (!Texture::InitializeAsync()) return false;
        return RenderTarget::InitializeAsync();
    }
    void TextureRenderTarget::ShutdownAsync()
    {
        Texture::ShutdownAsync();
        RenderTarget::ShutdownAsync();
    }

    bool TextureRenderTarget::InitializeGraphics()
    {
        if (!Texture::InitializeGraphics()) return false;
        return RenderTarget::InitializeGraphics();
    }
    void TextureRenderTarget::ShutdownGraphics()
    {
        Texture::ShutdownGraphics();
        RenderTarget::ShutdownGraphics();
    }

    std::string TextureRenderTarget::name()
    {
        return "TextureRenderTarget";
    }
}
