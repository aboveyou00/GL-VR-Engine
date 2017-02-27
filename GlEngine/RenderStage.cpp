#include "stdafx.h"
#include "RenderStage.h"
#include "OpenGl.h"

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
            glEnable(GL_DEPTH_TEST);
            checkForGlError();
            glEnable(GL_CULL_FACE);
            checkForGlError();
            glDepthFunc(GL_LEQUAL);
            checkForGlError();
        }
    );
    
    RenderStage* renderStage_translucent = new RenderStage("translucent",
        []() {
            glEnable(GL_DEPTH_TEST);
            checkForGlError();
            glEnable(GL_CULL_FACE);
            checkForGlError();
            glDepthFunc(GL_LEQUAL);
            checkForGlError();
        }
    );

    RenderStage* renderStage_2d = new RenderStage("2d", 
        []() {
            glDisable(GL_DEPTH_TEST);
            checkForGlError();
            glDisable(GL_CULL_FACE);
            checkForGlError();
            glDepthFunc(GL_NEVER);
            checkForGlError();
        }
    );
}
