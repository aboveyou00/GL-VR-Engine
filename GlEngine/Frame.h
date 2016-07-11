#pragma once

#include "IGameComponent.h"
#include <unordered_map>

namespace GlEngine
{
    class GameObject;
    class GraphicsObject;
    class GraphicsContext;
    class FrameStack;
    namespace Events
    {
        class Event;
    }

    using graphics_object_map = std::unordered_map<GameObject*, GraphicsObject*>;
    using graphics_context_map = std::unordered_map<GraphicsContext*, graphics_object_map>;

    class ENGINE_SHARED Frame : public IGameComponent
    {
    public:
        Frame();
        ~Frame();

        bool Initialize();
        void Shutdown();
        void Tick(float delta);

        virtual void FramePushed(FrameStack &machine);
        virtual void FramePopped(FrameStack &machine);
        virtual void FrameMasked(FrameStack &machine);
        virtual void FrameUnmasked(FrameStack &machine);

        template <typename T, typename... TArgs>
        T *CreateGameObject(TArgs... args)
        {
            T *t = new T(args...);
            objects.push_back(t);
            t->AddToFrame(this);
            if (initialized) t->Initialize();
            return t;
        }
        void DestroyGameObject(GameObject *gobj);
        bool OwnsGameObject(GameObject *gobj);

        void Update(GraphicsContext &ctx);

        virtual void HandleEvent(Events::Event &evt);

    private:
        std::vector<GameObject*> objects;
        bool initialized;

        graphics_context_map context_map;
    };
}
