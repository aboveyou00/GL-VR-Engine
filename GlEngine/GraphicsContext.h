#pragma once

#include "EngineShared.h"
#include "IComponent.h"
#include "TransformedGraphicsObject.h"
#include "Camera.h"
#include "GameObject.h"
#include "RenderTarget.h"
#include <unordered_map>

namespace GlEngine
{
    class GraphicsObject;
    class FrameStack;
    using graphics_object_map = std::unordered_map<GameObject*, GraphicsObject*>;
    
    class ENGINE_SHARED GraphicsContext : public IComponent
    {
    public:
        GraphicsContext(FrameStack *frames);
        ~GraphicsContext();

        std::list<TransformedGraphicsObject> transformed;
        
        Camera camera;

        bool Initialize();
        void Shutdown();

        void AddRenderTarget(RenderTarget *renderTarget);

        void Update(const graphics_object_map &objs);
        void UpdateCamera(GameObject*);
        void Render();

        void Tick(float delta);

        rt_mutex &GetMutex();

        const char *name() override;
    
    private:
        rt_mutex _mux;

        static const int MAX_RENDER_TARGETS = 16;
        RenderTarget *renderTargets[MAX_RENDER_TARGETS];
        size_t renderTargetCount = 0;
        FrameStack *frames;
    };
}
