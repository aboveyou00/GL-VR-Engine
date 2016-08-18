#pragma once

#include "IGraphicsComponent.h"

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

        void Render();
		virtual void PreRender();
        virtual void RenderImpl() = 0;
        virtual void PostRender();

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
