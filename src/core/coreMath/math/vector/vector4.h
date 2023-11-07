#ifndef __COREMATH_MATH_VECTOR4_H__
#define __COREMATH_MATH_VECTOR4_H__

namespace uge::math
{
    enum DotProductTypeMask
    {
        DotProduct2D = 0x3F,
        DotProduct3D = 0x7F,
        DotProduct4D = 0xFF
    };

    enum EqualMask
    {
        EqualMask2D = 0x03,
        EqualMask3D = 0x07,
        EqualMask4D = 0x0F
    };

    UGE_ALIGNED_STRUCT(Vec4, 16)
    {
        union
        {
            struct
            {
                Float x, y, z, w;
            };
            __m128 vec;
        };

        UGE_FORCE_INLINE Vec4() = default;

        Vec4(const Vec2 &v);
        Vec4(const Vec3 &v, const Float w = 1.f);
        Vec4(const Vec4 &v);
        Vec4(const Float f[4]);
        Vec4(const Float x, const Float y, const Float z, const Float w = 1.f);
        Vec4(const Float f);
        Vec4(const __m128 &v);
        Vec4(nullptr_t) = delete;

        operator __m128() const { return *reinterpret_cast<const __m128 *>(&x); }

        // operators
        Float &operator[](const size_t i);
        const Float &operator[](const size_t i) const;

        Vec4 operator-() const;
        Vec4 operator+(const Vec4 &v) const;
        Vec4 operator-(const Vec4 &v) const;
        Vec4 operator*(const Vec4 &v) const;
        Vec4 operator/(const Vec4 &v) const;

        Vec4 &operator+=(const Vec4 &v);
        Vec4 &operator-=(const Vec4 &v);
        Vec4 &operator*=(const Vec4 &v);
        Vec4 &operator/=(const Vec4 &v);

        Bool operator==(const Vec4 &v) const;
        Bool operator!=(const Vec4 &v) const;
        Bool operator<(const Vec4 &v) const;

        const Vec2& ToVec2() const;
        Vec2& ToVec2();
        const Vec3& ToVec3() const;
        Vec3& ToVec3();

        static Bool Equal(const Vec4 a, const Vec4 b, const EqualMask maskType);
        static Float Dot(const Vec4 &a, const Vec4 &b, const DotProductTypeMask maskType);
        Float Dot(const Vec4 &b, const DotProductTypeMask maskType) const;

        Float Magnitude(const DotProductTypeMask maskType) const;
        Float MagnitudeSquared(const DotProductTypeMask maskType) const;

        __m128 Normalize(__m128 v) const;
        Float Normalize(const DotProductTypeMask maskType);
        Vec4 Normalized(const DotProductTypeMask maskType);

        // distance calculations
        Float DistanceTo(const Vec4 &v) const;
        Float DistanceSquaredTo(const Vec4 &v) const;
        Float DistanceTo2D(const Vec4 &v) const;
        Float DistanceSquaredTo2D(const Vec4 &v) const;
        Float DistanceToEdge(const Vec4 &v0, const Vec4 &v1) const;
        Float DistanceToEdge2D(const Vec4 &v0, const Vec4 &v1) const;
        Float DistanceToEdgeSquared(const Vec4 &v0, const Vec4 &v1) const;
        Vec4 NearestPointOnEdge(const Vec4 &v0, const Vec4 &v1) const;

        static Vec4 Cross(const Vec4 &a, const Vec4 &b, const Float w);
    };
} // namespace uge::math

#include "vector4.inl"

#endif // __COREMATH_MATH_VECTOR4_H__