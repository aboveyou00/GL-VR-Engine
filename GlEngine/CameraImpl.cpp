#include "stdafx.h"
#include "CameraImpl.h"
#include "OpenGl.h"

namespace GlEngine
{
	namespace Impl
	{
		CameraImpl::CameraImpl() {}
		CameraImpl::~CameraImpl() {}

		void CameraImpl::ApplyView()
		{
			Vector<3> forward = (center - eye).Normalized();
			Vector<3> side = forward.Cross(up).Normalized();
			up = side.Cross(forward);

			view = Matrix<3, 3>::FromCols(-side, -up, -forward).ToTransformMatrix();

			glMatrixMode(GL_MODELVIEW);
			glMultMatrixf(view.getAddr());
			
			float mat[16];
			glGetFloatv(GL_MODELVIEW_MATRIX, mat);
			auto Mat = Matrix<4, 4>(mat);
			
			glTranslatef(-eye[0], -eye[1], -eye[2]);
		}

		void CameraImpl::ApplyProjection()
		{
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			glOrtho(left, right, bottom, top, nearVal, farVal);
			
			float p[16];
			glGetFloatv(GL_PROJECTION_MATRIX, p);
			Matrix<4, 4> mat(p);
		}
	}
}