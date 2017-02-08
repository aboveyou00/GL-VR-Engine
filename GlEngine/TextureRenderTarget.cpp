#include "stdafx.h"
#include "TextureRenderTarget.h"
#include "TextureRenderTargetImpl.h"
#include "Engine.h"
#include "ResourceLoader.h"

namespace GlEngine
{
    TextureRenderTarget::TextureRenderTarget(unsigned width, unsigned height)
        : RenderTarget(nullptr),
          Texture(width, height, TextureFlag::RenderTarget)
    {
        pimpl = new Impl::TextureRenderTargetImpl(this);
        auto resources = Engine::GetInstance().GetServiceProvider().GetService<ResourceLoader>();
        resources->QueueInitialize(static_cast<Texture*>(this));
        //resources->QueueInitialize(this);
    }
    TextureRenderTarget::~TextureRenderTarget()
    {
    }

    bool TextureRenderTarget::Initialize()
    {
        if (!Texture::Initialize()) return false;
        return RenderTarget::Initialize();
    }
    void TextureRenderTarget::Shutdown()
    {
        Texture::Shutdown();
        RenderTarget::Shutdown();
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
