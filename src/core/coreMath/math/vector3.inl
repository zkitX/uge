#include "vector3.h"
#ifndef __COREMATH_MATH_VECTOR3_INL__
#define __COREMATH_MATH_VECTOR3_INL__

namespace uge::math
{
    UGE_FORCE_INLINE Vec3::Vec3()
        : x(0.0f), y(0.0f), z(0.0f)
    {
    }

    UGE_FORCE_INLINE Vec3::Vec3(Float x, Float y, Float z)
        : x(x), y(y), z(z)
    {
    }

    UGE_FORCE_INLINE Vec3::Vec3(const Vec3 &other)
        : x(other.x), y(other.y), z(other.z)
    {
    }

    UGE_FORCE_INLINE Vec3 &Vec3::operator=(const Vec3 &other)
    {
        x = other.x;
        y = other.y;
        z = other.z;

        return *this;
    }

    UGE_FORCE_INLINE void Vec3::Set(Float x, Float y, Float z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    UGE_FORCE_INLINE Vec3 Vec3::operator+(const Vec3 &other) const
    {
        return Vec3(x + other.x, y + other.y, z + other.z);
    }

    UGE_FORCE_INLINE Vec3 Vec3::operator-(const Vec3 &other) const
    {
        return Vec3(x - other.x, y - other.y, z - other.z);
    }

    UGE_FORCE_INLINE Vec3 Vec3::operator*(const Vec3 &other) const
    {
        return Vec3(x * other.x, y * other.y, z * other.z);
    }

    UGE_FORCE_INLINE Vec3 Vec3::operator/(const Vec3 &other) const
    {
        return Vec3(x / other.x, y / other.y, z / other.z);
    }

    UGE_FORCE_INLINE Vec3 &Vec3::operator+=(const Vec3 &other)
    {
        x += other.x;
        y += other.y;
        z += other.z;

        return *this;
    }

    UGE_FORCE_INLINE Vec3 &Vec3::operator-=(const Vec3 &other)
    {
        x -= other.x;
        y -= other.y;
        z -= other.z;

        return *this;
    }

    UGE_FORCE_INLINE Vec3 &Vec3::operator*=(const Vec3 &other)
    {
        x *= other.x;
        y *= other.y;
        z *= other.z;
    }

    UGE_FORCE_INLINE Vec3 &Vec3::operator/=(const Vec3 &other)
    {
        x /= other.x;
        y /= other.y;
        z /= other.z;
    }

    UGE_FORCE_INLINE Vec3 Vec3::operator+(Float scalar) const
    {
        return Vec3(x + scalar, y + scalar, z + scalar);
    }

    UGE_FORCE_INLINE Vec3 Vec3::operator-(Float scalar) const
    {
        return Vec3(x - scalar, y - scalar, z - scalar);
    }

    UGE_FORCE_INLINE Vec3 Vec3::operator*(Float scalar) const
    {
        return Vec3(x * scalar, y * scalar, z * scalar);
    }

    UGE_FORCE_INLINE Vec3 Vec3::operator/(Float scalar) const
    {
        return Vec3(x / scalar, y / scalar, z / scalar);
    }

    UGE_FORCE_INLINE Vec3 &Vec3::operator+=(Float scalar)
    {
        x += scalar;
        y += scalar;
        z += scalar;

        return *this;
    }

    UGE_FORCE_INLINE Vec3 &Vec3::operator-=(Float scalar)
    {
        x -= scalar;
        y -= scalar;
        z -= scalar;

        return *this;
    }

    UGE_FORCE_INLINE Vec3 &Vec3::operator*=(Float scalar)
    {
        x *= scalar;
        y *= scalar;
        z *= scalar;

        return *this;
    }

    UGE_FORCE_INLINE Vec3 &Vec3::operator/=(Float scalar)
    {
        x /= scalar;
        y /= scalar;
        z /= scalar;

        return *this;
    }

    UGE_FORCE_INLINE Vec3 Vec3::operator-() const
    {
        return Vec3(-x, -y, -z);
    }

    UGE_FORCE_INLINE bool Vec3::operator==(const Vec3 &other) const
    {
        return x == other.x && y == other.y && z == other.z;
    }

    UGE_FORCE_INLINE bool Vec3::operator!=(const Vec3 &other) const
    {
        return x != other.x || y != other.y || z != other.z;
    }

    UGE_FORCE_INLINE Float Vec3::Length() const
    {
        return Sqrt(x * x + y * y + z * z);
    }

    UGE_FORCE_INLINE Float Vec3::LengthSquared() const
    {
        return x * x + y * y + z * z;
    }

    UGE_FORCE_INLINE Float Vec3::Dot(const Vec3 &other) const
    {
        return x * other.x + y * other.y + z * other.z;
    }

    UGE_FORCE_INLINE Vec3 Vec3::Cross(const Vec3 &other) const
    {
        return Vec3(y * other.z - z * other.y,
                    z * other.x - x * other.z,
                    x * other.y - y * other.x);
    }

    UGE_FORCE_INLINE Vec3 &Vec3::Normalize()
    {
        Float length = Length();

        if (length > 0.0f)
        {
            x /= length;
            y /= length;
            z /= length;
        }

        return *this;
    }

    UGE_FORCE_INLINE Vec3 Vec3::Normalized() const
    {
        Float length = Length();

        if (length > 0.0f)
        {
            return Vec3(x / length, y / length, z / length);
        }

        return Vec3();
    }

    UGE_FORCE_INLINE Vec3 Vec3::Lerp(const Vec3 &other, Float t) const
    {
        return Vec3(x + (other.x - x) * t,
                    y + (other.y - y) * t,
                    z + (other.z - z) * t);
    }

    UGE_FORCE_INLINE Vec3 Vec3::Slerp(const Vec3 &other, Float t) const
    {
        Float dot = Dot(other);
        dot = Clamp(dot, -1.0f, 1.0f);

        Float theta = Acos(dot) * t;
        Vec3 relative = other - *this * dot;
        relative.Normalize();

        return *this * Cos(theta) + relative * Sin(theta);
    }

    UGE_FORCE_INLINE Vec3 Vec3::Min(const Vec3 &a, const Vec3 &b)
    {
        return Vec3(math::Min(a.x, b.x), math::Min(a.y, b.y), math::Min(a.z, b.z));
    }

    UGE_FORCE_INLINE Vec3 Vec3::Max(const Vec3 &a, const Vec3 &b)
    {
        return Vec3(math::Max(a.x, b.x), math::Max(a.y, b.y), math::Max(a.z, b.z));
    }
}

#endif // __COREMATH_MATH_VECTOR3_INL__