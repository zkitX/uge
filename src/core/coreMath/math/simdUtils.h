#ifndef __COREMATH_MATH_SIMDUTILS_H__
#define __COREMATH_MATH_SIMDUTILS_H__

namespace uge::math
{
    UGE_INLINE constexpr Float AcosSSE(const Float& x)
    {
        __m128 acos = _mm_acos_ps(_mm_load_ss(&x));
        Float result;
        _mm_store_ss(&result, acos);
        return result;
    }

    UGE_INLINE constexpr Float CosSSE(const Float& x)
    {
        __m128 cos = _mm_cos_ps(_mm_load_ss(&x));
        Float result;
        _mm_store_ss(&result, cos);
        return result;
    }

    UGE_INLINE constexpr Float SinSSE(const Float& x)
    {
        __m128 sin = _mm_sin_ps(_mm_load_ss(&x));
        Float result;
        _mm_store_ss(&result, sin);
        return result;
    }

    UGE_INLINE constexpr Float SqrtSSE(const Float& x)
    {
        __m128 root = _mm_sqrt_ss(_mm_load_ss(&x));
        Float result;
        _mm_store_ss(&result, root);
        return result;
    }

}

#endif // __COREMATH_MATH_SIMDUTILS_H__