#pragma once

#include "IInitializable.h"
#include "ICamera.h"
#include "RenderTargetLayer.h"
#include <unordered_map>
#include "RenderPipeline.h"
#include "SpatialPartitions.h"

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
        std::vector<GameObject*> children();

        ICamera *mainCamera();
        RenderPipeline* mainPipeline();

        virtual std::vector<std::pair<RenderStage*, ICamera*>> renderStages() override;

        virtual Frame *frame() override;

        SpatialPartitions* spatialPartitions;
        
        template<class SpatialPartitionsClass, typename... TArgs>
        void CreateSpatialPartitions(TArgs... args)
        {
            static_assert(std::is_base_of<SpatialPartitions, SpatialPartitionsClass>::value, "The SpatialPartitionsClass template argument must inherit from SpatialPartitions");
            if (spatialPartitions != nullptr)
                delete spatialPartitions;
            spatialPartitions = new SpatialPartitionsClass(args...);
        }

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
