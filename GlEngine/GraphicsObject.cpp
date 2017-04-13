#include "stdafx.h"
#include "GraphicsObject.h"

#include "OpenGl.h"
#include "VBOFactory.h"

#include "Engine.h"
#include "ServiceProvider.h"
#include "ILogger.h"
#include "ResourceLoader.h"
#include "GameObject.h"
#include "Frame.h"

namespace GlEngine
{
    GraphicsObject::GraphicsObject(std::string name, bool autoinit)
        : GameComponent(name, autoinit),
          initialized(false),
          graphicsInitialized(false),
          renderOrder(0)
    {
    }
    GraphicsObject::~GraphicsObject()
    {
    }

    bool GraphicsObject::InitializeAsync()
    {
        if (initialized) return true;
        initialized = true;
        return GameComponent::InitializeAsync();
    }
    void GraphicsObject::ShutdownAsync()
    {
        initialized = false;
    }
    bool GraphicsObject::InitializeGraphics()
    {
        if (graphicsInitialized) return true;
        if (!initialized)
        {
            auto logger = Engine::GetInstance().GetServiceProvider().GetService<ILogger>();
            logger->Log(LogType::ErrorC, "GraphicsObject graphics initialized before the object could be initialized. %s", this);
            return false;
        }
        return graphicsInitialized = true;
    }
    void GraphicsObject::ShutdownGraphics()
    {
        graphicsInitialized = false;
    }

    void GraphicsObject::AddPropertyProvider(ShaderFactory::IPropertyProvider *provider)
    {
        _providers.push_back(provider);
    }
    void GraphicsObject::RemovePropertyProvider(ShaderFactory::IPropertyProvider *provider)
    {
        auto it = std::find(_providers.begin(), _providers.end(), provider);
        if (it != _providers.end()) _providers.erase(it);
    }

    void GraphicsObject::Render(RenderStage* stage)
    {
        PreRender(stage);
        RenderImpl(stage);
        PostRender(stage);
    }
    void GraphicsObject::PreRender(RenderStage*)
    {
    }
    void GraphicsObject::PostRender(RenderStage*)
    {
    }

    void GraphicsObject::RenderInstanced(RenderStage* stage, unsigned instanceCount)
    {
        if (instanceCount == 0) return;
        PreRenderInstanced(stage);
        RenderInstancedImpl(stage, instanceCount);
        PostRenderInstanced(stage);
    }
    void GraphicsObject::PreRenderInstanced(RenderStage*)
    {
    }
    void GraphicsObject::PostRenderInstanced(RenderStage*)
    {
    }

    std::vector<ShaderFactory::IPropertyProvider*> &GraphicsObject::providers()
    {
        return _providers;
    }
}
