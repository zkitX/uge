#include "vector4.h"
#ifndef __COREMATH_MATH_VECTOR4_INL__
#define __COREMATH_MATH_VECTOR4_INL__

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

    UGE_FORCE_INLINE Vec4& Vec4::operator+=(const Float f)
    {
        x += f;
        y += f;
        z += f;
        w += f;
        return *this;
    }

    UGE_FORCE_INLINE Vec4& Vec4::operator-=(const Float f)
    {
        x -= f;
        y -= f;
        z -= f;
        w -= f;
        return *this;
    }

    UGE_FORCE_INLINE Vec4& Vec4::operator*=(const Float f)
    {
        x *= f;
        y *= f;
        z *= f;
        w *= f;
        return *this;
    }

    UGE_FORCE_INLINE Vec4& Vec4::operator/=(const Float f)
    {
        x /= f;
        y /= f;
        z /= f;
        w /= f;
        return *this;
    }

    UGE_FORCE_INLINE Bool Vec4::operator==(const Vec4 &v) const
    {
        return Equal(*this, v, EqualMask4D);
    }

    UGE_FORCE_INLINE Bool Vec4::operator!=(const Vec4 &v) const
    {
        return Equal(*this, v, EqualMask4D);
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
        return reinterpret_cast<const Vec2&>(*this);
    }

    UGE_FORCE_INLINE Vec2 &Vec4::ToVec2()
    {
        return reinterpret_cast<Vec2&>(*this);
    }

    UGE_FORCE_INLINE const Vec3 &Vec4::ToVec3() const
    {
        return reinterpret_cast<const Vec3&>(*this);
    }

    UGE_FORCE_INLINE Vec3 &Vec4::ToVec3()
    {
        return reinterpret_cast<Vec3&>(*this);
    }

    UGE_FORCE_INLINE Bool Vec4::Equal(const Vec4 a, const Vec4 b, const EqualMask maskType)
    {
        return _mm_movemask_ps(_mm_cmpeq_ps(a.vec, b.vec)) == maskType;
    }

    inline Float Vec4::Dot(const Vec4 &a, const Vec4 &b, const DotProductTypeMask maskType)
    {
        return _mm_cvtss_f32(_mm_dp_ps(a.vec, b.vec, maskType));
    }

    inline Float Vec4::Dot(const Vec4 &b, const DotProductTypeMask maskType) const
    {
        return _mm_cvtss_f32(_mm_dp_ps(vec, b.vec, maskType));
    }

    UGE_FORCE_INLINE Float Vec4::Magnitude(const DotProductTypeMask maskType) const
    {
        return SqrtSSE(MagnitudeSquared(maskType));
    }

    UGE_FORCE_INLINE Float Vec4::MagnitudeSquared(const DotProductTypeMask maskType) const
    {
        return _mm_cvtss_f32(_mm_dp_ps(vec, vec, maskType));
    }

    UGE_INLINE __m128 Vec4::Normalize(__m128 v) const
    {
        __m128 vA = _mm_mul_ps(v, v);
        vA = _mm_add_ss(
            _mm_add_ss(_mm_shuffle_ps(vA, vA, _MM_SHUFFLE(0, 0, 0, 0)),
                       _mm_shuffle_ps(vA, vA, _MM_SHUFFLE(1, 1, 1, 1))),
            _mm_add_ss(_mm_shuffle_ps(vA, vA, _MM_SHUFFLE(2, 2, 2, 2)),
                       _mm_shuffle_ps(vA, vA, _MM_SHUFFLE(3, 3, 3, 3))));
        __m128 length = _mm_sqrt_ss(vA);
        length = _mm_shuffle_ps(length, length, _MM_SHUFFLE(0, 0, 0, 0));
        __m128 hasLength = _mm_cmpeq_ss(length, _mm_setzero_ps());
        hasLength = _mm_shuffle_ps( hasLength, hasLength, _MM_SHUFFLE( 0, 0, 0, 0 ) );
		__m128 unitLength = _mm_div_ps( _mm_set1_ps( 1.0f ), length );
		return _mm_andnot_ps( hasLength, _mm_mul_ps( v, unitLength) );
    }

    UGE_INLINE Vec4 Vec4::Normalize() const
    {
        return Vec4(Normalize(vec));
    }

    UGE_INLINE Float Vec4::Normalize(const DotProductTypeMask maskType)
    {
        Float len = Magnitude(maskType);
        if (len != 0)
        {
            switch (maskType)
            {
            case DotProduct2D:
                *this /= Vec4(len, len, 0.f, 0.f);
                break;
            case DotProduct3D:
                *this /= Vec4(len, len, len, 0.f);
                break;
            case DotProduct4D:
                *this /= Vec4(len, len, len, len);
                break;
            }
        }
        return len;
    }

    UGE_INLINE Vec4 Vec4::Normalized(const DotProductTypeMask maskType)
    {
        Float len = Magnitude(maskType);
        if (len == 0)
        {
            return *this;
        }
        else
        {
            switch (maskType)
            {
            case DotProduct2D:
                return *this / Vec4(len, len, 0.f, 0.f);
            case DotProduct3D:
                return *this / Vec4(len, len, len, 0.f);
            case DotProduct4D:
                return Vec4(Normalize(vec));
            }
        }
    }

    UGE_FORCE_INLINE void Vec4::Set(const Float x, const Float y, const Float z, const Float w)
    {
        this->x = x;
        this->y = y;
        this->z = z;
        this->w = w;
    }

    UGE_FORCE_INLINE void Vec4::Set(const Vec4& v)
    {
        Set(v.x, v.y, v.z, v.w);
    }

    UGE_FORCE_INLINE void Vec4::Set3(const Float x, const Float y, const Float z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    UGE_FORCE_INLINE void Vec4::Set3(const Vec4& v)
    {
        Set3(v.x, v.y, v.z);
    }

    UGE_FORCE_INLINE Vec4& Vec4::SetZero()
    {
        vec = _mm_setzero_ps();
        return *this;
    }

    UGE_FORCE_INLINE Vec4& Vec4::SetOne()
    {
        vec = _mm_set1_ps(1.f);
        return *this;
    }

    UGE_FORCE_INLINE Vec4& Vec4::Negate()
    {
        vec = _mm_sub_ps(_mm_setzero_ps(), vec);
        return *this;
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
        return delta.Magnitude(DotProduct3D);
    }

    UGE_INLINE Float Vec4::DistanceSquaredTo(const Vec4 &v) const
    {
        Vec4 delta = *this - v;
        return delta.MagnitudeSquared(DotProduct3D);
    }

    UGE_INLINE Float Vec4::DistanceTo2D(const Vec4 &other) const
    {
        Vec4 delta = *this - other;
        return delta.Magnitude(DotProduct2D);
    }

    UGE_INLINE Float Vec4::DistanceSquaredTo2D(const Vec4 &other) const
    {
        Vec4 delta = *this - other;
        return delta.MagnitudeSquared(DotProduct2D);
    }

    UGE_INLINE Float Vec4::DistanceToEdge(const Vec4 &v0, const Vec4 &v1) const
    {
        const Vec4 edge = (v1 - v0).Normalized(DotProduct3D);
        const Float ta = Dot(edge, v0, DotProduct3D);
        const Float tb = Dot(edge, v1, DotProduct3D);
        const Float p = Dot(edge, *this, DotProduct3D);
        if (p >= ta && p <= tb)
        {
            return DistanceTo(v0 + edge * (p-ta));
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

    UGE_INLINE Float Vec4::DistanceToEdge2D(const Vec4& a, const Vec4& b) const
    {
        Vec4 edgeXY = b - a;
        
        if (edgeXY.ToVec2().MagnitudeSquared() < 0.0001f)
        {
            return DistanceTo2D(a);
        }

        const Vec4 edge = edgeXY.Normalized(DotProduct2D);
        const Float ta = Dot(edge, a, DotProduct2D);
        const Float tb = Dot(edge, b, DotProduct2D);
        const Float p = Dot(edge, *this, DotProduct2D);
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
        Float len = d.Normalize(DotProduct3D);

        Vec4 v(x - v0.x, y - v0.y, z - v0.z);
        Float proj = len != 0.f ? Dot(v, d, DotProduct3D) / len : 0.f;

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
            return {v1 * proj + v0 * ( 1 - proj )};
        }
    }

    UGE_INLINE Vec4 Vec4::Cross(const Vec4 &a, const Vec4 &b, const Float w)
    {
        __m128 temp1 = _mm_shuffle_ps( a, a, _MM_SHUFFLE( 3, 0, 2, 1 ) );
		__m128 temp2 = _mm_shuffle_ps( b, b, _MM_SHUFFLE( 3, 1, 0, 2 ) );
		__m128 vResult = _mm_mul_ps( temp1, temp2 );
		temp1 = _mm_shuffle_ps( temp1, temp1, _MM_SHUFFLE( 3, 0, 2, 1 ) );
		temp2 = _mm_shuffle_ps( temp2, temp2, _MM_SHUFFLE( 3, 1, 0, 2 ) );
		Vec4 result = _mm_sub_ps( vResult, _mm_mul_ps( temp1, temp2 ) );
		result.w = w;
		return result;
    }

    UGE_FORCE_INLINE Vec4 Vec4::Zeros()
    {
        return { _mm_setzero_ps() };
    }

    UGE_FORCE_INLINE Vec4 Vec4::Ones()
    {
        return { _mm_set1_ps(1.f) };
    }

    UGE_FORCE_INLINE Vec4 Vec4::ZeroW()
    {
        return { _mm_set_ps(0.f, 0.f, 0.f, 1.f) };
    }
}
#endif // __COREMATH_MATH_VECTOR4_INL__