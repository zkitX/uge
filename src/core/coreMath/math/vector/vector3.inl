#ifndef __COREMATH_MATH_VECTOR3_INL__
#define __COREMATH_MATH_VECTOR3_INL__

namespace uge::math
{
    UGE_FORCE_INLINE Vec3::Vec3(Float x, Float y, Float z)
        : x(x), y(y), z(z)
    {
    }

    UGE_FORCE_INLINE Vec3::Vec3(const Vec3 &other)
        : x(other.x), y(other.y), z(other.z)
    {
    }

    UGE_FORCE_INLINE Vec3::Vec3(const Vec2 &v)
        : x(v.x), y(v.y), z(0.0f)
    {
    }

    UGE_FORCE_INLINE Vec3::Vec3(const Vec4 &v)
        : x(v.x), y(v.y), z(v.z)
    {
    }

    UGE_FORCE_INLINE Vec3::Vec3(const Float f[3])
        : x(f[0]), y(f[1]), z(f[2])
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

    UGE_FORCE_INLINE Float &Vec3::operator[](UInt32 index)
    {
        UGE_ASSERT(index < 3, "Index out of bounds");

        return v[index];
    }

    UGE_FORCE_INLINE const Float &Vec3::operator[](UInt32 index) const
    {
        UGE_ASSERT(index < 3, "Index out of bounds");

        return v[index];
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

        Float theta = ACos(dot) * t;
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

    const Vec3 Vec3::Zero = Vec3(0.0f, 0.0f, 0.0f);
    const Vec3 Vec3::One = Vec3(1.0f, 1.0f, 1.0f);
    const Vec3 Vec3::UnitX = Vec3(1.0f, 0.0f, 0.0f);
    const Vec3 Vec3::UnitY = Vec3(0.0f, 1.0f, 0.0f);
    const Vec3 Vec3::UnitZ = Vec3(0.0f, 0.0f, 1.0f);
}

#endif // __COREMATH_MATH_VECTOR3_INL__