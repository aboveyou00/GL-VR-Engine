#include "stdafx.h"
#include "TransformedGraphicsObjectImpl.h"
#include "OpenGl.h"

namespace GlEngine
{
	namespace Impl
	{
		void TransformedGraphicsObjectImpl::Render() const
		{
			glMatrixMode(GL_MODELVIEW);
			glPushMatrix();
			glMultMatrixf(Matrix<4, 4>::TranslateMatrix(position).getAddr());
			glMultMatrixf(orientation.getAddr());
			
			graphicsObject->Render();

			glPopMatrix();
		}
	}
}