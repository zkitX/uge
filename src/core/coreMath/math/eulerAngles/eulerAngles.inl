#ifndef __COREMATH_MATH_EULERANGLES_INL__
#define __COREMATH_MATH_EULERANGLES_INL__

namespace uge::math
{
    UGE_INLINE EulerAngles::EulerAngles(const Vec3 &v)
        : Roll(v.x)
        , Pitch(v.y)
        , Yaw(v.z)
    {
    }

    UGE_INLINE EulerAngles::EulerAngles(const Float f[3])
        : Roll(f[0])
        , Pitch(f[1])
        , Yaw(f[2])
    {
    }

    UGE_INLINE EulerAngles::EulerAngles(const Float Roll, const Float Pitch, const Float Yaw)
        : Roll(Roll)
        , Pitch(Pitch)
        , Yaw(Yaw)
    {
    }

    UGE_INLINE EulerAngles::EulerAngles(const EulerAngles &other)
        : Roll(other.Roll)
        , Pitch(other.Pitch)
        , Yaw(other.Yaw)
    {
    }

    UGE_INLINE EulerAngles &EulerAngles::operator=(const EulerAngles &other)
    {
        Roll = other.Roll;
        Pitch = other.Pitch;
        Yaw = other.Yaw;
        return *this;
    }

    UGE_INLINE void EulerAngles::Set(Float Roll, Float Pitch, Float Yaw)
    {
        this->Roll = Roll;
        this->Pitch = Pitch;
        this->Yaw = Yaw;
    }

    UGE_INLINE EulerAngles EulerAngles::operator-() const
    {
        return EulerAngles(-Roll, -Pitch, -Yaw);
    }

    UGE_INLINE EulerAngles EulerAngles::operator+(const EulerAngles &other) const
    {
        return EulerAngles(Roll + other.Roll, Pitch + other.Pitch, Yaw + other.Yaw);
    }

    UGE_INLINE EulerAngles EulerAngles::operator-(const EulerAngles &other) const
    {
        return EulerAngles(Roll - other.Roll, Pitch - other.Pitch, Yaw - other.Yaw);
    }

    UGE_INLINE EulerAngles EulerAngles::operator*(const EulerAngles &other) const
    {
        return EulerAngles(Roll * other.Roll, Pitch * other.Pitch, Yaw * other.Yaw);
    }

    UGE_INLINE EulerAngles EulerAngles::operator/(const EulerAngles &other) const
    {
        return EulerAngles(Roll / other.Roll, Pitch / other.Pitch, Yaw / other.Yaw);
    }

    UGE_INLINE EulerAngles &EulerAngles::operator+=(const EulerAngles &other)
    {
        Roll += other.Roll;
        Pitch += other.Pitch;
        Yaw += other.Yaw;
        return *this;
    }

    UGE_INLINE EulerAngles &EulerAngles::operator-=(const EulerAngles &other)
    {
        Roll -= other.Roll;
        Pitch -= other.Pitch;
        Yaw -= other.Yaw;
        return *this;
    }

    UGE_INLINE EulerAngles &EulerAngles::operator*=(const EulerAngles &other)
    {
        Roll *= other.Roll;
        Pitch *= other.Pitch;
        Yaw *= other.Yaw;
        return *this;
    }

    UGE_INLINE EulerAngles &EulerAngles::operator/=(const EulerAngles &other)
    {
        Roll /= other.Roll;
        Pitch /= other.Pitch;
        Yaw /= other.Yaw;
        return *this;
    }

    UGE_INLINE EulerAngles EulerAngles::operator+(Float scalar) const
    {
        return EulerAngles(Roll + scalar, Pitch + scalar, Yaw + scalar);
    }

    UGE_INLINE EulerAngles EulerAngles::operator-(Float scalar) const
    {
        return EulerAngles(Roll - scalar, Pitch - scalar, Yaw - scalar);
    }

    UGE_INLINE EulerAngles EulerAngles::operator*(Float scalar) const
    {
        return EulerAngles(Roll * scalar, Pitch * scalar, Yaw * scalar);
    }

    UGE_INLINE EulerAngles EulerAngles::operator/(Float scalar) const
    {
        return EulerAngles(Roll / scalar, Pitch / scalar, Yaw / scalar);
    }

    UGE_INLINE EulerAngles &EulerAngles::operator+=(Float scalar)
    {
        Roll += scalar;
        Pitch += scalar;
        Yaw += scalar;
        return *this;
    }

    UGE_INLINE EulerAngles &EulerAngles::operator-=(Float scalar)
    {
        Roll -= scalar;
        Pitch -= scalar;
        Yaw -= scalar;
        return *this;
    }

    UGE_INLINE EulerAngles &EulerAngles::operator*=(Float scalar)
    {
        Roll *= scalar;
        Pitch *= scalar;
        Yaw *= scalar;
        return *this;
    }

    UGE_INLINE EulerAngles &EulerAngles::operator/=(Float scalar)
    {
        Roll /= scalar;
        Pitch /= scalar;
        Yaw /= scalar;
        return *this;
    }

    UGE_INLINE Bool EulerAngles::operator==(const EulerAngles &other) const
    {
        return (Roll == other.Roll) && (Pitch == other.Pitch) && (Yaw == other.Yaw);
    }

    UGE_INLINE Bool EulerAngles::operator!=(const EulerAngles &other) const
    {
        return (Roll != other.Roll) || (Pitch != other.Pitch) || (Yaw != other.Yaw);
    }

    EulerAngles &EulerAngles::Normalize()
    {
        Roll = NormalizeAngle(Roll);
        Pitch = NormalizeAngle(Pitch);
        Yaw = NormalizeAngle(Yaw);
        return *this;
    }

    UGE_INLINE Float EulerAngles::NormalizeAngle(Float angle)
    {
        Int32 i = static_cast<Int32>(angle / 360.0f);
        if ( i != 0 )
            angle -= i * 360.0f;
        if ( angle < 0.0f )
            angle += 360.0f;
        return angle;
    }

    UGE_INLINE Float EulerAngles::NormalizeAngle180(Float angle)
    {
        angle = NormalizeAngle(angle);
        return (angle > 180.0f) ? (angle - 360.0f) : angle;
    }

    UGE_INLINE Float EulerAngles::YawFromXY(const Float x, const Float y)
    {
        return atan2f(y, x) * 180.0f / M_PI;
    }

    UGE_INLINE Double EulerAngles::YawFromXY(const Double x, const Double y)
    {
        return atan2(y, x) * 180.0 / M_PI;
    }

    UGE_INLINE Vec4 EulerAngles::YawToVector(const Float yaw)
    {
        Float rad = yaw * M_PI / 180.0f;
        return Vec4(Cos(rad), Sin(rad), 0.0f, 0.0f);
    }

    UGE_INLINE Vec2 EulerAngles::YawToVector2(const Float yaw)
    {
        Float rad = yaw * M_PI / 180.0f;
        return Vec2(Cos(rad), Sin(rad));
    }

    UGE_INLINE Float EulerAngles::AngleDistance(const Float a, const Float b)
    {
        Float d = NormalizeAngle(b) - NormalizeAngle(a);
        if ( d > 180.0f )
            d -= 360.0f;
        else if ( d < -180.0f )
            d += 360.0f;
        return d;
    }

    UGE_INLINE EulerAngles EulerAngles::AngleDistance(const EulerAngles &a, const EulerAngles &b)
    {
        return EulerAngles(AngleDistance(a.Roll, b.Roll), AngleDistance(a.Pitch, b.Pitch), AngleDistance(a.Yaw, b.Yaw));
    }

    UGE_INLINE Float EulerAngles::Interpolate(const Float a, const Float b, const Float t)
    {
		const Float diff = AngleDistance( a, b );
		return a + diff * t;
    }

    UGE_INLINE EulerAngles EulerAngles::Interpolate(const EulerAngles &a, const EulerAngles &b, const Float t)
    {
        return EulerAngles(Interpolate(a.Roll, b.Roll, t), Interpolate(a.Pitch, b.Pitch, t), Interpolate(a.Yaw, b.Yaw, t));
    }

    UGE_INLINE void EulerAngles::Interpolate(const EulerAngles &a, const Float t)
    {
        *this += AngleDistance(*this, a) * t;
    }
}

#endif  // __COREMATH_MATH_EULERANGLES_INL__