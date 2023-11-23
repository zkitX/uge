#ifndef __COREMATH_COLOR_INL__
#define __COREMATH_COLOR_INL__

namespace uge::math
{
    struct GammaToLinearLUT
    {
        static constexpr UInt32 LUTSize = 256;
        static constexpr Float Gamma = 2.2f;
        static constexpr Float InvGamma = 1.0f / Gamma;

        Float LUT[LUTSize];
        Half LUTHalf[LUTSize];

        GammaToLinearLUT();
    };

    UGE_INLINE Float ToLinearAccu(Float sRGBCol)
    {
        const Float linearRGBLo = sRGBCol / 12.92f;
        const Float linearRGBHi = powf((sRGBCol + 0.055f) / 1.055f, 2.4f);
        const Float linearRGB = (sRGBCol <= 0.04045f) ? linearRGBLo : linearRGBHi;
        return linearRGB;
    }

    UGE_INLINE Float ToLinear(Float gammaRGB)
    {
        return powf(gammaRGB, 1.0f / 2.2f);
    }

    UGE_INLINE Vec3 ToLinear(const Vec3& gammaRGB)
    {
        return Vec3(ToLinear(gammaRGB.x), ToLinear(gammaRGB.y), ToLinear(gammaRGB.z));
    }

    UGE_INLINE Vec4 ToLinear(const Vec4& gammaRGB)
    {
        return Vec4(ToLinear(gammaRGB.x), ToLinear(gammaRGB.y), ToLinear(gammaRGB.z), ToLinear(gammaRGB.w));
    }

    UGE_INLINE Float ToGammaAccu(Float linearRGB)
    {
        const Float sRGBColLo = linearRGB * 12.92f;
        const Float sRGBColHi = powf(linearRGB, 1.0f / 2.4f) * 1.055f - 0.055f;
        const Float sRGBCol = (linearRGB <= 0.0031308f) ? sRGBColLo : sRGBColHi;
        return sRGBCol;
    }

    UGE_INLINE Float ToGamma(Float linearRGB)
    {
        return powf(linearRGB, 2.2f);
    }

    UGE_INLINE Vec3 ToGamma(const Vec3& linearRGB)
    {
        return Vec3(ToGamma(linearRGB.x), ToGamma(linearRGB.y), ToGamma(linearRGB.z));
    }

    UGE_INLINE Vec4 ToGamma(const Vec4& linearRGB)
    {
        return Vec4(ToGamma(linearRGB.x), ToGamma(linearRGB.y), ToGamma(linearRGB.z), ToGamma(linearRGB.w));
    }

    COREMATH_API extern const GammaToLinearLUT g_gammaToLinearLUT;

    UGE_INLINE Color::Color(UByte r, UByte g, UByte b, UByte a)
        : r(r), g(g), b(b), a(a)
    {
    }

    UGE_INLINE Color::Color(UInt32 color)
    {
        rgba[0] = (color >> 24) & 0xFF;
        rgba[1] = (color >> 16) & 0xFF;
        rgba[2] = (color >> 8) & 0xFF;
        rgba[3] = color & 0xFF;
    }

    UGE_INLINE Color::Color(const Vec4& color)
    {
        r = math::Clamp(color.x * 255.0f, 0.0f, 255.0f);
        g = math::Clamp(color.y * 255.0f, 0.0f, 255.0f);
        b = math::Clamp(color.z * 255.0f, 0.0f, 255.0f);
        a = math::Clamp(color.w * 255.0f, 0.0f, 255.0f);
    }

    UGE_INLINE Color::Color(const Float f[4])
    {
        r = math::Clamp(f[0] * 255.0f, 0.0f, 255.0f);
        g = math::Clamp(f[1] * 255.0f, 0.0f, 255.0f);
        b = math::Clamp(f[2] * 255.0f, 0.0f, 255.0f);
        a = math::Clamp(f[3] * 255.0f, 0.0f, 255.0f);
    }

    UGE_INLINE Vec4 Color::ToVector() const
    {
        return Vec4(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f);
    }

    UGE_INLINE Vec4 Color::ToVectorLinearAccu() const
    {
        return Vec4(g_gammaToLinearLUT.LUT[r], g_gammaToLinearLUT.LUT[g], g_gammaToLinearLUT.LUT[b], a / 255.0f);
    }

    UGE_INLINE Half4 Color::ToHalfLinearAccu() const
    {
        return Half4(g_gammaToLinearLUT.LUTHalf[r], g_gammaToLinearLUT.LUTHalf[g], g_gammaToLinearLUT.LUTHalf[b], Half(a / 255.0f));
    }

    UGE_INLINE UInt32 Color::ToUInt32() const
    {
        return (r << 24) | (g << 16) | (b << 8) | a;
    }

    UGE_INLINE Color Color::FullAlpha() const
    {
        return Color(r, g, b, 255);
    }

    UGE_INLINE Color Color::FromVectorLinear(const Vec4& color)
    {
        return Color(
            (UByte)math::Clamp(ToGamma(color.x) * 255.0f, 0.0f, 255.0f),
            (UByte)math::Clamp(ToGamma(color.y) * 255.0f, 0.0f, 255.0f),
            (UByte)math::Clamp(ToGamma(color.z) * 255.0f, 0.0f, 255.0f),
            (UByte)math::Clamp(color.w * 255.0f, 0.0f, 255.0f)
        );
    }

    UGE_INLINE Color Color::FromVectorLinearAccu(const Vec4& color)
    {
        return Color(
            (UByte)math::Clamp(ToGammaAccu(color.x) * 255.0f, 0.0f, 255.0f),
            (UByte)math::Clamp(ToGammaAccu(color.y) * 255.0f, 0.0f, 255.0f),
            (UByte)math::Clamp(ToGammaAccu(color.z) * 255.0f, 0.0f, 255.0f),
            (UByte)math::Clamp(color.w * 255.0f, 0.0f, 255.0f)
        );
    }

    UGE_INLINE Color Color::Mul3(const Color& c1, Float f)
    {
        UGE_ASSERT(f >= 0.0f && f <= 1.0f, "Color::Mul3: f must be in range [0, 1]");

        return Color(
            (UByte)math::Clamp(c1.r * f, 0.0f, 255.0f),
            (UByte)math::Clamp(c1.g * f, 0.0f, 255.0f),
            (UByte)math::Clamp(c1.b * f, 0.0f, 255.0f),
            c1.a
        );
    }

    UGE_INLINE Color Color::Mul4(const Color& c1, Float f)
    {
        UGE_ASSERT(f >= 0.0f && f <= 1.0f, "Color::Mul4: f must be in range [0, 1]");

        return Color(
            (UByte)math::Clamp(c1.r * f, 0.0f, 255.0f),
            (UByte)math::Clamp(c1.g * f, 0.0f, 255.0f),
            (UByte)math::Clamp(c1.b * f, 0.0f, 255.0f),
            (UByte)math::Clamp(c1.a * f, 0.0f, 255.0f)
        );
    }

    UGE_INLINE void Color::Mul3(Float f)
    {
        UGE_ASSERT(f >= 0.0f && f <= 1.0f, "Color::Mul3: f must be in range [0, 1]");

        r = (UByte)math::Clamp(r * f, 0.0f, 255.0f);
        g = (UByte)math::Clamp(g * f, 0.0f, 255.0f);
        b = (UByte)math::Clamp(b * f, 0.0f, 255.0f);
    }

    UGE_INLINE void Color::Mul4(Float f)
    {
        UGE_ASSERT(f >= 0.0f && f <= 1.0f, "Color::Mul4: f must be in range [0, 1]");

        r = (UByte)math::Clamp(r * f, 0.0f, 255.0f);
        g = (UByte)math::Clamp(g * f, 0.0f, 255.0f);
        b = (UByte)math::Clamp(b * f, 0.0f, 255.0f);
        a = (UByte)math::Clamp(a * f, 0.0f, 255.0f);
    }

    UGE_INLINE Color Color::Lerp(const Color& c1, const Color& c2, Float t)
    {
        UGE_ASSERT(t >= 0.0f && t <= 1.0f, "Color::Lerp: t must be in range [0, 1]");
        const Float invT = 1.0f - t;

        return Color(
            (UByte)math::Clamp(c1.r * invT + c2.r * t, 0.0f, 255.0f),
            (UByte)math::Clamp(c1.g * invT + c2.g * t, 0.0f, 255.0f),
            (UByte)math::Clamp(c1.b * invT + c2.b * t, 0.0f, 255.0f),
            (UByte)math::Clamp(c1.a * invT + c2.a * t, 0.0f, 255.0f)
        );
    }
    
    UGE_INLINE Color Color::operator+(const Color& c) const
    {
        Color result = *this;

        result.r = math::Clamp<UByte>(result.r + c.r, 0.0f, 255.0f);
        result.g = math::Clamp<UByte>(result.g + c.g, 0.0f, 255.0f);
        result.b = math::Clamp<UByte>(result.b + c.b, 0.0f, 255.0f);
        result.a = math::Clamp<UByte>(result.a + c.a, 0.0f, 255.0f);

        return result;
    }

    UGE_INLINE Color Color::operator*(Float f) const
    {
        Color result = *this;
        result.Mul4(f);
        return result;
    }
}

#endif // __COREMATH_COLOR_INL__