#ifndef __COREMATH_MATH_VECTOR4_INL__
#define __COREMATH_MATH_VECTOR4_INL__

#include "vector2.h"
#include "vector3.h"

namespace uge::math
{
    UGE_FORCE_INLINE Vec4::Vec4(const Vec2 &v)
        : x(v.x), y(v.y), z(0.f), w(1.f)
    {
    }

    UGE_FORCE_INLINE Vec4::Vec4(const Vec3 &v, const Float w)
        : x(v.x), y(v.y), z(v.z), w(w)
    {
    }

    UGE_FORCE_INLINE Vec4::Vec4(const Vec4 &v)
        : x(v.x), y(v.y), z(v.z), w(v.w)
    {
    }

    UGE_FORCE_INLINE Vec4::Vec4(const Float f[4])
        : x(f[0]), y(f[1]), z(f[2]), w(f[3])
    {
    }

    UGE_FORCE_INLINE Vec4::Vec4(const Float x, const Float y, const Float z, const Float w)
        : x(x), y(y), z(z), w(w)
    {
    }

    UGE_FORCE_INLINE Vec4::Vec4(const Float f)
        : x(f), y(f), z(f), w(f)
    {
    }

    UGE_FORCE_INLINE Vec4::Vec4(const __m128 &v)
        : vec(v)
    {
    }

    UGE_INLINE Float &Vec4::operator[](const size_t i)
    {
        UGE_ASSERT(i < 4, "Index out of range");
        return (&x)[i];
    }

    UGE_INLINE const Float &Vec4::operator[](const size_t i) const
    {
        UGE_ASSERT(i < 4, "Index out of range");
        return (&x)[i];
    }

    UGE_FORCE_INLINE Vec4 Vec4::operator-() const
    {
        return _mm_sub_ps(_mm_setzero_ps(), vec);
    }

    UGE_FORCE_INLINE Vec4 Vec4::operator+(const Vec4 &v) const
    {
        return _mm_add_ps(vec, v.vec);
    }

    UGE_FORCE_INLINE Vec4 Vec4::operator-(const Vec4 &v) const
    {
        return _mm_sub_ps(vec, v.vec);
    }

    UGE_FORCE_INLINE Vec4 Vec4::operator*(const Vec4 &v) const
    {
        return _mm_mul_ps(vec, v.vec);
    }

    UGE_FORCE_INLINE Vec4 Vec4::operator/(const Vec4 &v) const
    {
        return _mm_div_ps(vec, v.vec);
    }

    UGE_FORCE_INLINE Vec4 &Vec4::operator+=(const Vec4 &v)
    {
        vec = _mm_add_ps(vec, v.vec);
        return *this;
    }

    UGE_FORCE_INLINE Vec4 &Vec4::operator-=(const Vec4 &v)
    {
        vec = _mm_sub_ps(vec, v.vec);
        return *this;
    }

    UGE_FORCE_INLINE Vec4 &Vec4::operator*=(const Vec4 &v)
    {
        vec = _mm_mul_ps(vec, v.vec);
        return *this;
    }

    UGE_FORCE_INLINE Vec4 &Vec4::operator/=(const Vec4 &v)
    {
        vec = _mm_div_ps(vec, v.vec);
        return *this;
    }

    UGE_FORCE_INLINE Vec4 &Vec4::operator+=(const Float f)
    {
        x += f;
        y += f;
        z += f;
        w += f;
        return *this;
    }

    UGE_FORCE_INLINE Vec4 &Vec4::operator-=(const Float f)
    {
        x -= f;
        y -= f;
        z -= f;
        w -= f;
        return *this;
    }

    UGE_FORCE_INLINE Vec4 &Vec4::operator*=(const Float f)
    {
        x *= f;
        y *= f;
        z *= f;
        w *= f;
        return *this;
    }

    UGE_FORCE_INLINE Vec4 &Vec4::operator/=(const Float f)
    {
        x /= f;
        y /= f;
        z /= f;
        w /= f;
        return *this;
    }

    UGE_FORCE_INLINE Bool Vec4::operator==(const Vec4 &v) const
    {
        return Vec4::Equal4(*this, v);
    }

    UGE_FORCE_INLINE Bool Vec4::operator!=(const Vec4 &v) const
    {
        return !Vec4::Equal4(*this, v);
    }

    UGE_FORCE_INLINE Bool Vec4::operator<(const Vec4 &v) const
    {
        if (x == v.x)
        {
            if (y == v.y)
            {
                if (z == v.z)
                {
                    return w < v.w;
                }
                return z < v.z;
            }
            return y < v.y;
        }
        return x < v.x;
    }

    UGE_FORCE_INLINE const Vec2 &Vec4::ToVec2() const
    {
        return reinterpret_cast<const Vec2 &>(*this);
    }

    UGE_FORCE_INLINE Vec2 &Vec4::ToVec2()
    {
        return reinterpret_cast<Vec2 &>(*this);
    }

    UGE_FORCE_INLINE const Vec3 &Vec4::ToVec3() const
    {
        return reinterpret_cast<const Vec3 &>(*this);
    }

    UGE_FORCE_INLINE Vec3 &Vec4::ToVec3()
    {
        return reinterpret_cast<Vec3 &>(*this);
    }

    UGE_FORCE_INLINE Bool Vec4::Equal2(const Vec4 a, const Vec4 b)
    {
        return ( _mm_movemask_ps( _mm_cmpeq_ps( a, b ) ) & 0x3 ) == 0x3;
    }

    UGE_FORCE_INLINE Bool Vec4::Equal3(const Vec4 a, const Vec4 b)
    {
        return ( _mm_movemask_ps( _mm_cmpeq_ps( a, b ) ) & 0x7 ) == 0x7;
    }

    UGE_FORCE_INLINE Bool Vec4::Equal4(const Vec4 a, const Vec4 b)
    {
        return ( _mm_movemask_ps( _mm_cmpeq_ps( a, b ) ) ) == 0xF;
    }

    UGE_FORCE_INLINE Bool Vec4::Less2(const Vec4 a, const Vec4 b)
    {
        return ( _mm_movemask_ps( _mm_cmplt_ps( a, b ) ) & 0x3 ) == 0x3;
    }

    UGE_FORCE_INLINE Bool Vec4::Less3(const Vec4 a, const Vec4 b)
    {
        return ( _mm_movemask_ps( _mm_cmplt_ps( a, b ) ) & 0x7 ) == 0x7;
    }

    UGE_FORCE_INLINE Bool Vec4::Less4(const Vec4 a, const Vec4 b)
    {
        return ( _mm_movemask_ps( _mm_cmplt_ps( a, b ) ) ) == 0xF;
    }

    UGE_FORCE_INLINE Bool Vec4::LessEqual2(const Vec4 a, const Vec4 b)
    {
        return ( _mm_movemask_ps( _mm_cmple_ps( a, b ) ) & 0x3 ) == 0x3;
    }

    UGE_FORCE_INLINE Bool Vec4::LessEqual3(const Vec4 a, const Vec4 b)
    {
        return ( _mm_movemask_ps( _mm_cmple_ps( a, b ) ) & 0x7 ) == 0x7;
    }

    UGE_FORCE_INLINE Bool Vec4::LessEqual4(const Vec4 a, const Vec4 b)
    {
        return ( _mm_movemask_ps( _mm_cmple_ps( a, b ) ) ) == 0xF;
    }

    UGE_FORCE_INLINE Float Vec4::Dot2(const Vec4 &a, const Vec4 &b)
    {
        return _mm_cvtss_f32(_mm_dp_ps(a.vec, b.vec, 0x3F));
    }

    UGE_FORCE_INLINE Float Vec4::Dot3(const Vec4 &a, const Vec4 &b)
    {
        return _mm_cvtss_f32(_mm_dp_ps(a.vec, b.vec, 0x7F));
    }

    UGE_FORCE_INLINE Float Vec4::Dot4(const Vec4 &a, const Vec4 &b)
    {
        return _mm_cvtss_f32(_mm_dp_ps(a.vec, b.vec, 0xFF));
    }

    UGE_FORCE_INLINE Float Vec4::Dot2(const Vec4 &b) const
    {
        return _mm_cvtss_f32(_mm_dp_ps(vec, b.vec, 0x3F));
    }

    UGE_FORCE_INLINE Float Vec4::Dot3(const Vec4 &b) const
    {
        return _mm_cvtss_f32(_mm_dp_ps(vec, b.vec, 0x7F));
    }

    UGE_FORCE_INLINE Float Vec4::Dot4(const Vec4 &b) const
    {
        return _mm_cvtss_f32(_mm_dp_ps(vec, b.vec, 0xFF));
    }

    UGE_FORCE_INLINE Float Vec4::Mag2() const
    {
        return SqrtSSE(SquareMag2());
    }

    UGE_FORCE_INLINE Float Vec4::Mag3() const
    {
        return SqrtSSE(SquareMag3());
    }

    UGE_FORCE_INLINE Float Vec4::Mag4() const
    {
        return SqrtSSE(SquareMag4());
    }

    UGE_FORCE_INLINE Float Vec4::SquareMag2() const
    {
        return _mm_cvtss_f32( _mm_dp_ps( vec, vec, 0x3F ) );
    }

    UGE_FORCE_INLINE Float Vec4::SquareMag3() const
    {
        return _mm_cvtss_f32( _mm_dp_ps( vec, vec, 0x7F ) );
    }

    UGE_FORCE_INLINE Float Vec4::SquareMag4() const
    {
        return _mm_cvtss_f32( _mm_dp_ps( vec, vec, 0xFF ) );
    }

    UGE_INLINE Float Vec4::Normalize2()
    {
        Float len = Mag2();
        if (len != 0)
        {
            *this /= Vec4(len, len, 0.f, 0.f);
        }
        return len;
    }

    UGE_INLINE Float Vec4::Normalize3()
    {
        Float len = Mag3();
        if (len != 0)
        {
            *this /= Vec4(len, len, len, 0.f);
        }
        return len;
    }

    UGE_INLINE void Vec4::Normalize4()
    {
        vec = VectorHelpers::Normalize(vec);
    }

    UGE_INLINE Vec4 Vec4::Normalized2() const
    {
        Float len = Mag2();
        if (len == 0)
        {
            return *this;
        }
        else
        {
            return *this / Vec4(len, len, 0.f, 0.f);
        }
    }

    UGE_INLINE Vec4 Vec4::Normalized3() const
    {
        Float len = Mag3();
        if (len == 0)
        {
            return *this;
        }
        else
        {
            return *this / Vec4(len, len, len, 0.f);
        }
    }

    UGE_INLINE Vec4 Vec4::Normalized4() const
    {
        return Vec4(VectorHelpers::Normalize(vec));
    }

    UGE_FORCE_INLINE void Vec4::Set(const Float x, const Float y, const Float z, const Float w)
    {
        this->x = x;
        this->y = y;
        this->z = z;
        this->w = w;
    }

    UGE_FORCE_INLINE void Vec4::Set(const Vec4 &v)
    {
        Set(v.x, v.y, v.z, v.w);
    }

    UGE_FORCE_INLINE void Vec4::Set3(const Float x, const Float y, const Float z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    UGE_FORCE_INLINE void Vec4::Set3(const Vec4 &v)
    {
        Set3(v.x, v.y, v.z);
    }

    UGE_FORCE_INLINE Vec4 &Vec4::SetZero()
    {
        vec = _mm_setzero_ps();
        return *this;
    }

    UGE_FORCE_INLINE Vec4 &Vec4::SetOne()
    {
        vec = _mm_set1_ps(1.f);
        return *this;
    }

    UGE_FORCE_INLINE Vec4 &Vec4::Negate()
    {
        vec = _mm_sub_ps(_mm_setzero_ps(), vec);
        return *this;
    }

    UGE_INLINE Bool Vec4::IsNormalized2(const Float eps) const
    {
        const Float len = SquareMag2();
        return fabsf(len - 1.f) < eps;
    }

    UGE_INLINE Bool Vec4::IsNormalized3(const Float eps) const
    {
        const Float len = SquareMag3();
        return fabsf(len - 1.f) < eps;
    }

    UGE_INLINE Bool Vec4::IsNormalized4(const Float eps) const
    {
        const Float len = SquareMag4();
        return fabsf(len - 1.f) < eps;
    }

    UGE_INLINE Vec4 Vec4::Min4(const Vec4 &a, const Vec4 &b)
    {
        return _mm_min_ps(a, b);
    }

    UGE_INLINE Vec4 Vec4::Max4(const Vec4 &a, const Vec4 &b)
    {
        return _mm_max_ps(a, b);
    }

    UGE_INLINE Bool Vec4::IsValid() const
    {
        return std::isfinite(x) && std::isfinite(y) && std::isfinite(z) && std::isfinite(w);
    }

    UGE_INLINE Bool Vec4::IsZero() const
    {
        return x == 0.f && y == 0.f && z == 0.f && w == 0.f;
    }

    UGE_INLINE Float Vec4::DistanceTo(const Vec4 &v) const
    {
        Vec4 delta = *this - v;
        return delta.Mag3();
    }

    UGE_INLINE Float Vec4::DistanceSquaredTo(const Vec4 &v) const
    {
        Vec4 delta = *this - v;
        return delta.Mag3();
    }

    UGE_INLINE Float Vec4::DistanceTo2D(const Vec4 &other) const
    {
        Vec4 delta = *this - other;
        return delta.Mag2();
    }

    UGE_INLINE Float Vec4::DistanceSquaredTo2D(const Vec4 &other) const
    {
        Vec4 delta = ToVec2() - other.ToVec2();
        return delta.SquareMag2();
    }

    UGE_INLINE Float Vec4::DistanceToEdge(const Vec4 &v0, const Vec4 &v1) const
    {
        const Vec4 edge = (v1 - v0).Normalized3();
        const Float ta = Vec4::Dot3(edge, v0);
        const Float tb = Vec4::Dot3(edge, v1);
        const Float p = Vec4::Dot3(edge, *this);
        if (p >= ta && p <= tb)
        {
            return DistanceTo(v0 + edge * (p - ta));
        }
        else if (p < ta)
        {
            return DistanceTo(v0);
        }
        else
        {
            return DistanceTo(v1);
        }
    }

    UGE_INLINE Float Vec4::DistanceToEdge2D(const Vec4 &a, const Vec4 &b) const
    {
        Vec4 edgeXY = b - a;

        if (edgeXY.ToVec2().MagnitudeSquared() < 0.0001f)
        {
            return DistanceTo2D(a);
        }

        const Vec4 edge = edgeXY.Normalized2();
        const Float ta = Vec4::Dot2(edge, a);
        const Float tb = Vec4::Dot2(edge, b);
        const Float p = Vec4::Dot2(edge, *this);
        if (p >= ta && p <= tb)
        {
            return DistanceTo2D(a + edge * (p - ta));
        }
        else if (p < ta)
        {
            return DistanceTo2D(a);
        }
        else
        {
            return DistanceTo2D(b);
        }
    }

    UGE_INLINE Vec4 Vec4::NearestPointOnEdge(const Vec4 &v0, const Vec4 &v1) const
    {
        Vec4 d = v1 - v0;
        Float len = d.Normalize3();

        Vec4 v(x - v0.x, y - v0.y, z - v0.z);
        Float proj = len != 0.f ? Vec4::Dot3(v, d) / len : 0.f;

        if (proj <= 0)
        {
            return v0;
        }
        else if (proj >= 1)
        {
            return v1;
        }
        else
        {
            return {v1 * proj + v0 * (1 - proj)};
        }
    }

    UGE_INLINE Vec4 Vec4::Cross(const Vec4 &a, const Vec4 &b, const Float w)
    {
        __m128 temp1 = _mm_shuffle_ps(a, a, _MM_SHUFFLE(3, 0, 2, 1));
        __m128 temp2 = _mm_shuffle_ps(b, b, _MM_SHUFFLE(3, 1, 0, 2));
        __m128 vResult = _mm_mul_ps(temp1, temp2);
        temp1 = _mm_shuffle_ps(temp1, temp1, _MM_SHUFFLE(3, 0, 2, 1));
        temp2 = _mm_shuffle_ps(temp2, temp2, _MM_SHUFFLE(3, 1, 0, 2));
        Vec4 result = _mm_sub_ps(vResult, _mm_mul_ps(temp1, temp2));
        result.w = w;
        return result;
    }

    UGE_FORCE_INLINE Vec4 Vec4::MaxPlus()
    {
        return {_mm_set_ps(FLT_MAX, FLT_MAX, FLT_MAX, FLT_MAX)};
    }

    UGE_FORCE_INLINE Vec4 Vec4::MaxMinus()
    {
        return {_mm_set_ps(-FLT_MAX, -FLT_MAX, -FLT_MAX, -FLT_MAX)};
    }

    UGE_FORCE_INLINE Vec4 Vec4::Zeros()
    {
        return {_mm_setzero_ps()};
    }

    UGE_FORCE_INLINE Vec4 Vec4::Ones()
    {
        return {_mm_set1_ps(1.f)};
    }

    UGE_FORCE_INLINE Vec4 Vec4::ZeroW()
    {
        return {_mm_set_ps(0.f, 0.f, 0.f, 1.f)};
    }
}
#endif // __COREMATH_MATH_VECTOR4_INL__