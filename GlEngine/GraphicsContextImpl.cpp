#include "stdafx.h"
#include "GraphicsContextImpl.h"

namespace GlEngine
{
	namespace Impl
	{
		GraphicsContextImpl::GraphicsContextImpl() {}
		GraphicsContextImpl::~GraphicsContextImpl() {}
		
		bool GraphicsContextImpl::Initialize()
		{
			return true;
		}

		void GraphicsContextImpl::Shutdown()
		{
		}

		void GraphicsContextImpl::AddGraphicsObject(TransformedGraphicsObject * graphicsObject)
		{
			ScopedLock slock(_lock);
			objects.insert(graphicsObject);
		}

		void GraphicsContextImpl::RemoveGraphicsObject(TransformedGraphicsObject * graphicsObject)
		{
			ScopedLock slock(_lock);
			objects.erase(graphicsObject);
		}

		void GraphicsContextImpl::Render() 
		{
			ScopedLock slock(_lock);
			for (auto it = objects.begin(); it != objects.end(); it++)
			{
				(*it)->Render();
			}
		}
	}
}