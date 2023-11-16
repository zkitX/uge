#include "build.h"

#include "matrix.h"

namespace uge::math
{

// https://lxjk.github.io/2017/09/03/Fast-4x4-Matrix-Inverse-with-SSE-SIMD-Explained.html

#define MakeShuffleMask(x, y, z, w) (x | (y << 2) | (z << 4) | (w << 6))
#define VecSwizzleMask(vec, mask) _mm_shuffle_ps(vec, vec, mask)
#define VecSwizzle(vec, x, y, z, w) VecSwizzleMask(vec, MakeShuffleMask(x, y, z, w))
#define VecSwizzle1(vec, x) VecSwizzleMask(vec, MakeShuffleMask(x, x, x, x))
#define VecSwizzle_0022(vec) _mm_moveldup_ps(vec)
#define VecSwizzle_1133(vec) _mm_movehdup_ps(vec)
#define VecShuffle(vec1, vec2, x, y, z, w) _mm_shuffle_ps(vec1, vec2, MakeShuffleMask(x, y, z, w))
#define VecShuffle_0101(vec1, vec2) _mm_movelh_ps(vec1, vec2)
#define VecShuffle_2323(vec1, vec2) _mm_movehl_ps(vec2, vec1)

    Matrix Matrix::InversedNoScale() const
    {
        Matrix result;

        // Transpose the 3x3 rotation submatrix
        Vector t0 = VecShuffle_0101(X, Y);
        Vector t1 = VecShuffle_2323(X, Y);
        result.X = VecShuffle(t0, Z, 0, 2, 0, 3);
        result.Y = VecShuffle(t0, Z, 1, 3, 1, 3);
        result.Z = VecShuffle(t1, Z, 0, 2, 2, 3);

        // calculate the inverted translation
        result.W = _mm_mul_ps(result.X, VecSwizzle1(W, 0));
        result.W = _mm_add_ps(result.W, _mm_mul_ps(result.Y, VecSwizzle1(W, 1)));
        result.W = _mm_add_ps(result.W, _mm_mul_ps(result.Z, VecSwizzle1(W, 2)));
        result.W = _mm_sub_ps(_mm_setr_ps(0.f, 0.f, 0.f, 1.f), result.W);

        return result;
    }

    // for row major matrix
    // we use __m128 to represent 2x2 matrix as A = | A0  A1 |
    //                                              | A2  A3 |
    // 2x2 row major Matrix multiply A*B
    UGE_FORCE_INLINE static Vector Mat2Mul(Vector v1, Vector v2)
    {
        return _mm_add_ps(_mm_mul_ps(v1, VecSwizzle(v2, 0, 3, 0, 3)),
                          _mm_mul_ps(VecSwizzle(v1, 1, 0, 3, 2), VecSwizzle(v2, 2, 1, 2, 1)));
    }

    // 2x2 row major Matrix adjugate multiply (A#)*B
    UGE_FORCE_INLINE static Vector Mat2AdjMul(Vector v1, Vector v2)
    {
        return _mm_sub_ps(_mm_mul_ps(v1, VecSwizzle(v2, 3, 3, 0, 0)),
                          _mm_mul_ps(VecSwizzle(v1, 1, 1, 2, 2), VecSwizzle(v2, 2, 3, 0, 1)));
    }

    // 2x2 row major Matrix multiply adjugate A*(B#)
    UGE_FORCE_INLINE static Vector Mat2MulAdj(Vector v1, Vector v2)
    {
        return _mm_sub_ps(_mm_mul_ps(v1, VecSwizzle(v2, 3, 0, 3, 0)),
                          _mm_mul_ps(VecSwizzle(v1, 1, 0, 3, 2), VecSwizzle(v2, 2, 1, 2, 1)));
    }

    Matrix Matrix::InversedFull() const
    {
        // use block matrix method
	    // A is a matrix, then i(A) or iA means inverse of A, A# (or A_ in code) means adjugate of A, |A| (or detA in code) is determinant, tr(A) is trace

        // sub matrices
        Vector A = VecShuffle_0101(X, Y);
        Vector B = VecShuffle_2323(X, Y);
        Vector C = VecShuffle_0101(Z, W);
        Vector D = VecShuffle_2323(Z, W);

        // determinant as (|A| |B| |C| |D|)
        Vector detSub = _mm_sub_ps(
            _mm_mul_ps(VecShuffle(X, Z, 0, 2, 0, 2), VecShuffle(Y, W, 1, 3, 1, 3)),
            _mm_mul_ps(VecShuffle(X, Z, 1, 3, 1, 3), VecShuffle(Y, W, 0, 2, 0, 2))
        );
        Vector detA = VecSwizzle1(detSub, 0);
        Vector detB = VecSwizzle1(detSub, 1);
        Vector detC = VecSwizzle1(detSub, 2);
        Vector detD = VecSwizzle1(detSub, 3);

        // let iM = 1/|M| * | X  Y |
        //                  | Z  W |

        // D#C
        Vector D_C = Mat2AdjMul(D, C);
        // A#B
        Vector A_B = Mat2AdjMul(A, B);
        // X# = |D|A - B(D#C)
        Vector X_ = _mm_sub_ps(_mm_mul_ps(detD, A), Mat2Mul(B, D_C));
        // W# = |A|D - C(A#B)
        Vector W_ = _mm_sub_ps(_mm_mul_ps(detA, D), Mat2Mul(C, A_B));

        // |M| = |A|*|D| + ... (continue later)
		__m128 detM = _mm_mul_ps( detA, detD );

		// Y# = |B|C - D(A#B)#
		__m128 Y_ = _mm_sub_ps( _mm_mul_ps( detB, C ), Mat2MulAdj( D, A_B ) );
		// Z# = |C|B - A(D#C)#
		__m128 Z_ = _mm_sub_ps( _mm_mul_ps( detC, B ), Mat2MulAdj( A, D_C ) );

		// |M| = |A|*|D| + |B|*|C| ... (continue later)
		detM = _mm_add_ps( detM, _mm_mul_ps( detB, detC ) );

        // tr((A#B)(D#C))
		__m128 tr = _mm_mul_ps( A_B, VecSwizzle( D_C, 0, 2, 1, 3 ) );
		tr = _mm_hadd_ps( tr, tr );
		tr = _mm_hadd_ps( tr, tr );
		// |M| = |A|*|D| + |B|*|C| - tr((A#B)(D#C)
		detM = _mm_sub_ps( detM, tr );

        const __m128 adjSignMask = _mm_setr_ps( 1.0f, -1.0f, -1.0f, 1.0f );
		// (1/|M|, -1/|M|, -1/|M|, 1/|M|)
		__m128 rDetM = _mm_div_ps( adjSignMask, detM );

		X_ = _mm_mul_ps( X_, rDetM );
		Y_ = _mm_mul_ps( Y_, rDetM );
		Z_ = _mm_mul_ps( Z_, rDetM );
		W_ = _mm_mul_ps( W_, rDetM );

        // apply adjugate and store, here we combine adjugate shuffle and store shuffle
		Matrix r;
		r.X = VecShuffle( X_, Y_, 3, 1, 3, 1 );
		r.Y = VecShuffle( X_, Y_, 2, 0, 2, 0 );
		r.Z = VecShuffle( Z_, W_, 3, 1, 3, 1 );
		r.W = VecShuffle( Z_, W_, 2, 0, 2, 0 );

		return r;
    }

    Matrix Matrix::Transposed() const
    {
        Vector r0 = X;
        Vector r1 = Y;
        Vector r2 = Z;
        Vector r3 = W;

        _MM_TRANSPOSE4_PS(r0, r1, r2, r3);

        return Matrix(r0, r1, r2, r3);
    }

    Matrix Matrix::Mul(const Matrix& a, const Matrix& b)
    {
        return Matrix(
            b.Transform4x4(a.X),
            b.Transform4x4(a.Y),
            b.Transform4x4(a.Z),
            b.Transform4x4(a.W)
        );
    }

}