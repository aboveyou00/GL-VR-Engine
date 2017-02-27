#include "stdafx.h"
#include "SimpleRenderPipeline.h"

namespace GlEngine
{
    SimpleRenderPipeline::SimpleRenderPipeline(Frame* frame, std::vector<std::pair<RenderStage*, ICamera*>> renderStages)
        : _frame(frame), _renderStages(renderStages)
    {
    }
    SimpleRenderPipeline::~SimpleRenderPipeline()
    {
    }
    std::vector<std::pair<RenderStage*, ICamera*>> SimpleRenderPipeline::renderStages()
    {
        return _renderStages;
    }
    Frame * SimpleRenderPipeline::frame()
    {
        return _frame;
    }
}