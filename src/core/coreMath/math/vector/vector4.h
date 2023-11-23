#ifndef __COREMATH_MATH_VECTOR4_H__
#define __COREMATH_MATH_VECTOR4_H__

namespace uge::math
{
    UGE_ALIGNED_STRUCT(Vec4, 16)
    {
        union
        {
            struct
            {
                Float x, y, z, w;
            };
            Vector vec;
        };

        UGE_FORCE_INLINE Vec4() = default;

        Vec4(const Vec2 &v);
        Vec4(const Vec3 &v, const Float w = 1.f);
        Vec4(const Vec4 &v);
        Vec4(const Float f[4]);
        Vec4(const Float x, const Float y, const Float z, const Float w = 1.f);
        Vec4(const Float f);
        Vec4(const Vector &v);
        Vec4(nullptr_t) = delete;

        operator Vector() const { return *reinterpret_cast<const Vector *>(&x); }

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

        Vec4 &operator+=(const Float f);
        Vec4 &operator-=(const Float f);
        Vec4 &operator*=(const Float f);
        Vec4 &operator/=(const Float f);

        Bool operator==(const Vec4 &v) const;
        Bool operator!=(const Vec4 &v) const;
        Bool operator<(const Vec4 &v) const;

        const Vec2 &ToVec2() const;
        Vec2 &ToVec2();
        const Vec3 &ToVec3() const;
        Vec3 &ToVec3();
        
        static Bool Equal2(const Vec4 a, const Vec4 b);
        static Bool Equal3(const Vec4 a, const Vec4 b);
        static Bool Equal4(const Vec4 a, const Vec4 b);

        static Bool Less2(const Vec4 a, const Vec4 b);
        static Bool Less3(const Vec4 a, const Vec4 b);
        static Bool Less4(const Vec4 a, const Vec4 b);

        static Bool LessEqual2(const Vec4 a, const Vec4 b);
        static Bool LessEqual3(const Vec4 a, const Vec4 b);
        static Bool LessEqual4(const Vec4 a, const Vec4 b);

        static Float Dot2(const Vec4 &a, const Vec4 &b);
        static Float Dot3(const Vec4 &a, const Vec4 &b);
        static Float Dot4(const Vec4 &a, const Vec4 &b);
        Float Dot2(const Vec4 &b) const;
        Float Dot3(const Vec4 &b) const;
        Float Dot4(const Vec4 &b) const;

        static Vec4 Cross(const Vec4 &a, const Vec4 &b, const Float w = 1.f);

        Float Mag2() const;
        Float Mag3() const;
        Float Mag4() const;
        Float SquareMag2() const;
        Float SquareMag3() const;
        Float SquareMag4() const;

        Float Normalize2();
        Float Normalize3();
        void Normalize4();
        Vec4 Normalized2() const;
        Vec4 Normalized3() const;
        Vec4 Normalized4() const; 

        void Set(const Float x, const Float y, const Float z, const Float w);
        void Set(const Vec4 &v);
        void Set3(const Float x, const Float y, const Float z);
        void Set3(const Vec4 &v);
        Vec4 &SetZero();
        Vec4 &SetOne();
        Vec4 &Negate();

        Bool IsNormalized2(const Float eps = 1e-4f) const;
        Bool IsNormalized3(const Float eps = 1e-4f) const;
        Bool IsNormalized4(const Float eps = 1e-4f) const;
        static Vec4 Min4(const Vec4 &a, const Vec4 &b);
        static Vec4 Max4(const Vec4 &a, const Vec4 &b);
        Bool IsValid() const;
        Bool IsZero() const;

        // distance calculations
        Float DistanceTo(const Vec4 &v) const;
        Float DistanceSquaredTo(const Vec4 &v) const;
        Float DistanceTo2D(const Vec4 &v) const;
        Float DistanceSquaredTo2D(const Vec4 &v) const;
        Float DistanceToEdge(const Vec4 &v0, const Vec4 &v1) const;
        Float DistanceToEdge2D(const Vec4 &v0, const Vec4 &v1) const;
        Float DistanceToEdgeSquared(const Vec4 &v0, const Vec4 &v1) const;
        Vec4 NearestPointOnEdge(const Vec4 &v0, const Vec4 &v1) const;

        static Vec4 MaxPlus();
        static Vec4 MaxMinus();
        static Vec4 Zeros();
        static Vec4 Ones();
        static Vec4 ZeroW();
    };
} // namespace uge::math

#endif // __COREMATH_MATH_VECTOR4_H__