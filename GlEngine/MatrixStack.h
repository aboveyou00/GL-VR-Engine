#pragma once

#include "Matrix.h"

namespace GlEngine
{
    template <int rows = 4, int cols = 4, typename ElemT = float>
    class MatrixStack
    {
    public:
        MatrixStack(int gl_enum = -1)
            : gl_enum(gl_enum)
        {
            push(Mat3T<float>::Identity());
        }
        ~MatrixStack()
        {
            if (remoteStack != nullptr)
            {
                delete remoteStack;
                remoteStack = nullptr;
            }
            idx = 0;
            push(Mat3T<float>::Identity());
        }

        static MatrixStack<> &Projection = _projection, &ModelView = _modelView;

    private:
        static MatrixStack<> _projection(0), _modelView(1);

    public:

        const Matrix<rows, cols, ElemT> &push(const Matrix<rows, cols, ElemT> &matrix)
        {
            idx++;
            if (idx < MAX_LOCAL_STACK) return stack[idx] = matrix;
            if (remoteStack == nullptr) remoteStack = new std::vector<Matrix<rows, cols, ElemT>>();
            remoteStack->push_back(matrix);
            return matrix;
        }
        const Matrix<rows, cols, ElemT> &pop()
        {
            auto &retval = (idx < MAX_LOCAL_STACK) ? stack[idx] : (*remoteStack)[idx - MAX_LOCAL_STACK];
            idx--;
            return retval;
        }
        const Matrix<rows, cols, ElemT> &dup()
        {
            return push(head());
        }
        Matrix<rows, cols, ElemT> &head()
        {
            if (idx < MAX_LOCAL_STACK) return stack[idx];
            else return (*remoteStack)[idx - MAX_LOCAL_STACK];
        }

        void tell_gl()
        {
            if (gl_enum == -1) return;
            glUniformMatrix4fv(gl_enum, 1, false, head().getAddr());
        }

    private:
        unsigned idx = 0;
        int gl_enum = 0;
        static const unsigned MAX_LOCAL_STACK = 12;
        Matrix<rows, cols, ElemT> stack[MAX_LOCAL_STACK];
        std::vector<Matrix<rows, cols, ElemT>> *remoteStack;
    };
}
