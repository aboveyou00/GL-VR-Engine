#pragma once

#include "IInitializable.h"
#include "OpenGl.h"
#include "ViewPort.h"
#include "RenderTargetLayer.h"
#include "RenderTargetViewMode.h"

namespace GlEngine
{
    class CameraComponent;

    namespace Impl
    {
        class RenderTargetImpl : public IAsyncInitializable
        {
        public:
            RenderTargetImpl(CameraComponent *camera);
            ~RenderTargetImpl();

            virtual bool InitializeAsync() override;
            virtual void ShutdownAsync() override;
            virtual bool InitializeGraphics() override;
            virtual void ShutdownGraphics() override;

            virtual std::string name() override;

            virtual void MakeCurrentTarget();

            inline bool GetShouldRender()
            {
                return shouldRender;
            }

            virtual void Prepare();
            virtual void PrePush();
            virtual void Push(RenderTargetLayer layer, RenderTargetViewMode viewMode, Matrix<4, 4> viewMatrix);
            virtual void Pop(RenderTargetLayer layer);
            virtual void PostPop();

            virtual void Flip();

            virtual void SetViewPort(RenderTargetLayer layer, ViewPort *viewPort);
            ViewPort *viewPort(RenderTargetLayer layer);

            static const int layerCount = (int)std::numeric_limits<RenderTargetLayer>::max() - (int)std::numeric_limits<RenderTargetLayer>::min() + 1;
            ViewPort* viewPorts[layerCount];

            CameraComponent *camera();

        private:
            bool shouldRender;
            CameraComponent *_camera;
        };
    }
}
