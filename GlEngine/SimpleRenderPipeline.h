#pragma once
#include "RenderPipeline.h"

namespace GlEngine
{
    class ENGINE_SHARED SimpleRenderPipeline : public RenderPipeline
    {
    public:
        SimpleRenderPipeline(Frame* frame, std::vector<std::pair<RenderStage*, ICamera*>> renderStages);
        ~SimpleRenderPipeline();

        virtual std::vector<std::pair<RenderStage*, ICamera*>> renderStages() override;

        virtual Frame * frame() override;

    private:
        std::vector<std::pair<RenderStage*, ICamera*>> _renderStages;
        Frame* _frame;
    };
}