#ifndef __COREMATH_MATH_VECTOR3_H__
#define __COREMATH_MATH_VECTOR3_H__

namespace uge::math
{
    struct Vec4;
    struct Vec3
    {
        union
        {
            struct
            {
                Float x, y, z;
            };
            Float v[3];
        };

        Vec3() = default;
        Vec3(Float x, Float y, Float z);
        Vec3(const Vec3 &other);

        Vec3(const Vec2 &v);
        Vec3(const Vec4 &v);
        Vec3(const Float f[3]);
        Vec3(std::nullptr_t) = delete;

        Vec3 &operator=(const Vec3 &other);

        void Set(Float x, Float y, Float z);

        Vec3 operator+(const Vec3 &other) const;
        Vec3 operator-(const Vec3 &other) const;
        Vec3 operator*(const Vec3 &other) const;
        Vec3 operator/(const Vec3 &other) const;

        Vec3 &operator+=(const Vec3 &other);
        Vec3 &operator-=(const Vec3 &other);
        Vec3 &operator*=(const Vec3 &other);
        Vec3 &operator/=(const Vec3 &other);

        Vec3 operator+(Float scalar) const;
        Vec3 operator-(Float scalar) const;
        Vec3 operator*(Float scalar) const;
        Vec3 operator/(Float scalar) const;

        Vec3 &operator+=(Float scalar);
        Vec3 &operator-=(Float scalar);
        Vec3 &operator*=(Float scalar);
        Vec3 &operator/=(Float scalar);

        Vec3 operator-() const;

        bool operator==(const Vec3 &other) const;
        bool operator!=(const Vec3 &other) const;

        Float &operator[](UInt32 index);
        const Float &operator[](UInt32 index) const;

        Float Length() const;
        Float LengthSquared() const;

        Float Dot(const Vec3 &other) const;
        Vec3 Cross(const Vec3 &other) const;

        Vec3 &Normalize();
        Vec3 Normalized() const;

        Vec3 Lerp(const Vec3 &other, Float t) const;
        Vec3 Slerp(const Vec3 &other, Float t) const;

        Vec3 Min(const Vec3 &a, const Vec3 &b);
        Vec3 Max(const Vec3 &a, const Vec3 &b);

        static const Vec3 Zero;
        static const Vec3 One;
        static const Vec3 UnitX;
        static const Vec3 UnitY;
        static const Vec3 UnitZ;
    };
}

#endif // __COREMATH_MATH_VECTOR3_H__