#ifndef __COREMATH_MATH_VECTOR2_H__
#define __COREMATH_MATH_VECTOR2_H__

namespace uge::math
{
    struct Vec2
    {
        union
        {
            struct
            {
                Float x, y;
            };
            Float v[2];
        };

        Vec2();
        Vec2( Float x, Float y );
        Vec2( const Vec2& other );

        Vec2& operator=( const Vec2& other );

        void Set( Float x, Float y );

        Vec2 operator+( const Vec2& other ) const;
        Vec2 operator-( const Vec2& other ) const;
        Vec2 operator*( const Vec2& other ) const;
        Vec2 operator/( const Vec2& other ) const;

        Vec2& operator+=( const Vec2& other );
        Vec2& operator-=( const Vec2& other );
        Vec2& operator*=( const Vec2& other );
        Vec2& operator/=( const Vec2& other );

        Vec2 operator+( Float scalar ) const;
        Vec2 operator-( Float scalar ) const;
        Vec2 operator*( Float scalar ) const;
        Vec2 operator/( Float scalar ) const;

        Vec2& operator+=( Float scalar );
        Vec2& operator-=( Float scalar );
        Vec2& operator*=( Float scalar );
        Vec2& operator/=( Float scalar );

        Bool operator==( const Vec2& other ) const;
        Bool operator!=( const Vec2& other ) const;

        Float& operator[]( UInt32 index );
        const Float& operator[]( UInt32 index ) const;

        Float Length() const;
        Float LengthSquared() const;
        Float Dot( const Vec2& other ) const;
        Float Magnitude() const;
        Float MagnitudeSquared() const;
        Vec2 Normalize() const;
        Vec2 Reflect( const Vec2& normal ) const;
        Vec2 Refract( const Vec2& normal, Float eta ) const;
        Vec2 Project( const Vec2& other ) const;
        Vec2 ProjectPerp( const Vec2& other ) const;
        Vec2 Lerp( const Vec2& other, Float t ) const;
        Vec2 Slerp( const Vec2& other, Float t ) const;
        Vec2 Nlerp( const Vec2& other, Float t ) const;
        Vec2 Rotate( Float angle ) const;
        Vec2 Rotate( const Vec2& axis, const Vec2& pivot, Float angle ) const;
        Vec2 Rotate( const Vec2& axis, Float angle ) const;
        Vec2 Rotate( const Vec2& axis, const Vec2& pivot, Float angle, Float scale ) const;
    };
}

#endif // __COREMATH_MATH_VECTOR2_H__