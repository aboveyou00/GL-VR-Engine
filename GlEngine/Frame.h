#pragma once

#include "IInitializable.h"
#include "ICamera.h"
#include "RenderTargetLayer.h"
#include <unordered_map>

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

    class ENGINE_SHARED Frame : public IInitializable, public ICamera
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
        virtual void Render(RenderTargetLayer layer);

        virtual void FramePushed(FrameStack &machine);
        virtual void FramePopped(FrameStack &machine);
        virtual void FrameMasked(FrameStack &machine);
        virtual void FrameUnmasked(FrameStack &machine);

        GameObject *findChild(std::string name);

        virtual void Push() override;
        virtual void Pop() override;

        virtual Vector<3> clearColor() override;

        virtual bool isReady() override;

        ICamera *mainCamera();

    protected:
        virtual CameraComponent *CreateDefaultCamera();
        void SetMainCamera(ICamera *camera);

    private:
        std::vector<GameObject*> _children;
        bool _initialized;

        void setCurrentRenderTarget(RenderTarget *target);
        void setCurrentCamera(ICamera *camera);

        virtual Frame *frame() override;

        RenderTarget *currentRenderTarget;
        ICamera *currentCamera, *_mainCamera;
    };
}
