#include "vector2.h"
#ifndef __COREMATH_MATH_VECTOR2_INL__
#define __COREMATH_MATH_VECTOR2_INL__

namespace uge::math
{
    UGE_FORCE_INLINE Vec2::Vec2()
        : x(0.0f), y(0.0f)
    {
    }

    UGE_FORCE_INLINE Vec2::Vec2(Float x, Float y)
        : x(x), y(y)
    {
    }

    UGE_FORCE_INLINE Vec2::Vec2(const Vec2 &other)
        : x(other.x), y(other.y)
    {
    }

    UGE_FORCE_INLINE Vec2 &Vec2::operator=(const Vec2 &other)
    {
        x = other.x;
        y = other.y;

        return *this;
    }

    UGE_FORCE_INLINE void Vec2::Set(Float x, Float y)
    {
        this->x = x;
        this->y = y;
    }

    UGE_FORCE_INLINE Vec2 Vec2::operator+(const Vec2 &other) const
    {
        return Vec2(x + other.x, y + other.y);
    }

    UGE_FORCE_INLINE Vec2 Vec2::operator-(const Vec2 &other) const
    {
        return Vec2(x - other.x, y - other.y);
    }

    UGE_FORCE_INLINE Vec2 Vec2::operator*(const Vec2 &other) const
    {
        return Vec2(x * other.x, y * other.y);
    }

    UGE_FORCE_INLINE Vec2 Vec2::operator/(const Vec2 &other) const
    {
        return Vec2(x / other.x, y / other.y);
    }

    UGE_FORCE_INLINE Vec2 &Vec2::operator+=(const Vec2 &other)
    {
        x += other.x;
        y += other.y;

        return *this;
    }

    UGE_FORCE_INLINE Vec2 &Vec2::operator-=(const Vec2 &other)
    {
        x -= other.x;
        y -= other.y;

        return *this;
    }

    UGE_FORCE_INLINE Vec2 &Vec2::operator*=(const Vec2 &other)
    {
        x *= other.x;
        y *= other.y;

        return *this;
    }

    UGE_FORCE_INLINE Vec2 &Vec2::operator/=(const Vec2 &other)
    {
        x /= other.x;
        y /= other.y;

        return *this;
    }

    UGE_FORCE_INLINE Vec2 Vec2::operator+(Float scalar) const
    {
        return Vec2(x + scalar, y + scalar);
    }

    UGE_FORCE_INLINE Vec2 Vec2::operator-(Float scalar) const
    {
        return Vec2(x - scalar, y - scalar);
    }

    UGE_FORCE_INLINE Vec2 Vec2::operator*(Float scalar) const
    {
        return Vec2(x * scalar, y * scalar);
    }

    UGE_FORCE_INLINE Vec2 Vec2::operator/(Float scalar) const
    {
        return Vec2(x / scalar, y / scalar);
    }

    UGE_FORCE_INLINE Vec2 &Vec2::operator+=(Float scalar)
    {
        x += scalar;
        y += scalar;

        return *this;
    }

    UGE_FORCE_INLINE Vec2 &Vec2::operator-=(Float scalar)
    {
        x -= scalar;
        y -= scalar;

        return *this;
    }

    UGE_FORCE_INLINE Vec2 &Vec2::operator*=(Float scalar)
    {
        x *= scalar;
        y *= scalar;

        return *this;
    }

    UGE_FORCE_INLINE Vec2 &Vec2::operator/=(Float scalar)
    {
        x /= scalar;
        y /= scalar;

        return *this;
    }

    UGE_FORCE_INLINE Bool Vec2::operator==(const Vec2 &other) const
    {
        return (x == other.x && y == other.y);
    }

    UGE_FORCE_INLINE Bool Vec2::operator!=(const Vec2 &other) const
    {
        return (x != other.x || y != other.y);
    }

    UGE_FORCE_INLINE Float &Vec2::operator[](UInt32 index)
    {
        UGE_ASSERT(index < 2, "Index out of range");

        return v[index];
    }

    UGE_FORCE_INLINE const Float &Vec2::operator[](UInt32 index) const
    {
        UGE_ASSERT(index < 2, "Index out of range");

        return v[index];
    }

    UGE_FORCE_INLINE Float Vec2::Length() const
    {
        return Sqrt(x * x + y * y);
    }

    UGE_FORCE_INLINE Float Vec2::LengthSquared() const
    {
        return x * x + y * y;
    }

    UGE_FORCE_INLINE Float Vec2::Dot(const Vec2 &other) const
    {
        return x * other.x + y * other.y;
    }

    UGE_FORCE_INLINE Float Vec2::Magnitude() const
    {
        return SqrtSSE(MagnitudeSquared());
    }

    UGE_FORCE_INLINE Float Vec2::MagnitudeSquared() const
    {
        return x*x + y*y;
    }

    UGE_FORCE_INLINE Vec2 Vec2::Normalize() const
    {
        Float length = Length();

        if (length > 0.0f)
        {
            return Vec2(x / length, y / length);
        }

        return Vec2(0.0f, 0.0f);
    }

    UGE_FORCE_INLINE Vec2 Vec2::Reflect(const Vec2 &normal) const
    {
        return *this - (normal * (2.0f * Dot(normal)));
    }

    UGE_FORCE_INLINE Vec2 Vec2::Refract(const Vec2 &normal, Float eta) const
    {
        Float dot = Dot(normal);
        Float k = 1.0f - eta * eta * (1.0f - dot * dot);

        if (k < 0.0f)
        {
            return Vec2(0.0f, 0.0f);
        }

        return *this * eta - normal * (eta * dot + Sqrt(k));
    }

    UGE_FORCE_INLINE Vec2 Vec2::Project(const Vec2 &other) const
    {
        Float dot = Dot(other);
        Float length = other.LengthSquared();

        if (length > 0.0f)
        {
            return other * (dot / length);
        }

        return Vec2(0.0f, 0.0f);
    }

    UGE_FORCE_INLINE Vec2 Vec2::ProjectPerp(const Vec2 &other) const
    {
        return *this - Project(other);
    }

    UGE_FORCE_INLINE Vec2 Vec2::Lerp(const Vec2 &other, Float t) const
    {
        return *this + (other - *this) * t;
    }

    UGE_FORCE_INLINE Vec2 Vec2::Slerp(const Vec2 &other, Float t) const
    {
        Float dot = Dot(other);
        dot = Clamp(dot, -1.0f, 1.0f);

        Float theta = Acos(dot) * t;
        Vec2 relative = other - *this * dot;
        relative.Normalize();

        return ((*this * Cos(theta)) + (relative * Sin(theta)));
    }

    UGE_FORCE_INLINE Vec2 Vec2::Nlerp(const Vec2 &other, Float t) const
    {
        return Lerp(other, t).Normalize();
    }

    UGE_FORCE_INLINE Vec2 Vec2::Rotate(Float angle) const
    {
        Float cosAngle = Cos(angle);
        Float sinAngle = Sin(angle);

        return Vec2(x * cosAngle - y * sinAngle, x * sinAngle + y * cosAngle);
    }

    inline Vec2 Vec2::Rotate(const Vec2 &axis, Float angle) const
    {
        return (*this - axis).Rotate(angle) + axis;
    }

    inline Vec2 Vec2::Rotate(const Vec2 &axis, const Vec2 &pivot, Float angle) const
    {
        Vec2 relative = *this - pivot;
        Vec2 rotated = relative.Rotate(angle);
        Vec2 relativeAxis = axis - pivot;
        Vec2 rotatedAxis = relativeAxis.Rotate(angle);

        return rotated - relative + rotatedAxis;
    }

    inline Vec2 Vec2::Rotate(const Vec2 &axis, const Vec2 &pivot, Float angle, Float scale) const
    {
        Vec2 relative = *this - pivot;
        Vec2 rotated = relative.Rotate(angle) * scale;
        Vec2 relativeAxis = axis - pivot;
        Vec2 rotatedAxis = relativeAxis.Rotate(angle) * scale;

        return rotated - relative + rotatedAxis;
    }

}

#endif // __COREMATH_MATH_VECTOR2_INL__