#include "stdafx.h"
#include "PerspectiveViewPort.h"
#include "MatrixStack.h"

namespace GlEngine
{
    PerspectiveViewPort::PerspectiveViewPort()
    {
    }
    PerspectiveViewPort::~PerspectiveViewPort()
    {
    }

    void PerspectiveViewPort::Push()
    {
        //relativeCamera.Apply();

        float viewWidth, viewHeight;
        if (width > height)
        {
            viewHeight = 1.0;
            viewWidth = (float)width / height;
        }
        else
        {
            viewWidth = 1.0;
            viewHeight = (float)height / width;
        }

        float nearVal = 1.f;
        float farVal = 100.f;

        MatrixStack::Projection.push(Mat3T<float>::Frustum(-viewWidth / 2, viewWidth / 2, -viewHeight / 2, viewHeight / 2, nearVal, farVal));
        MatrixStack::Projection.tell_gl();
    }

    void PerspectiveViewPort::Pop()
    {
        MatrixStack::Projection.pop();
        MatrixStack::Projection.tell_gl();
    }

    void PerspectiveViewPort::SetNear(float nearVal)
    {
        this->nearVal = nearVal;
    }

    void PerspectiveViewPort::SetFar(float farVal)
    {
        this->farVal = farVal;
    }
}