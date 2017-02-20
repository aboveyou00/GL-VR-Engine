#pragma once

#include "RenderTarget.h"

namespace GlEngine
{
    class Window;
    class CameraComponent;

    class ENGINE_SHARED WindowRenderTarget : public RenderTarget
    {
    public:
        WindowRenderTarget(Window *window, CameraComponent *camera);
        ~WindowRenderTarget();

        virtual std::string name() override;
    };
}
