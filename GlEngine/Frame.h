#pragma once

#include "IInitializable.h"
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
    class CameraComponent;
    class FrameStack;

    class ENGINE_SHARED Frame : public IInitializable
    {
    public:
        Frame();
        ~Frame();

        friend class RenderTarget;
        friend class GameObject;

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

    private:
        std::vector<GameObject*> _children;
        bool _initialized;

        void setCurrentRenderTarget(RenderTarget *target);
        void setCurrentCamera(CameraComponent *camera);

        RenderTarget *currentRenderTarget;
        CameraComponent *currentCamera;
    };
}
