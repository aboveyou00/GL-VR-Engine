#pragma once

#include "IComponent.h"
#include "VbObject.h"
#include "Shader.h"

namespace GlEngine
{
	namespace Impl
	{
		class GraphicsObjectImpl;
	}

	class ENGINE_SHARED GraphicsObject : public IComponent
	{
	public:
		GraphicsObject();
		~GraphicsObject();

        bool Initialize() override;
        void Shutdown() override;
		
		virtual void PreRender();
		virtual void Render();

	};
}
