#pragma once

#include "IInitializable.h"
#include "ICamera.h"
#include "RenderTargetLayer.h"
#include <unordered_map>
#include "RenderPipeline.h"

namespace GlEngine::Events
{
    class Event;
}

namespace GlEngine
{
    class GameObject;
    class RenderTarget;
    class FrameStack;
    class CameraComponent;

    class ENGINE_SHARED Frame : public IInitializable, public RenderPipeline
    {
    public:
        Frame();
        ~Frame();

        friend class RenderTarget;
        friend class GameObject;
        friend class FrameStack;

        virtual std::string name() override;

        //Lifecycle hooks
        virtual bool Initialize() override;
        virtual void Shutdown() override;

        virtual void Tick(float delta);

        virtual void HandleEvent(Events::Event &evt);

        virtual void TickGraphics(float delta);
        virtual void UpdateGraphics();
        virtual void Render(RenderStage* stage);

        virtual void FramePushed(FrameStack &machine);
        virtual void FramePopped(FrameStack &machine);
        virtual void FrameMasked(FrameStack &machine);
        virtual void FrameUnmasked(FrameStack &machine);

        GameObject *findChild(std::string name);

        ICamera *mainCamera();
        RenderPipeline* mainPipeline();

        virtual std::vector<std::pair<RenderStage*, ICamera*>> renderStages() override;

        virtual Frame * frame() override;

    protected:
        virtual RenderPipeline* CreateDefaultPipeline(CameraComponent*& cameraComponent);
        void SetMainCamera(ICamera *camera);
        void SetMainPipeline(RenderPipeline* pipeline);

    private:
        std::vector<GameObject*> _children;
        bool _initialized;

        void setCurrentRenderTarget(RenderTarget *target);
        void setCurrentCamera(ICamera *camera);

        RenderTarget *currentRenderTarget;
        ICamera *currentCamera, *_mainCamera;
        RenderPipeline* _mainPipeline;
    };
}
