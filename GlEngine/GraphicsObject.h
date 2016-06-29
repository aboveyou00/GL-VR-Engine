#pragma once

#include "EngineShared.h"
#include "IComponent.h"

namespace GlEngine
{
	namespace Impl
	{
		class GraphicsObjectImpl;
	}

	class ENGINE_SHARED GraphicsObject : IComponent
	{
	public:
		GraphicsObject();
		~GraphicsObject();

        bool Initialize();
        void Shutdown();

		void Render();

	private:
		Impl::GraphicsObjectImpl *pimpl;
	};
}