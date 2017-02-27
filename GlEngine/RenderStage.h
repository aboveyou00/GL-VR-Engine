#pragma once

#include <map>

namespace GlEngine
{
    class ENGINE_SHARED RenderStage
    {
        public:
            RenderStage(std::string name, std::function<void(void)> push = []() {}, std::function<void(void)> pop = [](){});
            ~RenderStage();

            static std::map<std::string, RenderStage*> stageMap;

            std::function<void(void)> Push;
            std::function<void(void)> Pop;
    };

    extern ENGINE_SHARED RenderStage* renderStage_opaque;
    extern ENGINE_SHARED RenderStage* renderStage_translucent;
    extern ENGINE_SHARED RenderStage* renderStage_2d;
}