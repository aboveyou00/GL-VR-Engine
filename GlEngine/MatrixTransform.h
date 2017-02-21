#pragma once

#include "MatrixStack.h"

namespace GlEngine
{
    struct Transform;

    class ENGINE_SHARED MatrixTransform
    {
    public:
        MatrixTransform(MatrixStack &stack, Transform &transform);
        ~MatrixTransform();

    private:
        MatrixStack *_stack;
    };
}
