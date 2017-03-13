#include "stdafx.h"
#include "PerspectiveViewPort.h"
#include "MatrixStack.h"

static float fovToRatio(float angle)
{
    return tan(angle / 2);
}

namespace GlEngine
{
    PerspectiveViewPort::PerspectiveViewPort(float fovAngle, float near, float far)
        : fovAngle(fovAngle), nearVal(near), farVal(far)
    {
    }
    PerspectiveViewPort::~PerspectiveViewPort()
    {
    }

    void PerspectiveViewPort::Push()
    {
        float viewWidth, viewHeight;
        if (width() > height())
        {
            viewHeight = 1.0;
            viewWidth = (float)width() / height();
        }
        else
        {
            viewWidth = 1.0;
            viewHeight = (float)height() / width();
        }

        auto fov = fovToRatio(fovAngle);
        viewWidth *= fov;
        viewHeight *= fov;

        MatrixStack::Projection.push(Matrix<4, 4>::Frustum(-viewWidth / 2, viewWidth / 2, -viewHeight / 2, viewHeight / 2, nearVal, farVal));
    }
    void PerspectiveViewPort::Pop()
    {
        MatrixStack::Projection.pop();
    }

    void PerspectiveViewPort::SetNear(float nearVal)
    {
        this->nearVal = nearVal;
    }
    void PerspectiveViewPort::SetFar(float farVal)
    {
        this->farVal = farVal;
    }

    void PerspectiveViewPort::SetFov(float fovAngle)
    {
        this->fovAngle = fovAngle;
    }

    float PerspectiveViewPort::near()
    {
        return nearVal;
    }
    float PerspectiveViewPort::far()
    {
        return farVal;
    }

    float PerspectiveViewPort::fov()
    {
        return fovAngle;
    }
}
