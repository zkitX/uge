#ifndef __COREMATH_MATH_UTILS_H__
#define __COREMATH_MATH_UTILS_H__

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
            if (Abs(term) < 0.00001) break;
            sum += term;
            n++;
        }

        return sum;
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
