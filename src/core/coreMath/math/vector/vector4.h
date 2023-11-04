#ifndef __COREMATH_MATH_VECTOR_H__
#define __COREMATH_MATH_VECTOR_H__

namespace uge::math
{
    struct Vec4
    {
        union 
        {
            struct { Float x, y, z, w; };
            Float v[4];
        };

        Vec4();
        Vec4(Float x, Float y, Float z, Float w);
        Vec4(const Vec4& other);

        Vec4& operator=(const Vec4& other);

        void Set(Float x, Float y, Float z, Float w);

        Vec4 operator+(const Vec4& other) const;
        Vec4 operator-(const Vec4& other) const;
        Vec4 operator*(const Vec4& other) const;
        Vec4 operator/(const Vec4& other) const;

        Vec4& operator+=(const Vec4& other);
        Vec4& operator-=(const Vec4& other);
        Vec4& operator*=(const Vec4& other);
        Vec4& operator/=(const Vec4& other);

        Vec4 operator+(Float scalar) const;
        Vec4 operator-(Float scalar) const;
        Vec4 operator*(Float scalar) const;
        Vec4 operator/(Float scalar) const;

        Vec4& operator+=(Float scalar);
        Vec4& operator-=(Float scalar);
        Vec4& operator*=(Float scalar);
        Vec4& operator/=(Float scalar);

        Vec4 operator-() const;

        Bool operator==(const Vec4& other) const;
        Bool operator!=(const Vec4& other) const;

        Float& operator[](UInt32 index);
        const Float& operator[](UInt32 index) const;

        Float Length() const;
        Float LengthSquared() const;

        Float Dot(const Vec4& other) const;

        Vec4& Normalize();
        Vec4 Normalized() const;

        Vec4 Lerp(const Vec4& other, Float t) const;
        Vec4 Slerp(const Vec4& other, Float t) const;

        Vec4 Min(const Vec4& a, const Vec4& b);
        Vec4 Max(const Vec4& a, const Vec4& b);

        static const Vec4 Zero;
        static const Vec4 One;
        static const Vec4 UnitX;
        static const Vec4 UnitY;
        static const Vec4 UnitZ;
        static const Vec4 UnitW;
    };
}

#include "vector4.inl"

#endif  // __COREMATH_MATH_VECTOR_H__