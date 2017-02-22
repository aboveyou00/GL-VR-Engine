#pragma once

#include "IAsyncInitializable.h"
#include "RenderTargetLayer.h"

namespace GlEngine::Events
{
    class Event;
}

namespace GlEngine
{
    class GameObject;
    class Frame;

    class ENGINE_SHARED GameComponent : public IAsyncInitializable
    {
    public:
        GameComponent(std::string name);
        ~GameComponent();

        friend class GameObject;

        GameObject *gameObject() const;
        Frame *frame() const;

        //Async Initialize
        virtual bool InitializeAsync() override;
        virtual void ShutdownAsync() override;
        virtual bool InitializeGraphics() override;
        virtual void ShutdownGraphics() override;

        virtual bool isReady() override;

        virtual std::string name() override;

        //Lifecycle hooks
        void Deactivate();
        void Activate();
        bool active() const;

        virtual void Tick(float delta);

        virtual void HandleEvent(Events::Event &evt);

        virtual void TickGraphics(float delta);
        virtual void UpdateGraphics();
        virtual void Render(RenderTargetLayer layer);

    private:
        GameObject *_gameObject;
        bool _active;
        std::string _name;
    };
}
