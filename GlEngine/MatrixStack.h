#pragma once

#include "Matrix.h"

namespace GlEngine
{
    class ENGINE_SHARED MatrixStack
    {
    public:
        MatrixStack();
        ~MatrixStack();

        static MatrixStack &Projection;
        static MatrixStack &Model;
        static MatrixStack &View;

    public:
        const Matrix<4, 4> &push(const Matrix<4, 4> &matrix);
        const Matrix<4, 4> &mult(const Matrix<4, 4> &matrix);
        const Matrix<4, 4> &pop();
        const Matrix<4, 4> &dup();
        const Matrix<4, 4> &head();

        inline unsigned GetStackSize()
        {
            return idx;
        }

    private:
        unsigned idx = 0;
        int gl_enum = 0;
        static const unsigned MAX_LOCAL_STACK = 12;
        Matrix<4, 4> stack[MAX_LOCAL_STACK];
        std::vector<Matrix<4, 4>> *remoteStack;
    };
}
