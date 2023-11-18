#ifndef __COREMATH_MATH_SIMDUTILS_H__
#define __COREMATH_MATH_SIMDUTILS_H__

namespace uge::math
{
    UGE_INLINE static Float AcosSSE(const Float &x)
    {
        Vector acos = _mm_acos_ps(_mm_load_ss(&x));
        Float result;
        _mm_store_ss(&result, acos);
        return result;
    }

    UGE_INLINE static Float CosSSE(const Float &x)
    {
        Vector cos = _mm_cos_ps(_mm_load_ss(&x));
        Float result;
        _mm_store_ss(&result, cos);
        return result;
    }

    UGE_INLINE static Float SinSSE(const Float &x)
    {
        Vector sin = _mm_sin_ps(_mm_load_ss(&x));
        Float result;
        _mm_store_ss(&result, sin);
        return result;
    }

    UGE_INLINE static Float SqrtSSE(const Float &x)
    {
        Vector root = _mm_sqrt_ss(_mm_load_ss(&x));
        Float result;
        _mm_store_ss(&result, root);
        return result;
    }

    namespace VectorHelpers
    {
        Vector Negate(Vector v);
        Vector Dot(Vector v1, Vector v2);
        Vector Cross(Vector v1, Vector v2);
        Vector RotateUnsafe(Vector quat, Vector vec);
        Vector Rotate(Vector quat, Vector vec);
        Vector Normalize(Vector v);
        Vector QuatMultiplication(Vector xyzw, Vector abcd);
        Vector QuatLerpFast(Vector q1, Vector q2, Float t);
        Vector QuatLerp(Vector q1, Vector q2, Float t);
        Vector QuatSlerpFast(Vector q1, Vector q2, Float t, Vector cosTheta, Float tolerance);
        Vector QuatSlerp(Vector q1, Vector q2, Float t, Float tolerance);
        Vector Transform(Vector translation, Vector rotation, Vector scale, Vector vec);
        Vector TransformUnsafe(Vector translation, Vector rotation, Vector scale, Vector vec);
        Vector Conjugate(Vector v);
    }
}

#endif // __COREMATH_MATH_SIMDUTILS_H__