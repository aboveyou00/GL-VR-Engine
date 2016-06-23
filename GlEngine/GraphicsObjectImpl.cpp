#include "stdafx.h"
#include "GraphicsObjectImpl.h"
#include "OpenGl.h"

namespace GlEngine
{
	namespace Impl
	{
		GraphicsObjectImpl::GraphicsObjectImpl() 
		{
			magic = 54321;
		}
		
		GraphicsObjectImpl::~GraphicsObjectImpl() 
		{
		}

		void GraphicsObjectImpl::Render()
		{
			glBegin(GL_TRIANGLES);

			glColor3d(0.0, 1.0, 0.0);
			glVertex3d(0.4, 0.4, 0.5);
			glVertex3d(0.4, 0, 0.5);
			glVertex3d(0, 0.4, 0.5);

			glEnd();

			//TODO: actual things
		}
	}
}