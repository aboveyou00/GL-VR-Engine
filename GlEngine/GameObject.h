#pragma once

#include "Transform.h"
#include "GameComponent.h"

#include "Actor.h"

#include <iterator>

namespace GlEngine
{
    class Frame;

    class ENGINE_SHARED GameObject final
    {
    public:
        GameObject(Frame *frame, std::string name);
        ~GameObject();

        friend class Frame;
        friend class GameComponent;

        //Context
        Frame *frame() const;
        std::string name() const;

        Transform transform;

        GameObject *parent() const;
        void SetParent(GameObject *parent);
        const std::vector<GameObject*> &children();

        //Behaviors
        void AddComponent(GameComponent *t);
        void RemoveComponent(GameComponent *);

        template <typename T>
        T *component()
        {
            for (auto it : components())
            {
                auto check = dynamic_cast<T*>(it);
                if (check != nullptr) return check;
            }
            return nullptr;
        }

        const std::vector<GameComponent*> &components();

        //Lifecycle hooks
        void Deactivate();
        void Activate();
        bool active() const;

        void Tick(float delta);

        void HandleEvent(Events::Event &evt);

        void TickGraphics(float delta);
        void UpdateGraphics();
        void Render(RenderTargetLayer layer);

    private:
        bool _active;
        Frame *_frame;
        std::string _name;

        GameObject *_parent;
        std::vector<GameObject*> _children;
        std::vector<GameComponent*> _components;
    };
}
