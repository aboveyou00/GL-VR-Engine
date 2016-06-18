#pragma once

#include "EngineShared.h"
#include "IComponent.h"
#include "TransformedGraphicsObject.h"

namespace GlEngine
{
	namespace Impl
	{
		class GraphicsContextImpl;
	}

	class ENGINE_SHARED GraphicsContext : public IComponent 
	{
	public:
		GraphicsContext();
		~GraphicsContext();

		bool Initialize();
		void Shutdown();

		void AddGraphicsObject(TransformedGraphicsObject * graphicsObject);
		void RemoveGraphicsObject(TransformedGraphicsObject * graphicsObject);
		
		void Render();

	private:
		Impl::GraphicsContextImpl * pimpl;
	};
}