#pragma once

#include "GameComponent.h"
#include "ICamera.h"
#include <map>
#include "Ray.h"

namespace GlEngine
{
    class Frame;
    class ViewPort;
    class RenderStage;
    class RenderPipeline;

    class ENGINE_SHARED CameraComponent : public GameComponent, public ICamera
    {
    public:
        CameraComponent();
        ~CameraComponent();

        static GameObject *Create(Frame *frame, std::string name);

        virtual std::string name() override;
        
        virtual void Tick(float delta) override;

        virtual void Push(RenderStage* stage) override;
        virtual void Pop(RenderStage* stage) override;

        virtual Frame* frame() override;

        Ray centerRay();
        Ray rayToPoint(Vector<3> point);

    private:
        Vector<3> eye, forward, up, right;
        Matrix<4, 4> view;

        Vector<3> _clearColor;

        RenderPipeline* _renderPipeline;
    };
}
