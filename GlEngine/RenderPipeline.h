#pragma once
#include <vector>
#include "RenderStage.h"
#include "ICamera.h"

namespace GlEngine
{
    class ENGINE_SHARED RenderPipeline
    {
    public:
        RenderPipeline(Vector<3> clearColor = Vector<3>(0, 0, 0));
        ~RenderPipeline();

        virtual std::vector<std::pair<RenderStage*, ICamera*>> renderStages() = 0;

        virtual Vector<3> clearColor();
        virtual void SetClearColor(Vector<3> color);

        virtual Frame* frame() = 0;

    protected:
        Vector<3> _clearColor;
    };
}