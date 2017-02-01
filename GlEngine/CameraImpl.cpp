#include "stdafx.h"
#include "CameraImpl.h"
#include "OpenGl.h"
#include "MatrixStack.h"
#include "Environment.h"

namespace GlEngine
{
    namespace Impl
    {
        CameraImpl::CameraImpl() : eye({ 0, 0, 0 }), forward({ 0, 0, 1 }), up({ 0, 1, 0 }), gameObject(nullptr) {}
        CameraImpl::~CameraImpl() {}

        void CameraImpl::Push()
        {
            Vector<3> side, forwardN;
            if (gameObject != nullptr)
            {
                ShaderFactory::Environment::GetInstance().SetCameraPosition(gameObject->position);
                eye = gameObject->position;
                forwardN = gameObject->orientation * Vector<3>{ 0, 0, 1 };
                side = gameObject->orientation * Vector<3>{ 1, 0, 0 };
                up = gameObject->orientation * Vector<3>{ 0, 1, 0 };
            }
            else
            {
                ShaderFactory::Environment::GetInstance().SetCameraPosition({ 0, 0, 0 });
                forwardN = forward.Normalized();
                side = up.Cross(forwardN).Normalized();
                up = forwardN.Cross(side);
            }
            view = Matrix<3, 3>::FromCols(-side, up, forwardN).ToTransformMatrix();

            MatrixStack::View.mult(Mat3T<float>::TranslateMatrix(-eye) * view);
        }

        void CameraImpl::Pop()
        {
            MatrixStack::View.pop();
        }
    }
}
