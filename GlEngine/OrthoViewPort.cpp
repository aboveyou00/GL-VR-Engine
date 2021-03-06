#include "stdafx.h"
#include "OrthoViewPort.h"
#include "MatrixStack.h"

namespace GlEngine
{
    OrthoViewPort::OrthoViewPort()
    {
    }
    OrthoViewPort::~OrthoViewPort()
    {
    }

    void OrthoViewPort::Push()
    {
        float left = -(float)width() / 2;
        float right = (float)width() / 2;
        float top = -(float)height() / 2;
        float bottom = (float)height() / 2;
        MatrixStack::Projection.push(Matrix<4, 4>::Ortho(left, right, bottom, top, nearVal, farVal));
    }

    void OrthoViewPort::Pop()
    {
        MatrixStack::Projection.pop();
    }

    void OrthoViewPort::SetNear(float nearVal)
    {
        this->nearVal = nearVal;
    }

    void OrthoViewPort::SetFar(float farVal)
    {
        this->farVal = farVal;
    }
}
