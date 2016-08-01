#include "stdafx.h"
#include "CameraImpl.h"
#include "OpenGl.h"
#include "MatrixStack.h"

namespace GlEngine
{
	namespace Impl
	{
		CameraImpl::CameraImpl() : eye({ 0, 0, 0 }), forward({ 0, 0, 1 }), up({ 0, 1, 0 }), gameObject(nullptr) {}
		CameraImpl::~CameraImpl() {}

		void CameraImpl::Push()
		{
			if (gameObject != nullptr)
			{
				eye = gameObject->position;
				forward = gameObject->orientation * Vector<3>{ 0, 0, 1 };
				up = gameObject->orientation * Vector<3>{ 0, 1, 0 };
			}

            Vector<3> forwardN = forward.Normalized();
            auto side = up.Cross(forwardN).Normalized();
            up = forwardN.Cross(side);

            view = Matrix<3, 3>::FromCols(-side, up, forwardN).ToTransformMatrix();
            
            MatrixStack::ModelView.mult(view * Mat3T<float>::TranslateMatrix(-eye));
		}

		void CameraImpl::Pop()
		{
            MatrixStack::ModelView.pop();
		}
	}
}
