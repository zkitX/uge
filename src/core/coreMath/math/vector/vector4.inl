#include "vector4.h"
#ifndef __COREMATH_MATH_VECTOR4_INL__
#define __COREMATH_MATH_VECTOR4_INL__

namespace uge::math
{
    UGE_FORCE_INLINE Vec4::Vec4()
        : x(0.0f), y(0.0f), z(0.0f), w(0.0f)
    {
    }

    UGE_FORCE_INLINE Vec4::Vec4(Float x, Float y, Float z, Float w)
        : x(x), y(y), z(z), w(w)
    {
    }

    UGE_FORCE_INLINE Vec4::Vec4(const Vec4 &other)
        : x(other.x), y(other.y), z(other.z), w(other.w)
    {
    }

    UGE_FORCE_INLINE Vec4 &Vec4::operator=(const Vec4 &other)
    {
        x = other.x;
        y = other.y;
        z = other.z;
        w = other.w;

        return *this;
    }

    UGE_FORCE_INLINE void Vec4::Set(Float x, Float y, Float z, Float w)
    {
        this->x = x;
        this->y = y;
        this->z = z;
        this->w = w;
    }

    UGE_FORCE_INLINE Vec4 Vec4::operator+(const Vec4 &other) const
    {
        return Vec4(x + other.x, y + other.y, z + other.z, w + other.w);
    }

    UGE_FORCE_INLINE Vec4 Vec4::operator-(const Vec4 &other) const
    {
        return Vec4(x - other.x, y - other.y, z - other.z, w - other.w);
    }

    UGE_FORCE_INLINE Vec4 Vec4::operator*(const Vec4 &other) const
    {
        return Vec4(x * other.x, y * other.y, z * other.z, w * other.w);
    }

    UGE_FORCE_INLINE Vec4 Vec4::operator/(const Vec4 &other) const
    {
        return Vec4(x / other.x, y / other.y, z / other.z, w / other.w);
    }

    UGE_FORCE_INLINE Vec4 &Vec4::operator+=(const Vec4 &other)
    {
        x += other.x;
        y += other.y;
        z += other.z;
        w += other.w;

        return *this;
    }

    UGE_FORCE_INLINE Vec4 &Vec4::operator-=(const Vec4 &other)
    {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        w -= other.w;
    }

    UGE_FORCE_INLINE Vec4 &Vec4::operator*=(const Vec4 &other)
    {
        x *= other.x;
        y *= other.y;
        z *= other.z;
        w *= other.w;

        return *this;
    }

    UGE_FORCE_INLINE Vec4 &Vec4::operator/=(const Vec4 &other)
    {
        x /= other.x;
        y /= other.y;
        z /= other.z;
        w /= other.w;

        return *this;
    }

    UGE_FORCE_INLINE Vec4 Vec4::operator+(Float scalar) const
    {
        return Vec4(x + scalar, y + scalar, z + scalar, w + scalar);
    }

    UGE_FORCE_INLINE Vec4 Vec4::operator-(Float scalar) const
    {
        return Vec4(x - scalar, y - scalar, z - scalar, w - scalar);
    }

    UGE_FORCE_INLINE Vec4 Vec4::operator*(Float scalar) const
    {
        return Vec4(x * scalar, y * scalar, z * scalar, w * scalar);
    }

    UGE_FORCE_INLINE Vec4 Vec4::operator/(Float scalar) const
    {
        return Vec4(x / scalar, y / scalar, z / scalar, w / scalar);
    }

    UGE_FORCE_INLINE Vec4 &Vec4::operator+=(Float scalar)
    {
        x += scalar;
        y += scalar;
        z += scalar;
        w += scalar;

        return *this;
    }

    UGE_FORCE_INLINE Vec4 &Vec4::operator-=(Float scalar)
    {
        x -= scalar;
        y -= scalar;
        z -= scalar;
        w -= scalar;

        return *this;
    }

    UGE_FORCE_INLINE Vec4 &Vec4::operator*=(Float scalar)
    {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        w *= scalar;

        return *this;
    }

    UGE_FORCE_INLINE Vec4 &Vec4::operator/=(Float scalar)
    {
        x /= scalar;
        y /= scalar;
        z /= scalar;
        w /= scalar;

        return *this;
    }

    UGE_FORCE_INLINE Vec4 Vec4::operator-() const
    {
        return Vec4(-x, -y, -z, -w);
    }

    UGE_FORCE_INLINE Bool Vec4::operator==(const Vec4 &other) const
    {
        return (x == other.x && y == other.y && z == other.z && w == other.w);
    }

    UGE_FORCE_INLINE Bool Vec4::operator!=(const Vec4 &other) const
    {
        return (x != other.x || y != other.y || z != other.z || w != other.w);
    }

    UGE_FORCE_INLINE Float &Vec4::operator[](UInt32 index)
    {
        UGE_ASSERT(index < 4, "Index out of bounds.");

        return v[index];
    }

    UGE_FORCE_INLINE const Float &Vec4::operator[](UInt32 index) const
    {
        UGE_ASSERT(index < 4, "Index out of bounds.");

        return v[index];
    }

    UGE_FORCE_INLINE Float Vec4::Length() const
    {
        return Sqrt(x * x + y * y + z * z + w * w);
    }

    UGE_FORCE_INLINE Float Vec4::LengthSquared() const
    {
        return x * x + y * y + z * z + w * w;
    }

    UGE_FORCE_INLINE Float Vec4::Dot(const Vec4 &other) const
    {
        return x * other.x + y * other.y + z * other.z + w * other.w;
    }

    UGE_FORCE_INLINE Vec4 &Vec4::Normalize()
    {
        Float length = Length();

        if (length > 0.0f)
        {
            x /= length;
            y /= length;
            z /= length;
            w /= length;
        }

        return *this;
    }

    UGE_FORCE_INLINE Vec4 Vec4::Normalized() const
    {
        Float length = Length();

        if (length > 0.0f)
        {
            return Vec4(x / length, y / length, z / length, w / length);
        }

        return Vec4();
    }

    UGE_FORCE_INLINE Vec4 Vec4::Lerp(const Vec4 &other, Float t) const
    {
        return Vec4(x + (other.x - x) * t,
                    y + (other.y - y) * t,
                    z + (other.z - z) * t,
                    w + (other.w - w) * t);
    }

    UGE_FORCE_INLINE Vec4 Vec4::Slerp(const Vec4 &other, Float t) const
    {
        Float dot = Dot(other);

        if (dot > 0.9995f)
        {
            return Lerp(other, t);
        }

        dot = Clamp(dot, -1.0f, 1.0f);
        Float theta = Acos(dot) * t;
        Vec4 relative = (other - *this * dot).Normalized();

        return *this * Cos(theta) + relative * Sin(theta);
    }

    UGE_FORCE_INLINE Vec4 Vec4::Min(const Vec4 &a, const Vec4 &b)
    {
        return Vec4(math::Min(a.x, b.x),
                    math::Min(a.y, b.y),
                    math::Min(a.z, b.z),
                    math::Min(a.w, b.w));
    }

    UGE_FORCE_INLINE Vec4 Vec4::Max(const Vec4 &a, const Vec4 &b)
    {
        return Vec4(math::Max(a.x, b.x),
                    math::Max(a.y, b.y),
                    math::Max(a.z, b.z),
                    math::Max(a.w, b.w));
    }

    const Vec4 Vec4::Zero = Vec4(0.0f, 0.0f, 0.0f, 0.0f);
    const Vec4 Vec4::One = Vec4(1.0f, 1.0f, 1.0f, 1.0f);
    const Vec4 Vec4::UnitX = Vec4(1.0f, 0.0f, 0.0f, 0.0f);
    const Vec4 Vec4::UnitY = Vec4(0.0f, 1.0f, 0.0f, 0.0f);
    const Vec4 Vec4::UnitZ = Vec4(0.0f, 0.0f, 1.0f, 0.0f);
    const Vec4 Vec4::UnitW = Vec4(0.0f, 0.0f, 0.0f, 1.0f);
}

#endif // __COREMATH_MATH_VECTOR4_INL__