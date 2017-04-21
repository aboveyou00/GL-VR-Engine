#include "stdafx.h"
#include "RenderStage.h"
#include "Engine.h"
#include "GraphicsAdapter.h"

#include "../OpenGlGraphicsAdapter/OpenGl.h"

namespace GlEngine
{
    RenderStage::RenderStage(std::string name, std::function<void(void)> push, std::function<void(void)> pop)
        : Push(push), Pop(pop)
    {
        stageMap[name] = this;
    }
    RenderStage::~RenderStage()
    {
    }

    std::map<std::string, RenderStage*> RenderStage::stageMap = std::map<std::string, RenderStage*>();
    
    RenderStage* renderStage_opaque = new RenderStage("opaque",
        []() {
            auto &graphicsAdapter = THIS_ENGINE.graphicsAdapter();
            graphicsAdapter.ForkCapabilities();
            graphicsAdapter.SetCapability(GraphicsCap::DepthTest, true);
            graphicsAdapter.SetCapability(GraphicsCap::CullFace, true);

            glDepthFunc(GL_LEQUAL);
            checkForGlError();
        },
        []() {
            auto &graphicsAdapter = THIS_ENGINE.graphicsAdapter();
            graphicsAdapter.PopCapabilities();
        }
    );
    
    RenderStage* renderStage_translucent = new RenderStage("translucent",
        []() {
            auto &graphicsAdapter = THIS_ENGINE.graphicsAdapter();
            graphicsAdapter.ForkCapabilities();
            graphicsAdapter.SetCapability(GraphicsCap::DepthTest, true);
            graphicsAdapter.SetCapability(GraphicsCap::CullFace, true);

            glDepthFunc(GL_LEQUAL);
            checkForGlError();
        },
        []() {
            auto &graphicsAdapter = THIS_ENGINE.graphicsAdapter();
            graphicsAdapter.PopCapabilities();
        }
    );

    RenderStage* renderStage_2d = new RenderStage("2d", 
        []() {
            auto &graphicsAdapter = THIS_ENGINE.graphicsAdapter();
            graphicsAdapter.ForkCapabilities();
            graphicsAdapter.SetCapability(GraphicsCap::DepthTest, false);
            graphicsAdapter.SetCapability(GraphicsCap::CullFace, false);

            glDepthFunc(GL_NEVER);
            checkForGlError();
        },
        []() {
            auto &graphicsAdapter = THIS_ENGINE.graphicsAdapter();
            graphicsAdapter.PopCapabilities();
        }
    );
}
