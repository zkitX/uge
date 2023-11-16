#ifndef __COREMATH_MATH_UTILS_H__
#define __COREMATH_MATH_UTILS_H__

#define M_E        2.71828182845904523536   // e
#define M_LOG2E    1.44269504088896340736   // log2(e)
#define M_LOG10E   0.434294481903251827651  // log10(e)
#define M_LN2      0.693147180559945309417  // ln(2)
#define M_LN10     2.30258509299404568402   // ln(10)
#define M_PI       3.14159265358979323846   // pi
#define M_PI_2     1.57079632679489661923   // pi/2
#define M_PI_4     0.785398163397448309616  // pi/4
#define M_1_PI     0.318309886183790671538  // 1/pi
#define M_2_PI     0.636619772367581343076  // 2/pi
#define M_2_SQRTPI 1.12837916709551257390   // 2/sqrt(pi)
#define M_SQRT2    1.41421356237309504880   // sqrt(2)
#define M_SQRT1_2  0.707106781186547524401  // 1/sqrt(2)

namespace uge::math
{
    typedef __m128 Vector;

    template <typename T>
    UGE_INLINE constexpr const T &Max(const T &a, const T &b)
    {
        return (a > b) ? a : b;
    }

    template <typename T>
    UGE_INLINE constexpr const T &Min(const T &a, const T &b)
    {
        return (a < b) ? a : b;
    }

    template <typename T>
    UGE_INLINE constexpr const T &Clamp(const T &value, const T &min, const T &max)
    {
        return Max(min, Min(value, max));
    }

    template <typename T>
    UGE_INLINE constexpr T Abs(const T &value)
    {
        return (value >= T{0}) ? value : -value;
    }

    template <typename T>
    UGE_INLINE constexpr T Sign(const T &value)
    {
        return (value > T{0}) ? T{1} : ((value < T{0}) ? T{-1} : T{0});
    }

    template <typename T>
    UGE_INLINE constexpr T Sqr(const T &value)
    {
        return value * value;
    }

    UGE_INLINE Float ASin(Float f)
    {
        UGE_ASSERT(Abs(f) <= 1.0f, "Value must be in range [-1, 1]");
        return ::asin(f);
    }

    UGE_INLINE Float ACos(Float f)
    {
        UGE_ASSERT(Abs(f) <= 1.0f, "Value must be in range [-1, 1]");
        return ::acos(f);
    }

    UGE_INLINE Float ASinSafe(Float f)
    {
        if (Abs(f) >= 1.f)
        {
		    f = ( f>0 )	? 0.5f * M_PI : -0.5f * M_PI;
		    return f;
        }

        return ASin(f);
    }

    UGE_INLINE Float ACosSafe(Float f)
    {
        if (Abs(f) >= 1.f)
        {
            f = (f > 0) ? 0 : M_PI;
            return f;
        }

        return ACos(f);
    }

    UGE_INLINE Float Atan(Float f)
    {
        return ::atan(f);
    }

    UGE_INLINE Float Atan2(Float y, Float x)
    {
        return ::atan2(y, x);
    }

    UGE_INLINE Float Tan(Float f)
    {
        return ::tan(f);
    }
    
    UGE_INLINE Float Ceil(Float f)
    {
        return ::ceil(f);
    }

    UGE_INLINE Float Cos(Float f)
    {
        return ::cos(f);
    }

    UGE_INLINE Float Sin(Float f)
    {
        return ::sin(f);
    }

    UGE_INLINE Float Sqrt(const Float f)
    {
        return ::sqrtf(f);
    }

    UGE_INLINE Float Rsqrt(const Float f)
    {
        return 1.0f / ::sqrtf(f);
    }

    UGE_INLINE Float Floor(Float f)
    {
        return ::floor(f);
    }

    UGE_INLINE Float Round(Float f)
    {
        return ::floor(f + 0.5f);
    }

    #define LT(n) n, n, n, n, n, n, n, n, n, n, n, n, n, n, n, n

    UGE_INLINE Int32 Log2(Int32 val)
    {
        static const Byte log2Table[256] = 
        {
            0, 1, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4,
            LT(5), LT(6), LT(6), LT(7), LT(7), LT(7), LT(7),
            LT(8), LT(8), LT(8), LT(8), LT(8), LT(8), LT(8), LT(8)
        };
        Int32 l = -1;
        while (val >= 256)
        {
            l += 8;
            val >>= 8;
        }
        return l + log2Table[val];
    }

    UGE_INLINE constexpr Float DegToRad(const Float &value)
    {
        return value * (M_PI / 180.0f);
    }

    UGE_INLINE constexpr Float RadToDeg(const Float &value)
    {
        return value * (180.0f / M_PI);
    }

    UGE_INLINE constexpr Float DegToRad_Half(const Float &value)
    {
        return value * (M_PI / 360.0f);
    }

    UGE_INLINE Int32 Pow(Int32 base, Int32 exponent)
    {
        Int32 result = 1;

        while (exponent > 0)
        {
            if (exponent & 1)
            {
                result *= base;
            }

            exponent >>= 1;
            base *= base;
        }

        return result;
    }

    UGE_INLINE UInt32 Pow(UInt32 base, UInt32 exponent)
    {
        UInt32 result = 1;

        while (exponent > 0)
        {
            if (exponent & 1)
            {
                result *= base;
            }

            exponent >>= 1;
            base *= base;
        }

        return result;
    }

    UGE_INLINE Float Pow(Float base, Float exponent)
    {
        return ::powf(base, exponent);
    }
}

#endif
