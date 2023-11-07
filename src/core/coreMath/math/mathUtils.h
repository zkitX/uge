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

        template <typename T>
    UGE_INLINE constexpr T Acos(const T &value)
    {
        T sum = 0;
        T term = 1;
        T xSquare = value * value;
        T tempValue = value;
        int n = 0;

        while (true)
        {
            term = term * tempValue;
            T y = term / (2 * n + 1);
            if (y < 0.00001)
                break;
            if (n % 2 == 0)
                sum += y;
            else
                sum -= y;
            tempValue = tempValue * xSquare;
            n++;
        }

        return (M_PI / 2) - sum;
    }

    template <typename T>
    UGE_INLINE constexpr T Cos(const T &value)
    {
        T sum = 1;
        T term = 1;
        T xSquare = value * value;
        int n = 1;

        while (true)
        {
            term *= xSquare / ((2 * n - 1) * (2 * n));
            if (term < 0.00001)
                break;
            if (n % 2 == 0)
                sum += term;
            else
                sum -= term;
            n++;
        }

        return sum;
    }

    template <typename T>
    UGE_INLINE constexpr T Sin(const T& value)
    {
        T sum = value;
        T term = value;
        T xSquare = value * value;
        int n = 1;

        while (true)
        {
            term *= -xSquare / ((2 * n) * (2 * n + 1));
            if (math::Abs(term) < 0.00001) break;
            sum += term;
            n++;
        }

        return sum;
    }

    template <typename T>
    UGE_INLINE constexpr T Sqrt(const T &value)
    {
        T x = value;
        T y = 1;
        T e = 0.000001;

        while (x - y > e)
        {
            x = (x + y) / 2;
            y = value / x;
        }

        return x;
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

    UGE_INLINE Float Pow(Float base, UInt32 exponent)
    {
        Float result = 1.0f;

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
}

#endif
