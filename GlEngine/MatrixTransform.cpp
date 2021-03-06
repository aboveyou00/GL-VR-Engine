#include "stdafx.h"
#include "MatrixTransform.h"
#include "Transform.h"

namespace GlEngine
{
    MatrixTransform::MatrixTransform(MatrixStack &stack, Transform &transform)
        : _stack(&stack)
    {
        _stack->mult(transform.matrix());
    }
    MatrixTransform::~MatrixTransform()
    {
        _stack->pop();
    }
}
