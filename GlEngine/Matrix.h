#pragma once

#include "Vector.h"
#include <iomanip>

template <int rows, int cols>
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

    static Matrix<rows, cols> Identity()
    {
		static_assert(rows == cols, "Identity cannot be called for a non-square matrix");
        Matrix<rows, rows> result;
        for (auto q = 0; q < rows; q++)
            result.values[q][q] = 1;
        return result;
    }

    template <typename = std::enable_if_t<rows == cols && (rows >= 2)>>
    static Matrix<rows, cols> TranslateMatrix(Vector<rows - 1> translateVec)
    {
        auto result = Matrix<rows, cols>::Identity();
        for (auto q = 0; q < rows - 1; q++)
        {
            result.values[rows - 1][q] = translateVec[q];
        }
        return result;
    }
    template <typename = std::enable_if<rows == 3 && cols == 3>::type>
    static Matrix<3, 3> TranslateMatrix(float x, float y)
    {
        return Matrix<3, 3> { 1, 0, 0,
                              0, 1, 0,
                              x, y, 1 };
    }
    template <typename = std::enable_if<rows == 4 && cols == 4>::type>
    static Matrix<4, 4> TranslateMatrix(float x, float y, float z)
    {
        return Matrix<4, 4> { 1, 0, 0, 0,
                              0, 1, 0, 0,
                              0, 0, 1, 0,
                              x, y, z, 1 };
    }
    template <typename = std::enable_if<rows == 3 && cols == 3>::type>
    static Matrix<rows, cols> RotateMatrix(float theta)
    {
        return Matrix<3, 3> { cos(theta), -sin(theta), 0,
                              sin(theta),  cos(theta), 0,
                              0, 0, 1 };
    }
    template <typename = std::enable_if_t<rows == cols && (rows >= 2)>>
    static Matrix<rows, cols> ScaleMatrix(Vector<rows - 1> scaleVec)
    {
        auto result = Matrix<rows, cols>::Identity();
        for (auto q = 0; q < rows - 1; q++)
        {
            result.values[q][q] = scaleVec[q];
        }
        return result;
    }
    template <typename = std::enable_if_t<rows == 3 && cols == 3>>
    static Matrix<3, 3> ScaleMatrix(float sx, float sy)
    {
        return Matrix<3, 3> { sx, 0, 0,
                              0, sy, 0,
                              0, 0, 1 };
    }
    template <typename = std::enable_if_t<rows == 4 && cols == 4>>
    static Matrix<4, 4> ScaleMatrix(float sx, float sy, float sz)
    {
        return Matrix<4, 4> { sx, 0, 0, 0,
                              0, sy, 0, 0,
                              0, 0, sz, 0,
                              0, 0, 0, 1 };
    }
    template <typename = std::enable_if_t<rows == cols && (rows >= 2)>>
    static Matrix<rows, cols> ScaleMatrix(float scale)
    {
        auto result = Matrix<rows, cols>::Identity();
        for (auto q = 0; q < rows - 1; q++)
        {
            result.values[q][q] = scale;
        }
        result.values[rows - 1][rows - 1] = 1;
        return result;
    }

    template <typename = std::enable_if_t<cols == 1>>
    inline static Matrix<rows, cols> FromVector(Vector<rows> vec)
    {
        Matrix<rows, cols> result;
        for (auto q = 0; q < rows; q++)
        {
            result.values[q][0] = vec[q];
        }
        return result;
    }

    Matrix<cols, rows> Transpose() const
    {
        Matrix<cols, rows> result;
        for (auto q = 0; q < rows; q++)
            for (auto w = 0; w < cols; w++)
                result.values[w][q] = values[q][w];
        return result;
    }

    template <typename = std::enable_if_t<cols == 1 || rows == cols>>
    Vector<rows> AsVector() const
    {
        float vals[rows];
        for (auto q = 0; q < rows; q++)
        {
            vals[q] = values[q][(rows == cols) ? q : 0];
        }
        return Vector<rows>(vals);
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
    template <typename = std::enable_if_t<cols == 1>>
    Vector<rows - 1> AsTranslatedVector() const
    {
        float vals[rows - 1];
        for (auto q = 0; q < rows - 1; q++)
        {
            vals[q] = values[q][0];
        }
        return Vector<rows - 1>(vals);
    }

    inline friend Matrix<rows, cols> operator-(const Matrix<rows, cols> &operand)
    {
        Matrix<rows, cols> result;
        for (auto q = 0; q < rows; q++)
            for (auto w = 0; w < cols; w++)
                result.values[q][w] = -operand.values[q][w];
        return result;
    }

    inline friend Matrix<rows, cols> operator*(const Matrix<rows, cols> &left, float right)
    {
        Matrix<rows, cols> result;
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
    inline friend Matrix<rows, cols> operator/(const Matrix<rows, cols> &left, float right)
    {
        Matrix<rows, cols> result;
        for (auto q = 0; q < rows; q++)
            for (auto w = 0; w < cols; w++)
                result.values[q][w] = left[q][w] / right;
        return result;
    }

    inline friend Matrix<rows, cols> operator+(const Matrix<rows, cols> &left, const Matrix<rows, cols> &right)
    {
        Matrix<rows, cols> result;
        for (auto q = 0; q < rows; q++)
            for (auto w = 0; w < cols; w++)
                result.values[q][w] = left[q][w] + right[q][w];
        return result;
    }
    inline friend Matrix<rows, cols> operator-(const Matrix<rows, cols> &left, const Matrix<rows, cols> &right)
    {
        Matrix<rows, cols> result;
        for (auto q = 0; q < rows; q++)
            for (auto w = 0; w < cols; w++)
                result.values[q][w] = left[q][w] - right[q][w];
        return result;
    }

    template <int innerDim>
    friend Matrix<rows, cols> operator*(const Matrix<rows, innerDim> &left, const Matrix<innerDim, cols> &right)
    {
        return Multiply(left, right);
    }
    template <int innerDim>
    static Matrix<rows, cols> Multiply(const Matrix<rows, innerDim> &left, const Matrix<innerDim, cols> &right)
    {
        Matrix<rows, cols> result;
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
    inline Matrix<rows, rightCols> operator*(const Matrix<cols, rightCols> &right)
    {
        return Matrix<rows, rightCols>::Multiply(*this, right);
    }

    inline Matrix<rows, cols> &operator=(const Matrix<rows, cols> &right)
    {
        for (auto q = 0; q < rows; q++)
            for (auto w = 0; w < cols; w++)
                values[q][w] = right[q][w];
        return *this;
    }
    inline friend Matrix<rows, cols> &operator*=(const Matrix<rows, cols> &left, float right)
    {
        for (auto q = 0; q < rows; q++)
            for (auto w = 0; w < cols; w++)
                left[q][w] *= right;
        return left;
    }
    inline friend Matrix<rows, cols> &operator/=(const Matrix<rows, cols> &left, float right)
    {
        for (auto q = 0; q < rows; q++)
            for (auto w = 0; w < cols; w++)
                left[q][w] /= right;
        return left;
    }
    inline friend Matrix<rows, cols> &operator+=(const Matrix<rows, cols> &left, const Matrix<rows, cols> &right)
    {
        for (auto q = 0; q < rows; q++)
            for (auto w = 0; w < cols; w++)
                left[q][w] += right[q][w];
        return left;
    }
    inline friend Matrix<rows, cols> &operator-=(const Matrix<rows, cols> &left, const Matrix<rows, cols> &right)
    {
        for (auto q = 0; q < rows; q++)
            for (auto w = 0; w < cols; w++)
                left[q][w] -= right[q][w];
        return left;
    }
    inline friend Matrix<rows, cols> &operator*=(Matrix<rows, cols> &left, const Matrix<rows, cols> &right)
    {
        return left = left * right;
    }
    template <typename = std::enable_if_t<rows == cols && (rows >= 2)>>
    inline friend Vector<rows - 1> &operator*=(Vector<rows - 1> &vec, const Matrix<rows, cols> &right)
    {
        return left = left * right;
    }

    inline friend std::ostream &operator<<(std::ostream &stream, const Matrix<rows, cols> &mat)
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

    inline const float *operator[](int idx) const
    {
        return values[idx];
    }

    inline const float *getAddr() const
    {
        return values[0];
    }

	template <typename... Args>
	static Matrix<rows, cols> FromRows(Args... rowVectors)
	{
		float arr[cols * rows];
		PopulateFromRows(arr, 0, rowVectors...);
		return Matrix<rows, cols>(arr);
	}

	template <typename... Args>
	static Matrix<rows, cols> FromCols(Args... colVectors)
	{
		float arr[cols * rows];
		PopulateFromRows(arr, 0, colVectors...);
		return Matrix<rows, cols>(arr);
	}

	Matrix<rows + 1, cols + 1> ToTransformMatrix()
	{
		return Matrix<rows + 1, cols + 1>::CreateTransformMatrix(*this);
	}

	static Matrix<rows, cols> CreateTransformMatrix(Matrix<rows - 1, cols - 1>& from)
	{
		static_assert(rows == cols, "ToTransformationMatrix cannot be called on non-square matrix");
		auto result = Matrix<rows, cols>::Identity();

		for (int i = 0; i < rows - 1; i++)
			for (int j = 0; j < cols - 1; j++)
				result.values[i][j] = from[i][j];

		return result;
	}

private:
    float values[rows][cols]; //TODO: Find some way to make this private!

    //Constructor helpers:
    template <int ridx = 0, int cidx = 0, typename T, typename... Args>
    inline void initialize(T val, Args... args)
    {
        values[ridx][cidx] = (float)val;
        constexpr int next_cidx = (cidx + 1 >= cols) ? 0 : cidx + 1;
        constexpr int next_ridx = (next_cidx == 0) ? ridx + 1 : ridx;
        initialize<next_ridx, next_cidx>(args...);
    }
    template <int ridx = 0, int cidx = 0, typename T>
    inline void initialize(T val)
    {
        values[ridx][cidx] = (float)val;
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
    template <typename = std::enable_if_t<cols == 1 && (rows >= 2)>>
    inline void initialize(Vector<rows - 1> vec)
    {
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
    template <typename = std::enable_if_t<cols == 1 && (rows >= 2)>>
    inline void initialize(Vector<rows> vec)
    {
        for (auto q = 0; q < rows - 1; q++)
        {
            values[q][0] = vec[q];
        }
    }
    inline void initialize()
    {
    }

	template <typename... Args, int rowSize>
	static void PopulateFromRows(float * out, int rowIndex, Vector<rowSize> row, Args... rowVectors)
	{
		static_assert(rowSize <= cols, "Vector rowSize cannot be greater than Matrix cols");

		for (int c = 0; c < rowSize; c++)
			out[rowIndex * cols + c] = row[c];
		PopulateFromRows(out, rowIndex + 1, rowVectors...);
	}
	template <int rowSize>
	static void PopulateFromRows(float * out, int rowIndex, Vector<rowSize> row)
	{
		static_assert(rowSize <= cols, "Vector rowSize cannot be greater than Matrix cols");

		for (int c = 0; c < rowSize; c++)
			out[rowIndex * cols + c] = row[c];
	}

	template <typename... Args, int colSize>
	static void PopulateFromCols(float * out, int colIndex, Vector<colSize> col, Args... colVectors)
	{
		static_assert(colSize <= rows, "Vector colSize cannot be greater than Matrix rows")

		for (int c = 0; c < colSize; c++)
			out[c * cols + colIndex] = row[c];
		PopulateFromRows(out, rowIndex + 1, rowVectors...);
	}
	template <int colSize>
	static void PopulateFromCols(float * out, int colIndex, Vector<colSize> col)
	{
		static_assert(colSize <= rows, "Vector colSize cannot be greater than Matrix rows")

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

template <int dim>
Matrix<dim, 1> MakeMatrix(Vector<dim> vec)
{
    return Matrix<dim, 1>::FromVector(vec);
}

template <int rows, int cols>
Vector<rows - 1> operator*(const Matrix<rows, cols> &mat, const Vector<rows - 1> &vec)
{
    auto rhs = Matrix<rows, 1>(vec);
    auto result = mat * rhs;
    return result.AsTranslatedVector();
}
