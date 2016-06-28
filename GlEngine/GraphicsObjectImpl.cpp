#include "stdafx.h"
#include "GraphicsObjectImpl.h"
#include "OpenGl.h"

namespace GlEngine
{
	namespace Impl
	{
		GraphicsObjectImpl::GraphicsObjectImpl() 
		{
			vbo = 0;
		}
		
		GraphicsObjectImpl::~GraphicsObjectImpl() 
		{
		}

		void GraphicsObjectImpl::Render()
		{
			if (vbo != 0)
			{
				glBindBuffer(GL_VERTEX_ARRAY, vbo);
			}
		}
	}
}