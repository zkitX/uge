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
        X.Set(other.X);
        Y.Set(other.Y);
        Z.Set(other.Z);
        W.Set(other.W);

        return *this;
    }

    UGE_FORCE_INLINE Matrix& Matrix::SetRows(const Float* f)
    {
        X.Set(f[0], f[1], f[2], f[3]);
        Y.Set(f[4], f[5], f[6], f[7]);
        Z.Set(f[8], f[9], f[10], f[11]);
        W.Set(f[12], f[13], f[14], f[15]);
    }

    UGE_INLINE Matrix& Matrix::SetColumns(const Float* f)
    {
        X.Set(f[0], f[4], f[8], f[12]);
        Y.Set(f[1], f[5], f[9], f[13]);
        Z.Set(f[2], f[6], f[10], f[14]);
        W.Set(f[3], f[7], f[11], f[15]);

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
        X.Set(x.x, y.x, z.x, w.x);
        Y.Set(x.y, y.y, z.y, w.y);
        Z.Set(x.z, y.z, z.z, w.z);
        W.Set(x.w, y.w, z.w, w.w);

        return *this;
    }

    UGE_FORCE_INLINE Matrix& Matrix::SetZero()
    {
        X.SetZero();
        Y.SetZero();
        Z.SetZero();
        W.SetZero();
        return *this;
    }

    UGE_FORCE_INLINE Matrix& Matrix::SetIdentity()
    {
        X = Vec4(1.f, 0.f, 0.f, 0.f);
        Y = Vec4(0.f, 1.f, 0.f, 0.f);
        Z = Vec4(0.f, 0.f, 1.f, 0.f);
        W = Vec4(0.f, 0.f, 0.f, 1.f);
        return *this;
    }

    UGE_INLINE Matrix& Matrix::Set33(const Matrix &other)
    {
        X.Set3(other.X);
        Y.Set3(other.Y);
        Z.Set3(other.Z);

        return *this;
    }

    UGE_INLINE Matrix& Matrix::Set33(const Vec4& x, const Vec4& y, const Vec4& z)
    {
        X.Set3(x);
        Y.Set3(y);
        Z.Set3(z);

        return *this;
    }

    // CCW Rotation around the X axis
    // [ 1 0 0 ]
    // [ 0 c s ]
    // [ 0 -s c ]
    UGE_INLINE Matrix& Matrix::SetRotX33(const Float angle)
    {
        const Float c = Cos(angle);
        const Float s = Sin(angle);

        X.Set3(1.f, 0.f, 0.f);
        Y.Set3(0.f, c, s);
        Z.Set3(0.f, -s, c);

        return *this;
    }

    // CCW Rotation around the Y axis
    // [ c 0 -s ]
    // [ 0 1 0 ]
    // [ s 0 c ]
    UGE_INLINE Matrix& Matrix::SetRotY33(const Float angle)
    {
        const Float c = Cos(angle);
        const Float s = Sin(angle);

        X.Set3(c, 0.f, -s);
        Y.Set3(0.f, 1.f, 0.f);
        Z.Set3(s, 0.f, c);

        return *this;
    }

    // CCW Rotation around the Z axis
    // [ c s 0 ]
    // [ -s c 0 ]
    // [ 0 0 1 ]
    UGE_INLINE Matrix& Matrix::SetRotZ33(const Float angle)
    {
        const Float c = Cos(angle);
        const Float s = Sin(angle);

        X.Set3(c, s, 0.f);
        Y.Set3(-s, c, 0.f);
        Z.Set3(0.f, 0.f, 1.f);

        return *this;
    }

    UGE_INLINE Matrix& Matrix::SetScale(const Vec4& scale)
    {
        X.x = scale.x;
        Y.y = scale.y;
        Z.z = scale.z;

        return *this;
    }

    UGE_INLINE Matrix& Matrix::SetScale33(const Vec4& scale)
    {
        X.ToVec3() *= scale.x;
        Y.ToVec3() *= scale.y;
        Z.ToVec3() *= scale.z;

        return *this;
    }
    
    UGE_INLINE Matrix& Matrix::SetScale44(const Vec4& scale)
    {
        X *= scale.x;
        Y *= scale.y;
        Z *= scale.z;

        return *this;
    }

    UGE_INLINE Vec4 Matrix::GetScale33() const
    {
        return Vec4(X.Magnitude(DotProduct3D), Y.Magnitude(DotProduct3D), Z.Magnitude(DotProduct3D), 1.f);
    }

    UGE_INLINE Matrix& Matrix::SetPreScale33(const Vec4& scale)
    {
        X.ToVec3() *= scale.x;
        Y.ToVec3() *= scale.y;
        Z.ToVec3() *= scale.z;

        return *this;
    }

    UGE_INLINE Matrix& Matrix::SetPreScale44(const Vec4& scale)
    {
        // Only scale the first 3 columns
        X.ToVec3() *= scale.x;
        Y.ToVec3() *= scale.y;
        Z.ToVec3() *= scale.z;
        W.ToVec3() *= scale.w;

        return *this;
    }

    UGE_INLINE Vec4 Matrix::GetPreScale33() const
    {
        Vec4 v0{ X[0], Y[0], Z[0] };
        Vec4 v1{ X[1], Y[1], Z[1] };
        Vec4 v2{ X[2], Y[2], Z[2] };
        return { v0.Magnitude(DotProduct3D), v1.Magnitude(DotProduct3D), v2.Magnitude(DotProduct3D) };
    }

    UGE_INLINE Matrix& Matrix::SetScale33(const Float uniformScale)
    {
        X.ToVec3() *= uniformScale;
        Y.ToVec3() *= uniformScale;
        Z.ToVec3() *= uniformScale;

        return *this;
    }

    UGE_INLINE Matrix& Matrix::SetTranslation(const Vec4& translation)
    {
        W.Set(translation.x, translation.y, translation.z, 1.f);
        return *this;
    }

    UGE_INLINE Matrix& Matrix::SetTranslation(const Float x, const Float y, const Float z)
    {
        W.Set(x, y, z, 1.f);
        return *this;
    }

    UGE_INLINE Vec4 Matrix::GetTranslation() const
    {
        return { W.x, W.y, W.z, 1.f };
    }

    UGE_FORCE_INLINE const Vec4& Matrix::GetTranslationRef() const
    {
        return W;
    }

    UGE_FORCE_INLINE Vec4& Matrix::GetTranslationRef()
    {
        return W;
    }

    UGE_FORCE_INLINE Matrix& Matrix::InverseNoScale()
    {
        *this = InversedNoScale();
        return *this;
    }

    UGE_FORCE_INLINE Matrix& Matrix::InverseFull()
    {
        *this = InversedFull();
        return *this;
    }

    UGE_FORCE_INLINE Matrix& Matrix::Transpose()
    {
        *this = Transposed();
        return *this;
    }

    UGE_INLINE Vec4 Matrix::GetColumn(const size_t index) const
    {
        UGE_ASSERT(index < 4, "Index out of bounds");
        return { X[index], Y[index], Z[index], W[index] };
    }

    UGE_INLINE Matrix& Matrix::SetColumn(const size_t index, const Vec4& column)
    {
        UGE_ASSERT(index < 4, "Index out of bounds");
        X[index] = column.x;
        Y[index] = column.y;
        Z[index] = column.z;
        W[index] = column.w;

        return *this;
    }

    UGE_FORCE_INLINE Vec4 Matrix::GetRow(const size_t index) const
    {
        UGE_ASSERT(index < 4, "Index out of bounds");
        return operator[](index);
    }

    UGE_INLINE Vec4 Matrix::GetAxisX() const
    {
        return { X.x, X.y, X.z, 0.f };
    }
    
    UGE_INLINE Vec4 Matrix::GetAxisY() const
    {
        return { Y.x, Y.y, Y.z, 0.f };
    }

    UGE_INLINE Vec4 Matrix::GetAxisZ() const
    {
        return { Z.x, Z.y, Z.z, 0.f };
    }

    UGE_INLINE void Matrix::GetColumnMajor(Float* out) const
    {
        out[0] = X[0];
        out[1] = Y[0];
        out[2] = Z[0];
        out[3] = W[0];
        out[4] = X[1];
        out[5] = Y[1];
        out[6] = Z[1];
        out[7] = W[1];
        out[8] = X[2];
        out[9] = Y[2];
        out[10] = Z[2];
        out[11] = W[2];
        out[12] = X[3];
        out[13] = Y[3];
        out[14] = Z[3];
        out[15] = W[3];
    }

    UGE_INLINE void Matrix::GetColumnMajor3x4(Float* out) const
    {
        out[0] = X[0];
        out[1] = Y[0];
        out[2] = Z[0];
        out[3] = W[0];
        out[4] = X[1];
        out[5] = Y[1];
        out[6] = Z[1];
        out[7] = W[1];
        out[8] = X[2];
        out[9] = Y[2];
        out[10] = Z[2];
        out[11] = W[2];
    }

    UGE_INLINE void Matrix::SetColumnMajor3x4(const Float * data)
    {
        X[0] = data[0];  X[1] = data[4];  X[2] = data[8];
        Y[0] = data[1];  Y[1] = data[5];  Y[2] = data[9];
        Z[0] = data[2];  Z[1] = data[6];  Z[2] = data[10];
    }

    UGE_INLINE void Matrix::SetRowMajor4x3(const Float* data)
    {
        X[0] = data[0];  X[1] = data[1];  X[2] = data[2];  X[3] = data[3];
        Y[0] = data[4];  Y[1] = data[5];  Y[2] = data[6];  Y[3] = data[7];
        Z[0] = data[8];  Z[1] = data[9];  Z[2] = data[10]; Z[3] = data[11];
        W[0] = 0.f;      W[1] = 0.f;      W[2] = 0.f;      W[3] = 1.f;
    }

    UGE_FORCE_INLINE Vec4 Matrix::Transform(const Vec4& v) const
    {
        Vec4 result = X * v.x + Y * v.x + Z * v.x;
        result.w = 0.f;
        return result;
    } 

    UGE_FORCE_INLINE Vec4 Matrix::Transform4x4(const Vec4& v) const
    {
        return X * v.x + Y * v.x + Z * v.x + W * v.x;
    }

    UGE_FORCE_INLINE Vec4 Matrix::TransformPoint(const Vec4& v) const
    {
        Vec4 result = X * v.x + Y * v.y + Z * v.z + W;
        result.w = 1.0f;
        return result;
    }

    UGE_FORCE_INLINE Vec3 Matrix::TransformPoint(const Vec3& v) const
    {
        return TransformPoint(Vec4(v));
    }

    UGE_FORCE_INLINE Matrix Matrix::operator*(const Matrix& other) const
    {
        return Mul(*this, other);
    }
}

#endif  // __COREMATH_MATH_MATRIX_INL__