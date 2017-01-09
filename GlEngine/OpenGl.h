#pragma once

#include <GL/glew.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#define BUFFER_OFFSET(expr) ((char*)NULL + (expr)) 

//template <typename T>
//ENGINE_SHARED void glUniform(unsigned uniformLocation, const T &val)
//{
//    static_assert(false, "Invalid type parameter for glUniform(unsigned, T)");
//}
//
//template <>
//ENGINE_SHARED void glUniform<Matrix<2, 2>>(unsigned uniformLocation, const Matrix<2, 2> &val)
//{
//    glUniformMatrix2fv(uniformLocation, 1, false, val.getAddr());
//}
//template <>
//ENGINE_SHARED void glUniform<Matrix<3, 3>>(unsigned uniformLocation, const Matrix<3, 3> &val)
//{
//    glUniformMatrix3fv(uniformLocation, 1, false, val.getAddr());
//}
//template <>
//ENGINE_SHARED void glUniform<Matrix<4, 4>>(unsigned uniformLocation, const Matrix<4, 4> &val)
//{
//    glUniformMatrix4fv(uniformLocation, 1, false, val.getAddr());
//}
//
//template <>
//ENGINE_SHARED void glUniform<Vector<2>>(unsigned uniformLocation, const Vector<2> &val)
//{
//    glUniform2f(uniformLocation, val[0], val[1]);
//}
//template <>
//ENGINE_SHARED void glUniform<Vector<3>>(unsigned uniformLocation, const Vector<3> &val)
//{
//    glUniform3f(uniformLocation, val[0], val[1], val[2]);
//}
//template <>
//ENGINE_SHARED void glUniform<Vector<4>>(unsigned uniformLocation, const Vector<4> &val)
//{
//    glUniform4f(uniformLocation, val[0], val[1], val[2], val[3]);
//}
