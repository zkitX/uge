#ifndef __COREMATH_MATH_MATRIX_INL__
#define __COREMATH_MATH_MATRIX_INL__

namespace uge::math
{
    UGE_FORCE_INLINE Matrix::Matrix(const Float m[16])
    : Matrix { m[0], m[1], m[2], m[3],
               m[4], m[5], m[6], m[7],
               m[8], m[9], m[10], m[11],
               m[12], m[13], m[14], m[15] }
    {
    }

    UGE_FORCE_INLINE Matrix::Matrix(const Vec4& x, const Vec4& y, const Vec4& z, const Vec4& w)
    : X(x), Y(y), Z(z), W(w)
    {
    }

    UGE_INLINE Matrix::Matrix(const Float m00, const Float m01, const Float m02, const Float m03,
                              const Float m10, const Float m11, const Float m12, const Float m13,
                              const Float m20, const Float m21, const Float m22, const Float m23,
                              const Float m30, const Float m31, const Float m32, const Float m33)
    : Matrix { {m00, m01, m02, m03},
               {m10, m11, m12, m13},
               {m20, m21, m22, m23},
               {m30, m31, m32, m33} }
    {
    }

    UGE_FORCE_INLINE Matrix::Matrix(const Matrix &other)
    {
        X = other.X;
        Y = other.Y;
        Z = other.Z;
        W = other.W;
    }

    UGE_FORCE_INLINE Matrix &Matrix::operator=(const Matrix &other)
    {
        X = other.X;
        Y = other.Y;
        Z = other.Z;
        W = other.W;

        return *this;
    }

    UGE_FORCE_INLINE Bool Matrix::operator==(const Matrix &other) const
    {
        return X == other.X && Y == other.Y && Z == other.Z && W == other.W;
    }

    UGE_FORCE_INLINE Bool Matrix::operator!=(const Matrix &other) const
    {
        return !(*this == other);
    }

    UGE_FORCE_INLINE Matrix& Matrix::Set(const Matrix &other)
    {
        X = other.X;
        Y = other.Y;
        Z = other.Z;
        W = other.W;

        return *this;
    }

    UGE_FORCE_INLINE Matrix& Matrix::SetRows(const Float* f)
    {
        X = Vec4(f + 0);
        Y = Vec4(f + 4);
        Z = Vec4(f + 8);
        W = Vec4(f + 12);
    }

    UGE_INLINE Matrix& Matrix::SetColumns(const Float* f)
    {
        X = Vec4(f[0], f[4], f[8], f[12]);
        Y = Vec4(f[1], f[5], f[9], f[13]);
        Z = Vec4(f[2], f[6], f[10], f[14]);
        W = Vec4(f[3], f[7], f[11], f[15]);

        return *this;
    }

    UGE_INLINE Matrix& Matrix::SetRows(const Vec4& x, const Vec4& y, const Vec4& z, const Vec4& w)
    {
        X = x;
        Y = y;
        Z = z;
        W = w;

        return *this;
    }

    UGE_INLINE Matrix& Matrix::SetColumns(const Vec4& x, const Vec4& y, const Vec4& z, const Vec4& w)
    {
        X = Vec4(x.x, y.x, z.x, w.x);
        Y = Vec4(x.y, y.y, z.y, w.y);
        Z = Vec4(x.z, y.z, z.z, w.z);
        W = Vec4(x.w, y.w, z.w, w.w);

        return *this;
    }

    UGE_FORCE_INLINE Matrix& Matrix::SetZero()
    {
        return *this;
    }
}

#endif  // __COREMATH_MATH_MATRIX_INL__