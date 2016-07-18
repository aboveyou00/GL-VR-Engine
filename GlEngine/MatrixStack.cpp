#include "stdafx.h"
#include "MatrixStack.h"

#include "OpenGl.h"

namespace GlEngine
{
    MatrixStack::MatrixStack(int gl_enum)
        : gl_enum(gl_enum)
    {
        stack[idx] = Mat3T<float>::Identity();
    }
    MatrixStack::~MatrixStack()
    {
        if (remoteStack != nullptr)
        {
            delete remoteStack;
            remoteStack = nullptr;
        }
        idx = 0;
        stack[idx] = Mat3T<float>::Identity();
    }

    static MatrixStack _projection(0), _modelView(1);
    MatrixStack &MatrixStack::Projection = _projection;
    MatrixStack &MatrixStack::ModelView = _modelView;

    const Matrix<4, 4> &MatrixStack::push(const Matrix<4, 4> &matrix)
    {
        idx++;
        if (idx >= MAX_LOCAL_STACK)
        {
            if (remoteStack == nullptr) remoteStack = new std::vector<Matrix<4, 4>>();
            if (remoteStack->size() == idx - MAX_LOCAL_STACK) remoteStack->push_back(matrix);
            else remoteStack->at(idx - MAX_LOCAL_STACK) = matrix;
        }
        else stack[idx] = matrix;
        return matrix;
    }
    const Matrix<4, 4> &MatrixStack::mult(const Matrix<4, 4> &matrix)
    {
        auto &retval = push(head() * matrix);
        tell_gl();
        return retval;
    }
    const Matrix<4, 4> &MatrixStack::pop()
    {
        auto &retval = (idx < MAX_LOCAL_STACK) ? stack[idx] : (*remoteStack)[idx - MAX_LOCAL_STACK];
        idx--;
        tell_gl();
        return retval;
    }
    const Matrix<4, 4> &MatrixStack::dup()
    {
        auto &retval = push(head());
        tell_gl();
        return retval;
    }
    const Matrix<4, 4> &MatrixStack::head()
    {
        if (idx < MAX_LOCAL_STACK) return stack[idx];
        else return (*remoteStack)[idx - MAX_LOCAL_STACK];
    }

    void MatrixStack::tell_gl()
    {
        if (gl_enum == -1) return;
        glUniformMatrix4fv(gl_enum, 1, false, head().getAddr());
    }
}
