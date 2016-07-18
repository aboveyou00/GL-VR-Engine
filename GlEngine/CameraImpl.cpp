#include "stdafx.h"
#include "CameraImpl.h"
#include "OpenGl.h"
#include "MatrixStack.h"

namespace GlEngine
{
	namespace Impl
	{
		CameraImpl::CameraImpl() : eye({ 0, 0, 0 }), target({ 0, 0, 1 }), up({ 0, 1, 0 }) {}
		CameraImpl::~CameraImpl() {}

		void CameraImpl::Push()
		{
            Vector<3> forward = (eye - target).Normalized();
            auto side = up.Cross(forward).Normalized();
            up = forward.Cross(side);

            view = Matrix<3, 3>::FromCols(-side, up, forward).ToTransformMatrix();
            
            ModelViewMatrixStack.push(
                ModelViewMatrixStack.head() * view * Mat3T<float>::TranslateMatrix(-eye)
            );
            ModelViewMatrixStack.tell_gl();
		}

		void CameraImpl::Pop()
		{
            ModelViewMatrixStack.pop();
            ModelViewMatrixStack.tell_gl();
		}
	}
}
