#pragma once

#include "Vector.h"
#include <iomanip>

template <int rows, int cols, typename ElemT = float>
struct Matrix
{
public:
    template <typename... Args>
    Matrix(Args... vals)
    {
        for (auto q = 0; q < rows; q++)
            for (auto w = 0; w < cols; w++)
                values[q][w] = 0;
        initialize(vals...);
    }
    Matrix(ElemT *vals)
    {
        for (auto i = 0; i < rows * cols; i++)
            values[i / cols][i%cols] = vals[i];
    }
    ~Matrix()
    {
    }

    static Matrix<rows, cols, ElemT> Identity()
    {
        static_assert(rows == cols, "Identity cannot be called for a non-square matrix");
        Matrix<rows, rows, ElemT> result;
        for (auto q = 0; q < rows; q++)
            result.values[q][q] = (ElemT)1;
        return result;
    }

    static Matrix<rows, cols, ElemT> TranslateMatrix(Vector<rows - 1, ElemT> translateVec)
    {
        static_assert(rows == cols && rows >= 2, "Matrix::TranslateMatrix can only be applied to square matrices with sizes of at least 2*2");
        auto result = Matrix<rows, cols, ElemT>::Identity();
        for (auto q = 0; q < rows - 1; q++)
        {
            result.values[rows - 1][q] = translateVec[q];
        }
        return result;
    }
    static Matrix<3, 3, ElemT> TranslateMatrix(ElemT x, ElemT y)
    {
        static_assert(rows == 3 && cols == 3, "Matrix::TranslateMatrix(ElemT, ElemT) can only be applied to 3*3 matrices");
        return Matrix<3, 3, ElemT> { 1, 0, 0,
                              0, 1, 0,
                              x, y, 1 };
    }
    static Matrix<4, 4, ElemT> TranslateMatrix(ElemT x, ElemT y, ElemT z)
    {
        static_assert(rows == 4 && cols == 4, "Matrix::TranslateMatrix(ElemT, ElemT, ElemT) can only be applied to 4*4 matrices");
        return Matrix<4, 4, ElemT> { 1, 0, 0, 0,
                                     0, 1, 0, 0,
                                     0, 0, 1, 0,
                                     x, y, z, 1 };
    }
    static Matrix<rows, cols, ElemT> Rotate2dMatrix(ElemT theta)
    {
        static_assert(rows == 3 && cols == 3, "Matrix::RotateMatrix(ElemT) can only be applied to 3*3 matrices");
        return Matrix<3, 3, ElemT> { cos(theta), -sin(theta), 0,
                                     sin(theta),  cos(theta), 0,
                                     0, 0, 1 };
    }
    static Matrix<rows, cols, ElemT> ScaleMatrix(Vector<rows - 1, ElemT> scaleVec)
    {
        static_assert(rows == cols && rows >= 2, "Matrix::ScaleMatrix can only be applied to square matrices with sizes of at least 2*2");
        auto result = Matrix<rows, cols, ElemT>::Identity();
        for (auto q = 0; q < rows - 1; q++)
        {
            result.values[q][q] = scaleVec[q];
        }
        return result;
    }
    static Matrix<3, 3, ElemT> ScaleMatrix(ElemT sx, ElemT sy)
    {
        static_assert(rows == 3 && cols == 3, "Matrix::ScaleMatrix(ElemT, ElemT) can only be applied to 3*3 matrices");
        return Matrix<3, 3, ElemT> { sx, 0, 0,
                                     0, sy, 0,
                                     0, 0, 1 };
    }
    static Matrix<4, 4, ElemT> ScaleMatrix(ElemT sx, ElemT sy, ElemT sz)
    {
        static_assert(rows == 4 && cols == 4, "Matrix::SCaleMatrix(ElemT, ElemT, ElemT) can only be applied to 4*4 matrices");
        return Matrix<4, 4, ElemT> { sx, 0, 0, 0,
                                     0, sy, 0, 0,
                                     0, 0, sz, 0,
                                     0, 0, 0, 1 };
    }
    static Matrix<rows, cols, ElemT> ScaleMatrix(ElemT scale)
    {
        static_assert(rows == cols && rows >= 2, "Matrix::ScaleMatrix(ElemT) can only be applied to square matrices with sizes of at least 2*2");
        auto result = Matrix<rows, cols, ElemT>::Identity();
        for (auto q = 0; q < rows - 1; q++)
        {
            result.values[q][q] = scale;
        }
        result.values[rows - 1][rows - 1] = 1;
        return result;
    }

    static Matrix<rows, cols, ElemT> RotationMatrixNormalized(ElemT theta, Vector<rows - 1, ElemT> axis)
    {
        static_assert(rows == 4 && cols == 4, "Matrix::RotationMatrixNormalized(ElemT) can only be applied to 4*4 matrices");
        
        auto u = axis[0], v = axis[1], w = axis[3];
        auto u2 = u*u, v2 = v*v, w2 = w*w;
        auto uv = u*v, uw = u*w, vw = v*w;
        auto sinTheta = sin(theta);
        auto cosTheta = cos(theta);
        auto oneMinusCosTheta = 1 - cosTheta;

        return Matrix<4, 4, ElemT> 
        {
            u2 + (1 - u2)*cosTheta,               uv * oneMinusCosTheta - w * sinTheta, uw * oneMinusCosTheta + v * sinTheta, 0,
            uv * oneMinusCosTheta + w * sinTheta, v2 + (1 - v2) * cosTheta,             vw * oneMinusCosTheta - u * sinTheta, 0,
            uw * oneMinusCosTheta - v * sinTheta, vw * oneMinusCosTheta + u * sinTheta, w2 + (1 - w2) * cosTheta,             0,
            0,                                    0,                                    0,                                    1
        };
    }

    static Matrix<rows, cols, ElemT> RotateMatrix(ElemT radians, Vector<rows-1, ElemT> axis)
    {
        static_assert(rows == 4 && cols == 4, "Matrix::RotationMatrix(ElemT) can only be applied to 4*4 matrices");
        return RotationMatrixNormalized(radians, axis.Normalized());
    }

    static Matrix<rows, cols, ElemT> PitchMatrix(ElemT theta)
    {
        /// <summary>Rotates about the Z axis
        /// </summary>

        static_assert(rows == 4 && cols == 4, "Matrix::PitchMatrix(ElemT) can only be applied to 4*4 matrices");
        return Matrix<4, 4, ElemT> { cos(theta), -sin(theta), 0, 0,
                                     sin(theta), cos(theta),  0, 0,
                                     0,          0,           1, 0,
                                     0,          0,           0, 1 };
    }

    static Matrix<rows, cols, ElemT> YawMatrix(ElemT theta)
    {
        /// <summary>Rotates about the Y axis
        /// </summary>

        static_assert(rows == 4 && cols == 4, "Matrix::YawMatrix(ElemT) can only be applied to 4*4 matrices");
        return Matrix<4, 4, ElemT> { cos(theta), 0, -sin(theta), 0,
                                     0,          1,           0, 0,
                                     sin(theta), 0,  cos(theta), 0,
                                     0,          0,           0, 1 };
    }

    static Matrix<rows, cols, ElemT> RollMatrix(ElemT theta)
    {
        /// <summary>Rotates about the X axis
        /// </summary>

        static_assert(rows == 4 && cols == 4, "Matrix::RollMatrix(ElemT) can only be applied to 4*4 matrices");
        return Matrix<4, 4, ElemT> { 1,          0,           0, 0,
                                     0, cos(theta), -sin(theta), 0,
                                     0, sin(theta),  cos(theta), 0,
                                     0,          0,           0, 1 };
    }

    inline static Matrix<rows, cols, ElemT> FromVector(Vector<rows, ElemT> vec)
    {
        static_assert(cols == 1, "Matrix::FromVector cannot be called for matrices with more than one column");
        Matrix<rows, cols, ElemT> result;
        for (auto q = 0; q < rows; q++)
        {
            result.values[q][0] = vec[q];
        }
        return result;
    }

    Matrix<cols, rows, ElemT> Transpose() const
    {
        Matrix<cols, rows, ElemT> result;
        for (auto q = 0; q < rows; q++)
            for (auto w = 0; w < cols; w++)
                result.values[w][q] = values[q][w];
        return result;
    }

    template <typename = std::enable_if_t<rows == 1 || cols == 1 || rows == cols>>
    Vector<rows, ElemT> AsVector() const
    {
        static_assert(cols == 1 || rows == cols, "Matrix::FromVector cannot be applied for matrices unless they are square or they only have one column");
        ElemT vals[rows];
        for (auto q = 0; q < rows; q++)
        {
            vals[q] = (rows == 1) ? values[0][q] :
                      (cols == 1) ? values[q][0] : 
                                    values[q][q];
        }
        return Vector<rows, ElemT>(vals);
    }
    //Vector<cols - 1, ElemT> AsTranslatedVector() const
    //{
    //    static_assert(rows == 1 && cols >= 2, "Matrix::AsTranslatedVector called with invalid template parameters");
    //    ElemT vals[cols - 1];
    //    for (auto q = 0; q < cols - 1; q++)
    //    {
    //        vals[q] = values[0][q];
    //    }
    //    return Vector<cols - 1, ElemT>(vals);
    //}

    Vector<rows - 1, ElemT> AsTranslatedVector() const
    {
        static_assert(cols == 1, "Matrix::AsTranslatedVector cannot be called for matrices with more than one column and row");
        ElemT vals[rows - 1];
        for (auto q = 0; q < rows - 1; q++)
        {
            vals[q] = values[q][0];
        }
        return Vector<rows - 1, ElemT>(vals);
    }

    inline friend Matrix<rows, cols, ElemT> operator-(const Matrix<rows, cols, ElemT> &operand)
    {
        Matrix<rows, cols, ElemT> result;
        for (auto q = 0; q < rows; q++)
            for (auto w = 0; w < cols; w++)
                result.values[q][w] = -operand.values[q][w];
        return result;
    }

    inline friend Matrix<rows, cols, ElemT> operator*(const Matrix<rows, cols, ElemT> &left, ElemT right)
    {
        Matrix<rows, cols, ElemT> result;
        for (auto q = 0; q < rows; q++)
            for (auto w = 0; w < cols; w++)
                result.values[q][w] = left.values[q][w] * right;
        return result;
    }
    inline friend Matrix<rows, cols> operator*(ElemT left, const Matrix<rows, cols> &right)
    {
        Matrix<rows, cols> result;
        for (auto q = 0; q < rows; q++)
            for (auto w = 0; w < cols; w++)
                result.values[q][w] = left * left.values[q][w];
        return result;
    }
    inline friend Matrix<rows, cols, ElemT> operator/(const Matrix<rows, cols, ElemT> &left, ElemT right)
    {
        Matrix<rows, cols, ElemT> result;
        for (auto q = 0; q < rows; q++)
            for (auto w = 0; w < cols; w++)
                result.values[q][w] = left[q][w] / right;
        return result;
    }

    inline friend Matrix<rows, cols, ElemT> operator+(const Matrix<rows, cols, ElemT> &left, const Matrix<rows, cols, ElemT> &right)
    {
        Matrix<rows, cols, ElemT> result;
        for (auto q = 0; q < rows; q++)
            for (auto w = 0; w < cols; w++)
                result.values[q][w] = left[q][w] + right[q][w];
        return result;
    }
    inline friend Matrix<rows, cols, ElemT> operator-(const Matrix<rows, cols, ElemT> &left, const Matrix<rows, cols, ElemT> &right)
    {
        Matrix<rows, cols, ElemT> result;
        for (auto q = 0; q < rows; q++)
            for (auto w = 0; w < cols; w++)
                result.values[q][w] = left[q][w] - right[q][w];
        return result;
    }

    template <int innerDim>
    friend Matrix<rows, cols, ElemT> operator*(const Matrix<rows, innerDim, ElemT> &left, const Matrix<innerDim, cols, ElemT> &right)
    {
        return Multiply(left, right);
    }
    template <int innerDim>
    static Matrix<rows, cols, ElemT> Multiply(const Matrix<rows, innerDim, ElemT> &left, const Matrix<innerDim, cols, ElemT> &right)
    {
        Matrix<rows, cols, ElemT> result;
        for (auto q = 0; q < rows; q++)
            for (auto w = 0; w < cols; w++)
            {
                ElemT sum = 0.f;
                for (auto e = 0; e < innerDim; e++)
                    sum += left[q][e] * right[e][w];
                result.values[q][w] = sum;
            }
        return result;
    }
    template <int rightCols>
    inline Matrix<rows, rightCols, ElemT> operator*(const Matrix<cols, rightCols, ElemT> &right)
    {
        return Matrix<rows, rightCols, ElemT>::Multiply(*this, right);
    }

    inline Matrix<rows, cols, ElemT> &operator=(const Matrix<rows, cols, ElemT> &right)
    {
        for (auto q = 0; q < rows; q++)
            for (auto w = 0; w < cols; w++)
                values[q][w] = right[q][w];
        return *this;
    }
    inline friend Matrix<rows, cols, ElemT> &operator*=(const Matrix<rows, cols, ElemT> &left, ElemT right)
    {
        for (auto q = 0; q < rows; q++)
            for (auto w = 0; w < cols; w++)
                left[q][w] *= right;
        return left;
    }
    inline friend Matrix<rows, cols, ElemT> &operator/=(const Matrix<rows, cols, ElemT> &left, ElemT right)
    {
        for (auto q = 0; q < rows; q++)
            for (auto w = 0; w < cols; w++)
                left[q][w] /= right;
        return left;
    }
    inline friend Matrix<rows, cols, ElemT> &operator+=(const Matrix<rows, cols, ElemT> &left, const Matrix<rows, cols, ElemT> &right)
    {
        for (auto q = 0; q < rows; q++)
            for (auto w = 0; w < cols; w++)
                left[q][w] += right[q][w];
        return left;
    }
    inline friend Matrix<rows, cols, ElemT> &operator-=(const Matrix<rows, cols, ElemT> &left, const Matrix<rows, cols, ElemT> &right)
    {
        for (auto q = 0; q < rows; q++)
            for (auto w = 0; w < cols; w++)
                left[q][w] -= right[q][w];
        return left;
    }
    inline friend Matrix<rows, cols, ElemT> &operator*=(Matrix<rows, cols, ElemT> &left, const Matrix<rows, cols, ElemT> &right)
    {
        return left = left * right;
    }
    inline friend Vector<rows - 1, ElemT> &operator*=(Vector<rows - 1, ElemT> &left, const Matrix<rows, cols, ElemT> &right)
    {
        static_assert(rows == cols && rows >= 2, "You can't multiply-assign a matrix unless it is a square matrix and it is being multiplied by a matrix of the same size");
        return left = left * right;
    }

    inline friend std::ostream &operator<<(std::ostream &stream, const Matrix<rows, cols, ElemT> &mat)
    {
        stream << "[ ";
        for (auto q = 0; q < rows; q++)
        {
            if (q != 0) stream << "\n ";
            stream << " [";
            for (auto w = 0; w < cols; w++)
                stream << " " << mat[q][w];
            stream << " ]";
        }
        stream << " ]" << std::endl;
        return stream;
    }

    inline const ElemT *operator[](int idx) const
    {
        return values[idx];
    }

    inline const ElemT *getAddr() const
    {
        return values[0];
    }

    template <typename... Args>
    static Matrix<rows, cols, ElemT> FromRows(Args... rowVectors)
    {
        ElemT arr[cols * rows];
        PopulateFromRows(arr, 0, rowVectors...);
        return Matrix<rows, cols>(arr);
    }

    template <typename... Args>
    static Matrix<rows, cols, ElemT> FromCols(Args... colVectors)
    {
        ElemT arr[cols * rows];
        PopulateFromRows(arr, 0, colVectors...);
        return Matrix<rows, cols, ElemT>(arr);
    }

    Matrix<rows + 1, cols + 1> ToTransformMatrix()
    {
        return Matrix<rows + 1, cols + 1, ElemT>::CreateTransformMatrix(*this);
    }

    static Matrix<rows, cols, ElemT> CreateTransformMatrix(Matrix<rows - 1, cols - 1, ElemT>& from)
    {
        static_assert(rows == cols, "ToTransformationMatrix cannot be called on non-square matrix");
        auto result = Matrix<rows, cols, ElemT>::Identity();

        for (int i = 0; i < rows - 1; i++)
            for (int j = 0; j < cols - 1; j++)
                result.values[i][j] = from[i][j];

        return result;
    }

    static Matrix<rows, cols, ElemT> Frustum(ElemT left, ElemT right, ElemT bottom, ElemT top, ElemT nearVal, ElemT farVal)
    {
        static_assert(rows == 4 && cols == 4, "Frustum can only be called on a 4 by 4 matrix");
        ElemT X = (2 * nearVal) / (right - left),
              Y = (2 * nearVal) / (top - bottom),
              A = (right + left) / (right - left),
              B = (top + bottom) / (top - bottom),
              C = -(farVal + nearVal) / (farVal - nearVal),
              D = -(2 * farVal * nearVal) / (farVal - nearVal);
        return Matrix<rows, cols, ElemT> { X, 0, A, 0,
                                           0, Y, B, 0,
                                           0, 0, C, D,
                                           0, 0,-1, 0 };
    }
    static Matrix<rows, cols, ElemT> Ortho(ElemT left, ElemT right, ElemT bottom, ElemT top, ElemT nearVal, ElemT farVal)
    {
        static_assert(rows == 4 && cols == 4, "Ortho can only be called on a 4 by 4 matrix");
        ElemT X = 2 / (right - left),
              Y = 2 / (top - bottom),
              Z = -2 / (farVal - nearVal),
              Tx = -(right + left) / (right - left),
              Ty = -(top + bottom) / (top - bottom),
              Tz = -(farVal + nearVal) / (farVal - nearVal);
        return Matrix<rows, cols, ElemT> { X, 0, 0, Tx,
                                           0, Y, 0, Ty,
                                           0, 0, Z, Tz,
                                           0, 0, 0, 1 };
    }

private:
    ElemT values[rows][cols]; //TODO: Find some way to make this private!

    //Constructor helpers:
    template <int ridx = 0, int cidx = 0, typename T, typename... Args>
    inline void initialize(T val, Args... args)
    {
        values[ridx][cidx] = (ElemT)val;
        constexpr int next_cidx = (cidx + 1 >= cols) ? 0 : cidx + 1;
        constexpr int next_ridx = (next_cidx == 0) ? ridx + 1 : ridx;
        initialize<next_ridx, next_cidx>(args...);
    }
    template <int ridx = 0, int cidx = 0, typename T>
    inline void initialize(T val)
    {
        values[ridx][cidx] = (ElemT)val;
    }
    //inline void initialize(Vector<cols - 1, ElemT> vec)
    //{
    //    static_assert(rows == 1 && cols >= 2, "A matrix was initialized with an invalid vector parameter.");
    //    for (auto q = 0; q < cols - 1; q++)
    //    {
    //        values[0][q] = vec[q];
    //    }
    //    values[0][cols - 1] = 1;
    //}
    inline void initialize(Vector<rows - 1, ElemT> vec)
    {
        static_assert(cols == 1 && rows >= 2, "A matrix cannot be initialized with vectors unless it has one row or column");
        for (auto q = 0; q < rows - 1; q++)
        {
            values[q][0] = vec[q];
        }
        values[rows - 1][0] = 1;
    }
    //inline void initialize(Vector<rows, ElemT> vec)
    //{
    //    static_assert(rows == 1, "A matrix was initialized with an invalid vector parameter.");
    //    for (auto q = 0; q < rows - 1; q++)
    //    {
    //        values[0][q] = vec[q];
    //    }
    //}
    inline void initialize(Vector<rows, ElemT> vec)
    {
        static_assert(cols == 1 && rows >= 2, "A matrix cannot be initialized unless it has one row or column");
        for (auto q = 0; q < rows; q++)
        {
            values[q][0] = vec[q];
        }
    }
    inline void initialize()
    {
    }

    template <typename... Args, int rowSize>
    static void PopulateFromRows(ElemT * out, int rowIndex, Vector<rowSize, ElemT> row, Args... rowVectors)
    {
        static_assert(rowSize <= cols, "Vector rowSize cannot be greater than Matrix cols");
        for (int c = 0; c < rowSize; c++)
            out[rowIndex * cols + c] = row[c];
        PopulateFromRows(out, rowIndex + 1, rowVectors...);
    }
    template <int rowSize>
    static void PopulateFromRows(ElemT * out, int rowIndex, Vector<rowSize, ElemT> row)
    {
        static_assert(rowSize <= cols, "Vector rowSize cannot be greater than Matrix cols");
        for (int c = 0; c < rowSize; c++)
            out[rowIndex * cols + c] = row[c];
    }

    template <typename... Args, int colSize>
    static void PopulateFromCols(ElemT * out, int colIndex, Vector<colSize, ElemT> col, Args... colVectors)
    {
        static_assert(colSize <= rows, "Vector colSize cannot be greater than Matrix rows");
        for (int c = 0; c < colSize; c++)
            out[c * cols + colIndex] = row[c];
        PopulateFromRows(out, rowIndex + 1, rowVectors...);
    }
    template <int colSize>
    static void PopulateFromCols(ElemT * out, int colIndex, Vector<colSize, ElemT> col)
    {
        static_assert(colSize <= rows, "Vector colSize cannot be greater than Matrix rows");
        for (int c = 0; c < colSize; c++)
            out[c * cols + colIndex] = row[c];
    }
};

template <int rows, int cols, typename ElemT = float>
using Mat = Matrix<rows, cols, ElemT>;

template <typename ElemT = float>
using Mat2 = Matrix<2, 2, ElemT>;

template <typename ElemT = float>
using Mat3 = Matrix<3, 3, ElemT>;
template <typename ElemT = float>
using Mat2T = Matrix<3, 3, ElemT>;

template <typename ElemT = float>
using Mat4 = Matrix<4, 4, ElemT>;
template <typename ElemT = float>
using Mat3T = Matrix<4, 4, ElemT>;

template <int rows, typename ElemT = float>
using MatV = Matrix<rows, 1, ElemT>;
template <typename ElemT = float>
using Mat2V = Matrix<2, 1, ElemT>;
template <typename ElemT = float>
using Mat3V = Matrix<3, 1, ElemT>;
template <typename ElemT = float>
using Mat4V = Matrix<4, 1, ElemT>;

template <int dim, typename ElemT = float>
Matrix<dim, 1, ElemT> MakeMatrix(Vector<dim, ElemT> vec)
{
    return Matrix<dim, 1, ElemT>::FromVector(vec);
}

template <int rows, int cols, typename ElemT = float>
Vector<cols, ElemT> operator*(const Matrix<rows, cols, ElemT> &mat, const Vector<rows, ElemT> &vec)
{
    auto rhs = Matrix<cols, 1, ElemT>(vec);
    return (mat * rhs).AsVector();
}

template <int rows, int cols, typename ElemT = float>
Vector<cols - 1, ElemT> operator*(const Matrix<rows, cols, ElemT> &mat, const Vector<rows - 1, ElemT> &vec)
{
    Matrix<rows, 1, ElemT> rhs(vec);
    auto result = mat * rhs;
    return result.AsTranslatedVector();
}
