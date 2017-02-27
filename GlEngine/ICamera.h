#pragma once

namespace GlEngine
{
    class Frame;
    class RenderStage;
    class RenderPipeline;

    class ENGINE_SHARED ICamera
    {
    public:
        virtual void Push(RenderStage* stage) = 0;
        virtual void Pop(RenderStage* stage) = 0;

        virtual Frame *frame() = 0;

        virtual bool isReady();
    };
}
