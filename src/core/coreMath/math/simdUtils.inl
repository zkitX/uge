#ifndef __COREMATH_MATH_SIMDUTILS_INL__
#define __COREMATH_MATH_SIMDUTILS_INL__

namespace uge::math
{
    namespace VectorHelpers
    {
        UGE_INLINE Vector Negate(Vector v)
        {
            return _mm_xor_ps(v, _mm_set1_ps(-0.f));
        }

        UGE_INLINE Vector Dot(Vector v1, Vector v2)
        {
            Vector r1 = _mm_mul_ps(v1, v2);
            Vector r2 = _mm_hadd_ps(r1, r1);
            Vector r3 = _mm_hadd_ps(r2, r2);
            return r3;
        }

        UGE_INLINE Vector Cross(Vector v1, Vector v2)
        {
            Vector c = _mm_sub_ps(
                _mm_mul_ps(v1, _mm_shuffle_ps(v2, v2, _MM_SHUFFLE(3, 0, 2, 1))),
                _mm_mul_ps(v2, _mm_shuffle_ps(v1, v1, _MM_SHUFFLE(3, 0, 2, 1))));
            return _mm_shuffle_ps(c, c, _MM_SHUFFLE(3, 0, 2, 1));
        }

        UGE_INLINE Vector RotateUnsafe(Vector quat, Vector vec)
        {
            Vector t = Cross(quat, vec);
            t = _mm_add_ps(t, t);
            return _mm_add_ps(vec, _mm_add_ps(_mm_mul_ps(t, _mm_shuffle_ps(quat, quat, _MM_SHUFFLE(3, 3, 3, 3))), Cross(quat, t)));
        }

        UGE_INLINE Vector Rotate(Vector quat, Vector vec)
        {
            Vector quat = Normalize(quat);
            return RotateUnsafe(quat, vec);
        }

        UGE_INLINE Vector Normalize(Vector v)
        {
            Vector vA = _mm_mul_ps(v, v);
            vA = _mm_add_ss(
                _mm_add_ss(_mm_shuffle_ps(vA, vA, _MM_SHUFFLE(0, 0, 0, 0)),
                           _mm_shuffle_ps(vA, vA, _MM_SHUFFLE(1, 1, 1, 1))),
                _mm_add_ss(_mm_shuffle_ps(vA, vA, _MM_SHUFFLE(2, 2, 2, 2)),
                           _mm_shuffle_ps(vA, vA, _MM_SHUFFLE(3, 3, 3, 3))));
            Vector length = _mm_sqrt_ss(vA);
            length = _mm_shuffle_ps(length, length, _MM_SHUFFLE(0, 0, 0, 0));
            Vector hasLength = _mm_cmpeq_ss(length, _mm_setzero_ps());
            hasLength = _mm_shuffle_ps(hasLength, hasLength, _MM_SHUFFLE(0, 0, 0, 0));
            Vector unitLength = _mm_div_ps(_mm_set1_ps(1.0f), length);
            return _mm_andnot_ps(hasLength, _mm_mul_ps(v, unitLength));
        }

        UGE_INLINE Vector QuatMultiplication(Vector xyzw, Vector abcd)
        {
            /* The product of two quaternions is:                                 */
            /* (X,Y,Z,W) = (xd+yc-zb+wa, -xc+yd+za+wb, xb-ya+zd+wc, -xa-yb-zc+wd) */

            __m128 wzyx = _mm_shuffle_ps(xyzw, xyzw, _MM_SHUFFLE(0, 1, 2, 3));
            __m128 baba = _mm_shuffle_ps(abcd, abcd, _MM_SHUFFLE(0, 1, 0, 1));
            __m128 dcdc = _mm_shuffle_ps(abcd, abcd, _MM_SHUFFLE(2, 3, 2, 3));

            /* variable names below are for parts of componens of result (X,Y,Z,W) */
            /* nX stands for -X and similarly for the other components             */

            /* znxwy  = (xb - ya, zb - wa, wd - zc, yd - xc) */
            __m128 ZnXWY = _mm_hsub_ps(_mm_mul_ps(xyzw, baba), _mm_mul_ps(wzyx, dcdc));

            /* xzynw  = (xd + yc, zd + wc, wb + za, yb + xa) */
            __m128 XZYnW = _mm_hadd_ps(_mm_mul_ps(xyzw, dcdc), _mm_mul_ps(wzyx, baba));

            /* _mm_shuffle_ps(XZYnW, ZnXWY, _MM_SHUFFLE(3,2,1,0)) */
            /*      = (xd + yc, zd + wc, wd - zc, yd - xc)        */
            /* _mm_shuffle_ps(ZnXWY, XZYnW, _MM_SHUFFLE(2,3,0,1)) */
            /*      = (zb - wa, xb - ya, yb + xa, wb + za)        */

            /* _mm_addsub_ps adds elements 1 and 3 and subtracts elements 0 and 2, so we get: */
            /* _mm_addsub_ps(*, *) = (xd+yc-zb+wa, xb-ya+zd+wc, wd-zc+yb+xa, yd-xc+wb+za)     */

            __m128 XZWY = _mm_addsub_ps(_mm_shuffle_ps(XZYnW, ZnXWY, _MM_SHUFFLE(3, 2, 1, 0)),
                                        _mm_shuffle_ps(ZnXWY, XZYnW, _MM_SHUFFLE(2, 3, 0, 1)));

            /* now we only need to shuffle the components in place and return the result      */
            return _mm_shuffle_ps(XZWY, XZWY, _MM_SHUFFLE(2, 1, 3, 0));

            /* operations: 6 shuffles, 4 multiplications, 3 compound additions/subtractions   */
        }
        
        UGE_INLINE Vector QuatLerpFast(Vector q1, Vector q2, Float t)
        {
            return Normalize(_mm_add_ps( _mm_mul_ps( q1, _mm_set_ps1( 1 - t ) ), _mm_mul_ps( q2, _mm_set_ps1( t ) ) ));
        }

        UGE_INLINE Vector QuatLerp(Vector q1, Vector q2, Float t)
        {
            const Vector cosTheta = Dot(q1, q2);
            const Vector q2a = _mm_and_ps(cosTheta, _mm_set_ps1(-0.f));
            q2 = _mm_xor_ps(q2, q2a);
            return QuatLerpFast(q1, q2, t);
        }

        UGE_INLINE Vector QuatSlerpFast(Vector q1, Vector q2, Float t, Vector cosTheta, Float tolerance)
        {
            const Float scalarCosTheta = Vec4( cosTheta ).x;
            if (scalarCosTheta > tolerance)
            {
                return QuatLerpFast(q1, q2, t);
            }
            else
            {
                const Float theta = ACos( scalarCosTheta );
                const Float sinTheta = Sin( theta );
                const Float t1 = Sin( ( 1.f - t ) * theta ); 
                const Float t2 = Sin( t * theta );
                return _mm_div_ps( _mm_add_ps( _mm_mul_ps( q1, _mm_set_ps1( t1 ) ), _mm_mul_ps( q2, _mm_set_ps1( t2 ) ) ), _mm_set_ps1( sinTheta ));
            }
        }

        UGE_INLINE Vector QuatSlerp(Vector q1, Vector q2, Float t, Float tolerance)
        {
            Vector cosTheta = Dot( q1, q2 );
            const Vector mask = _mm_and_ps( cosTheta, _mm_set_ps1( -0.f ) );
            q2 = _mm_xor_ps( q2, mask );
            cosTheta = _mm_xor_ps( cosTheta, mask );
            return QuatSlerpFast(q1, q2, t, cosTheta, tolerance);
        }

        UGE_INLINE Vector Transform(Vector translation, Vector rotation, Vector scale, Vector vec)
        {
            const Vector extra = Rotate(rotation, _mm_mul_ps(vec, scale));
            return _mm_add_ps(translation, extra);
        }

        UGE_INLINE Vector TransformUnsafe(Vector translation, Vector rotation, Vector scale, Vector vec)
        {
            const Vector extra = RotateUnsafe(rotation, _mm_mul_ps(vec, scale));
            return _mm_add_ps(translation, extra);
        }

        UGE_INLINE Vector Conjugate(Vector v)
        {
            static const Vector mask = _mm_set_ps(0.f, -0.f, -0.f, -0.f);
            return _mm_xor_ps(v, mask);
        }
        
    }
}

#endif // __COREMATH_MATH_SIMDUTILS_INL__