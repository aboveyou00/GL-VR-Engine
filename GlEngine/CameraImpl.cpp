#include "stdafx.h"
#include "CameraImpl.h"
#include "OpenGl.h"

namespace GlEngine
{
	namespace Impl
	{
		CameraImpl::CameraImpl() : eye({ 0, 0, 0 }), target({ 0, 0, 1 }), up({ 0, 1, 0 }) {}
		CameraImpl::~CameraImpl() {}

		void CameraImpl::Apply()
		{
			Vector<3> forward = (eye - target).Normalized();
			auto side = up.Cross(forward).Normalized();
			up = forward.Cross(side);

			view = Matrix<3, 3>::FromCols(-side, up, forward).ToTransformMatrix();
			glMultMatrixf(view.getAddr());
			
			glTranslatef(-eye[0], -eye[1], -eye[2]);
		}

		void CameraImpl::Push()
		{
			glMatrixMode(GL_MODELVIEW);
			glPushMatrix();
			Apply();
		}

		void CameraImpl::Pop()
		{
			glMatrixMode(GL_MODELVIEW);
			glPopMatrix();
		}
	}
}