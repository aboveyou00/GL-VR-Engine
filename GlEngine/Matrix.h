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
	Matrix(float * vals)
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
    static Matrix<rows, cols, ElemT> RotateMatrix(ElemT theta)
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

    template <typename = std::enable_if_t<cols == 1 || rows == cols>>
    Vector<rows, ElemT> AsVector() const
    {
        static_assert(cols == 1 || rows == cols, "Matrix::FromVector cannot be applied for matrices unless they are square or they only have one column");
        ElemT vals[rows];
        for (auto q = 0; q < rows; q++)
        {
            vals[q] = values[q][(rows == cols) ? q : 0];
        }
        return Vector<rows, ElemT>(vals);
    }
    //template <typename = std::enable_if_t<rows == 1 && (cols >= 2)>>
    //Vector<cols - 1> AsTranslatedVector() const
    //{
    //    float vals[cols - 1];
    //    for (auto q = 0; q < cols - 1; q++)
    //    {
    //        vals[q] = values[0][q];
    //    }
    //    return Vector<cols - 1>(vals);
    //}
    Vector<rows - 1, ElemT> AsTranslatedVector() const
    {
        static_assert(cols == 1, "Matrix::AsTranslatedVector cannot be called for matrices with more than one column");
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
    inline friend Matrix<rows, cols> operator*(float left, const Matrix<rows, cols> &right)
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
                float sum = 0.f;
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
    inline friend Vector<rows - 1, ElemT> &operator*=(Vector<rows - 1, ElemT> &vec, const Matrix<rows, cols, ElemT> &right)
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
    //template <typename = std::enable_if_t<rows == 1 && (cols >= 2)>>
    //inline void initialize(Vector<cols - 1> vec)
    //{
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
    //template <typename = std::enable_if_t<rows == 1>>
    //inline void initialize(Vector<rows> vec)
    //{
    //    for (auto q = 0; q < rows - 1; q++)
    //    {
    //        values[0][q] = vec[q];
    //    }
    //}
    inline void initialize(Vector<rows, ElemT> vec)
    {
        static_assert(cols == 1 && rows >= 2, "A matrix cannot be initialized unless it has one row or column");
        for (auto q = 0; q < rows - 1; q++)
        {
            values[q][0] = vec[q];
        }
    }
    inline void initialize()
    {
    }

	template <typename... Args, int rowSize>
	static void PopulateFromRows(float * out, int rowIndex, Vector<rowSize, ElemT> row, Args... rowVectors)
	{
		static_assert(rowSize <= cols, "Vector rowSize cannot be greater than Matrix cols");
		for (int c = 0; c < rowSize; c++)
			out[rowIndex * cols + c] = row[c];
		PopulateFromRows(out, rowIndex + 1, rowVectors...);
	}
	template <int rowSize>
	static void PopulateFromRows(float * out, int rowIndex, Vector<rowSize, ElemT> row)
	{
		static_assert(rowSize <= cols, "Vector rowSize cannot be greater than Matrix cols");
		for (int c = 0; c < rowSize; c++)
			out[rowIndex * cols + c] = row[c];
	}

	template <typename... Args, int colSize>
	static void PopulateFromCols(float * out, int colIndex, Vector<colSize, ElemT> col, Args... colVectors)
	{
        static_assert(colSize <= rows, "Vector colSize cannot be greater than Matrix rows");
		for (int c = 0; c < colSize; c++)
			out[c * cols + colIndex] = row[c];
		PopulateFromRows(out, rowIndex + 1, rowVectors...);
	}
	template <int colSize>
	static void PopulateFromCols(float * out, int colIndex, Vector<colSize, ElemT> col)
	{
        static_assert(colSize <= rows, "Vector colSize cannot be greater than Matrix rows");
		for (int c = 0; c < colSize; c++)
			out[c * cols + colIndex] = row[c];
	}
};

template <int rows, int cols>
using Mat = Matrix<rows, cols>;

using Mat2 = Matrix<2, 2>;

using Mat3 = Matrix<3, 3>;
using Mat2T = Matrix<3, 3>;

using Mat4 = Matrix<4, 4>;
using Mat3T = Matrix<4, 4>;

template <int rows>
using MatV = Matrix<rows, 1>;
using Mat2V = Matrix<2, 1>;
using Mat3V = Matrix<3, 1>;
using Mat4V = Matrix<4, 1>;

template <int dim, typename ElemT = float>
Matrix<dim, 1, ElemT> MakeMatrix(Vector<dim, ElemT> vec)
{
    return Matrix<dim, 1, ElemT>::FromVector(vec);
}

template <int rows, int cols, typename ElemT = float>
Vector<rows - 1, ElemT> operator*(const Matrix<rows, cols, ElemT> &mat, const Vector<rows - 1, ElemT> &vec)
{
    auto rhs = Matrix<rows, 1, ElemT>(vec);
    auto result = mat * rhs;
    return result.AsTranslatedVector();
}
