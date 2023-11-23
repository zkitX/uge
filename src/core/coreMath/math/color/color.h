#ifndef __COREMATH_COLOR_H__
#define __COREMATH_COLOR_H__

namespace uge::math
{
    struct Color
    {
        union 
        {
            struct
            {
                UByte r;
                UByte g;
                UByte b;
                UByte a;
            };
            UByte rgba[4];
        };

        Color() = default;
        Color(UByte r, UByte g, UByte b, UByte a = 255);

        // HDR Color
        Color(const Vec4& color);
        Color(const Float f[4]);

        explicit Color(UInt32 color);

        Bool operator==(const Color& other) const { return r == other.r && g == other.g && b == other.b && a == other.a; };
        Bool operator!=(const Color& other) const { return r != other.r || g != other.g || b != other.b || a != other.a; };

        Vec4 ToVector() const;
        Vec4 ToVectorLinearAccu() const;
        Half4 ToHalfLinearAccu() const;
        UInt32 ToUInt32() const;
        Color FullAlpha() const;

        static Color FromVectorLinear(const Vec4& color);
        static Color FromVectorLinearAccu(const Vec4& color);

        static Color Mul3(const Color& c1, Float f);
        static Color Mul4(const Color& c1, Float f);

        void Mul3(Float f);
        void Mul4(Float f);

        static Color Lerp(const Color& c1, const Color& c2, Float t);

        Color operator+(const Color& c) const;
        Color operator*(Float f) const;
    };
}

#define COLOR_RGBA(r, g, b, a) uge::math::Color(r, g, b, a)
#define COLOR_RGB(r, g, b) uge::math::Color(r, g, b)

namespace uge::math::Colors
{
    static Color const Transparent = COLOR_RGBA(0, 0, 0, 0);
    static Color const White = COLOR_RGBA(255, 255, 255, 255);
    static Color const Black = COLOR_RGBA(0, 0, 0, 255);
    static Color const Red = COLOR_RGBA(255, 0, 0, 255);
    static Color const Green = COLOR_RGBA(0, 255, 0, 255);
    static Color const Blue = COLOR_RGBA(0, 0, 255, 255);
    static Color const Yellow = COLOR_RGBA(255, 255, 0, 255);
    static Color const Cyan = COLOR_RGBA(0, 255, 255, 255);
    static Color const Magenta = COLOR_RGBA(255, 0, 255, 255);
    static Color const Orange = COLOR_RGBA(255, 128, 0, 255);
    static Color const Purple = COLOR_RGBA(128, 0, 255, 255);
    static Color const Pink = COLOR_RGBA(255, 0, 128, 255);
    static Color const Brown = COLOR_RGBA(128, 64, 0, 255);
    static Color const Grey = COLOR_RGBA(128, 128, 128, 255);

    // Lights
    static Color const LightGrey = COLOR_RGBA(192, 192, 192, 255);
    static Color const LightRed = COLOR_RGBA(255, 128, 128, 255);
    static Color const LightGreen = COLOR_RGBA(128, 255, 128, 255);
    static Color const LightBlue = COLOR_RGBA(128, 128, 255, 255);
    static Color const LightYellow = COLOR_RGBA(255, 255, 128, 255);
    static Color const LightCyan = COLOR_RGBA(128, 255, 255, 255);
    static Color const LightMagenta = COLOR_RGBA(255, 128, 255, 255);
    static Color const LightOrange = COLOR_RGBA(255, 192, 128, 255);
    static Color const LightPurple = COLOR_RGBA(192, 128, 255, 255);
    static Color const LightPink = COLOR_RGBA(255, 128, 192, 255);
    static Color const LightBrown = COLOR_RGBA(192, 128, 64, 255);

    // Darks
    static Color const DarkGrey = COLOR_RGBA(64, 64, 64, 255);
    static Color const DarkRed = COLOR_RGBA(128, 0, 0, 255);
    static Color const DarkGreen = COLOR_RGBA(0, 128, 0, 255);
    static Color const DarkBlue = COLOR_RGBA(0, 0, 128, 255);
    static Color const DarkYellow = COLOR_RGBA(128, 128, 0, 255);
    static Color const DarkCyan = COLOR_RGBA(0, 128, 128, 255);
    static Color const DarkMagenta = COLOR_RGBA(128, 0, 128, 255);
    static Color const DarkOrange = COLOR_RGBA(128, 64, 0, 255);
    static Color const DarkPurple = COLOR_RGBA(64, 0, 128, 255);
    static Color const DarkPink = COLOR_RGBA(128, 0, 64, 255);
    static Color const DarkBrown = COLOR_RGBA(64, 0, 0, 255);
}

#include "color.inl"

#endif // __COREMATH_COLOR_H__