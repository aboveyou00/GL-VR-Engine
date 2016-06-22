#pragma once

#include "EngineShared.h"
#include "GraphicsObject.h"

namespace GlEngine
{
	namespace Impl
	{
		class TransformedGraphicsObjectImpl;
	}

	class ENGINE_SHARED TransformedGraphicsObject 
	{
	public:
		TransformedGraphicsObject(GraphicsObject & obj);
		TransformedGraphicsObject(GraphicsObject * obj);
		~TransformedGraphicsObject();

		void Render();

	private:
		Impl::TransformedGraphicsObjectImpl * pimpl;
	};
}