#include "stdafx.h"
#include "GraphicsObjectImpl.h"
#include "OpenGl.h"

namespace GlEngine
{
	namespace Impl
	{
		void GraphicsObjectImpl::Render()
		{
			glBegin(GL_TRIANGLES);
			glColor3d(1, 1, 1);
			glVertex3d(0, 0, -5);
			glVertex3d(10, 0, 5);
			glVertex3d(0, 10, 0);
			glEnd();

			//TODO: actual things
		}
	}
}