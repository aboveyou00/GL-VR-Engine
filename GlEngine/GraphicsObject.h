#pragma once

#include "IGraphicsComponent.h"
#include "RenderTargetLayer.h"

namespace GlEngine
{
	namespace Impl
	{
		class GraphicsObjectImpl;
	}

	class ENGINE_SHARED GraphicsObject : public IGraphicsComponent
	{
	public:
		GraphicsObject(bool autoinit = true, bool instanced = false);
		~GraphicsObject();

        bool Initialize() override;
        void Shutdown() override;
        bool InitializeGraphics() override;
        void ShutdownGraphics() override;

        void Render(RenderTargetLayer layer);
		virtual void PreRender(RenderTargetLayer layer);
        virtual void RenderImpl(RenderTargetLayer layer) = 0;
        virtual void PostRender(RenderTargetLayer layer);

        inline bool IsInstanced()
        {
            return isInstanced;
        }
        inline unsigned GetInstanceCount()
        {
            return instanceCount;
        }

    protected:
        bool initialized, graphicsInitialized;

        inline void SetInstanceCount(unsigned count)
        {
            instanceCount = count;
        }

    private:
        bool isInstanced;
        unsigned instanceCount;
	};
}
