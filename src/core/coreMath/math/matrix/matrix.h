#ifndef __COREMATH_MATH_MATRIX_H__
#define __COREMATH_MATH_MATRIX_H__

namespace uge::math
{
    UGE_ALIGNED_STRUCT(Matrix, 16)
    {
        Vec4 X, Y, Z, W;

        Matrix() = default;
        Matrix(const Vec4& x, const Vec4& y, const Vec4& z, const Vec4& w);
        Matrix(const Float m[16]);
        Matrix(const Float m00, const Float m01, const Float m02, const Float m03,
               const Float m10, const Float m11, const Float m12, const Float m13,
               const Float m20, const Float m21, const Float m22, const Float m23,
               const Float m30, const Float m31, const Float m32, const Float m33);
        Matrix(const Matrix &other);

        Matrix &operator=(const Matrix &other);

        Bool operator==(const Matrix &other) const;
        Bool operator!=(const Matrix &other) const;

        Matrix& Set(const Matrix &other);
        Matrix& SetRows(const Float* f);
        Matrix& SetRows(const Vec4& x, const Vec4& y, const Vec4& z, const Vec4& w);
        Matrix& SetColumns(const Float* f);
        Matrix& SetColumns(const Vec4& x, const Vec4& y, const Vec4& z, const Vec4& w);
        Matrix& SetZero();
        Matrix& SetIdentity();

        Matrix& Set33(const Matrix &other);
        Matrix& Set33(const Vec4& x, const Vec4& y, const Vec4& z);
        Matrix& SetRotX33(const Float angle);
        Matrix& SetRotY33(const Float angle);
        Matrix& SetRotZ33(const Float angle);

        Matrix& SetScale(const Vec4& scale);
        Matrix& SetScale33(const Vec4& scale);
        Matrix& SetScale44(const Vec4& scale);
        Matrix& SetPreScale33( const Vec4& scale );
        Matrix& SetPreScale44( const Vec4& scale );
        Matrix& SetScale33( Float uniformScale );
        Vec4 GetScale33() const;
        Vec4 GetPreScale33() const;

        Matrix& SetTranslation(const Vec4& translation);
        Matrix& SetTranslation(const Float x, const Float y, const Float z);
        Vec4 GetTranslation() const;
        const Vec4& GetTranslationRef() const;
        Vec4& GetTranslationRef();

        Matrix InversedNoScale() const;
        Matrix& InverseNoScale();
        Matrix InversedFull() const;
        Matrix& InverseFull();
        Matrix Transposed() const;
        Matrix& Transpose();

        Vec4 GetColumn(const size_t index) const;
        Matrix& SetColumn(const size_t index, const Vec4& column);
        Vec4 GetRow(const size_t index) const;
        Matrix& SetRow(const size_t index, const Vec4& row);

        UGE_FORCE_INLINE const Vec4& operator[](const size_t index) const
        {
            UGE_ASSERT(index < 4, "Index out of bounds");
            return (&X)[index];
        }

        UGE_FORCE_INLINE Vec4& operator[](const size_t index)
        {
            UGE_ASSERT(index < 4, "Index out of bounds");
            return (&X)[index];
        }

        Vec4 GetAxisX() const;
        Vec4 GetAxisY() const;
        Vec4 GetAxisZ() const;

        void GetColumnMajor(Float* out) const;
        void GetColumnMajor3x4(Float* out) const;
        void SetColumnMajor3x4(const Float* data);
        void SetRowMajor4x3(const Float* data);

        Vec4 Transform(const Vec4& v) const;
        Vec4 Transform4x4(const Vec4& v) const;
        Vec4 TransformPoint(const Vec4& v) const;
        Vec3 TransformPoint(const Vec3& v) const;

        static Matrix Mul(const Matrix& a, const Matrix& b);
        Matrix operator*(const Matrix& other) const;
    };
}

#include "matrix.inl"

#endif  // __COREMATH_MATH_MATRIX_H__