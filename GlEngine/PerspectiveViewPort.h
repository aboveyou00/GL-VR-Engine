#pragma once

#include "ViewPort.h"
#include "MathUtils.h"

namespace GlEngine
{
    class ENGINE_SHARED PerspectiveViewPort : public ViewPort
    {
    public:
        PerspectiveViewPort(float fovAngle = 60deg, float nearVal = 1, float farVal = 100);
        ~PerspectiveViewPort();

        virtual void Push() override;
        virtual void Pop() override;

        virtual void SetNear(float nearVal);
        virtual void SetFar(float farVal);

        virtual void SetFov(float fovAngle);

        float near();
        float far();

        float fov();

    protected:
        float nearVal;
        float farVal;

        float fovAngle;
    };
}
