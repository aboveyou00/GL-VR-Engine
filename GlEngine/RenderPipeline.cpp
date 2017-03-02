#include "stdafx.h"
#include "RenderPipeline.h"

namespace GlEngine
{
    RenderPipeline::RenderPipeline(Vector<3> clearColor)
        : _clearColor(clearColor)
    {
    }
    RenderPipeline::~RenderPipeline()
    {
    }

    Vector<3> RenderPipeline::clearColor()
    {
        return _clearColor;
    }
    void RenderPipeline::SetClearColor(Vector<3> color)
    {
        _clearColor = color;
    }
}
