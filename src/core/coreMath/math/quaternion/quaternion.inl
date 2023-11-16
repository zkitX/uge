#ifndef __COREMATH_MATH_QUATERNION_INL__
#define __COREMATH_MATH_QUATERNION_INL__

namespace uge::math
{
    UGE_FORCE_INLINE Quaternion::Quaternion()
        : i( 0.0f ), j( 0.0f ), k( 0.0f ), r( 1.0f )
    {
    }

    UGE_FORCE_INLINE Quaternion::Quaternion( const Float i, const Float j, const Float k, const Float r )
        : i( i ), j( j ), k( k ), r( r )
    {
    }

    UGE_FORCE_INLINE Quaternion::Quaternion( const Float f[4] )
        : i( f[0] ), j( f[1] ), k( f[2] ), r( f[3] )
    {
    }

    UGE_FORCE_INLINE Quaternion::Quaternion( const Quaternion& q )
        : i( q.i ), j( q.j ), k( q.k ), r( q.r )
    {
    }

    UGE_FORCE_INLINE Quaternion::Quaternion( const Vec4& v )
        : i( v.x ), j( v.y ), k( v.z ), r( v.w )
    {
    }

    UGE_FORCE_INLINE Quaternion::Quaternion(const Float yaw, const Float pitch, const Float roll)
    {
        const Float halfYaw = yaw * 0.5f;
        const Float halfPitch = pitch * 0.5f;
        const Float halfRoll = roll * 0.5f;

        const Float cosYaw = Cos( halfYaw );
		const Float cosPitch = Cos( halfPitch );
		const Float cosRoll = Cos( halfRoll );
		const Float sinYaw = Sin( halfYaw );
		const Float sinPitch = Sin( halfPitch );
		const Float sinRoll = Sin( halfRoll );

		r = cosYaw * cosPitch * cosRoll - sinYaw * sinPitch * sinRoll;
		i = cosYaw * sinPitch * cosRoll - sinYaw * cosPitch * sinRoll;
		j = sinYaw * sinPitch * cosRoll + cosYaw * cosPitch * sinRoll;
		k = sinYaw * cosPitch * cosRoll + cosYaw * sinPitch * sinRoll;
    }

    UGE_FORCE_INLINE Quaternion::Quaternion(const Vec4& axis, const Float angle)
    {
        SetAxisAngle(axis, angle);
    }

    UGE_FORCE_INLINE Quaternion::Quaternion(const Vec3& axis, const Float angle)
    {
        SetAxisAngle(axis, angle);
    }

    UGE_FORCE_INLINE Quaternion& Quaternion::operator=( const Quaternion& q )
    {
        vec = q.vec;
        return *this;
    }

        UGE_FORCE_INLINE Quaternion Quaternion::operator+( const Quaternion& q ) const
    {
        return Quaternion( vec + q.vec );
    }

    UGE_FORCE_INLINE Quaternion Quaternion::operator-( const Quaternion& q ) const
    {
        return Quaternion( vec - q.vec );
    }

    UGE_INLINE Quaternion Quaternion::operator*( const Quaternion& q ) const
    {
        return Quaternion(
            r * q.r - i * q.i - j * q.j - k * q.k,
            r * q.i + i * q.r + j * q.k - k * q.j,
            r * q.j - i * q.k + j * q.r + k * q.i,
            r * q.k + i * q.j - j * q.i + k * q.r
        );
    }

    UGE_FORCE_INLINE Quaternion Quaternion::operator*( const Float f ) const
    {
        return Quaternion( vec * f );
    }

    UGE_FORCE_INLINE Quaternion Quaternion::operator/( const Quaternion& q ) const
    {
        return Quaternion( vec / q.vec );
    }

    UGE_FORCE_INLINE Quaternion Quaternion::operator/( const Float f ) const
    {
        return Quaternion( vec / f );
    }

    UGE_INLINE Quaternion& Quaternion::operator+=( const Quaternion& q )
    {
        *this = *this + q;
        return *this;
    }

    UGE_INLINE Quaternion& Quaternion::operator-=( const Quaternion& q )
    {
        *this = *this - q;
        return *this;
    }

    UGE_INLINE Quaternion& Quaternion::operator*=( const Quaternion& q )
    {
        *this = *this * q;
        return *this;
    }

    UGE_INLINE Quaternion& Quaternion::operator/=( const Quaternion& q )
    {
        *this = *this / q;
        return *this;
    }

    UGE_INLINE Quaternion& Quaternion::operator*=( const Float f )
    {
        *this = *this * f;
        return *this;
    }

    UGE_INLINE Quaternion& Quaternion::operator/=( const Float f )
    {
        *this = *this / f;
        return *this;
    }

    UGE_INLINE Bool Quaternion::operator==( const Quaternion& q ) const
    {
        return r == q.r && i == q.i && j == q.j && k == q.k;
    }

    UGE_INLINE Bool Quaternion::operator!=( const Quaternion& q ) const
    {
        return r != q.r || i != q.i || j != q.j || k != q.k;
    }

    UGE_FORCE_INLINE Vec3 Quaternion::operator*( const Vec3& v ) const
    {
        return Transform(v);
    }

    UGE_FORCE_INLINE Vec4 Quaternion::operator*( const Vec4& v ) const
    {
        return Transform(v);
    }

    UGE_FORCE_INLINE Quaternion Quaternion::Identity()
    {
        return { 0.0f, 0.0f, 0.0f, 1.0f };
    }

    UGE_FORCE_INLINE Quaternion Quaternion::I()
    {
        return { 1.0f, 0.0f, 0.0f, 0.0f };
    }

    UGE_FORCE_INLINE Quaternion Quaternion::J()
    {
        return { 0.0f, 1.0f, 0.0f, 0.0f };
    }

    UGE_FORCE_INLINE Quaternion Quaternion::K()
    {
        return { 0.0f, 0.0f, 1.0f, 0.0f };
    }

    UGE_FORCE_INLINE void Quaternion::SetIdentity()
    {
        vec = { 0.0f, 0.0f, 0.0f, 1.0f };
    }

    UGE_FORCE_INLINE void Quaternion::SetZero()
    {
        vec.SetZero();
    }

    UGE_FORCE_INLINE void Quaternion::SetInverse()
    {
        *this = Conjugate() / MagnitudeSquared();
    }

    UGE_FORCE_INLINE void Quaternion::SetNegate()
    {
        vec = -vec;
    }

    UGE_FORCE_INLINE void Quaternion::SetConjugate()
    {
        *this = Conjugate();
    }

    UGE_INLINE void Quaternion::SetAxisAngle(const Vec4& axis, const Float angle)
    {
        const Float halfAngle = angle * 0.5f;
        const Float sinHalfAngle = Sin( halfAngle );

        r = Cos( halfAngle );
        i = axis.x * sinHalfAngle;
        j = axis.y * sinHalfAngle;
        k = axis.z * sinHalfAngle;
    }

    UGE_INLINE void Quaternion::SetAxisAngle(const Vec3& axis, const Float angle)
    {
        const Float halfAngle = angle * 0.5f;
        const Float sinHalfAngle = Sin( halfAngle );

        r = Cos( halfAngle );
        i = axis.x * sinHalfAngle;
        j = axis.y * sinHalfAngle;
        k = axis.z * sinHalfAngle;
    }

    UGE_INLINE void Quaternion::SetXRotation(const Float angle)
    {
        const Float halfAngle = angle * 0.5f;
        const Float sinHalfAngle = Sin( halfAngle );
        
        i = sinHalfAngle;
        j = 0.0f;
        k = 0.0f;
        r = Cos( halfAngle );
    }

    UGE_INLINE void Quaternion::SetYRotation(const Float angle)
    {
        const Float halfAngle = angle * 0.5f;
        const Float sinHalfAngle = Sin( halfAngle );
        
        i = 0.0f;
        j = sinHalfAngle;
        k = 0.0f;
        r = Cos( halfAngle );
    }

    UGE_INLINE void Quaternion::SetZRotation(const Float angle)
    {
        const Float halfAngle = angle * 0.5f;
        const Float sinHalfAngle = Sin( halfAngle );
        
        i = 0.0f;
        j = 0.0f;
        k = sinHalfAngle;
        r = Cos( halfAngle );
    }

    UGE_FORCE_INLINE Float Quaternion::Magnitude() const
    {
        return Sqrt(vec.MagnitudeSquared(DotProduct4D));
    }

    UGE_FORCE_INLINE Float Quaternion::MagnitudeSquared() const
    {
        return vec.MagnitudeSquared(DotProduct4D);
    }

    UGE_FORCE_INLINE Quaternion Quaternion::Conjugate() const
    {
        return { -i, -j, -k, r };
    }

    UGE_INLINE Quaternion Quaternion::Inverse() const
    {
        const Float magnitudeSq = MagnitudeSquared();
        const Float magSqInv = (magnitudeSq > FLT_EPSILON) ? 1.0f / magnitudeSq : 0.0f;
        return Conjugate() * magSqInv;
    }

    UGE_INLINE Quaternion Quaternion::Normalized() const
    {
        return Quaternion( vec.Normalize() );
    }

    UGE_INLINE void Quaternion::Normalize()
    {
        vec.Normalize(DotProduct4D);
    }

    UGE_INLINE Vec4 Quaternion::DoTransform(const Vec4& v) const
    {
        const Quaternion& q = *this;
        Vec4 t = Vec4::Cross(q.vec, v);
        t = t + t;
        return v + t * q.r + Vec4::Cross(q.vec, t);
    }

    UGE_FORCE_INLINE Vec3 Quaternion::DoTransform(const Vec3& v) const
    {
        return (DoTransform(Vec4(v))).ToVec3();
    }

    UGE_INLINE Vec4 Quaternion::Transform(const Vec4& v) const
    {
        const Quaternion q = Normalized();
        return Vec4(q.DoTransform(v), 0.f);
    }

    UGE_INLINE Vec3 Quaternion::Transform(const Vec3& v) const
    {
        const Quaternion q = Normalized();
        return q.DoTransform(v);
    }
    
    UGE_INLINE Vec4 Quaternion::TransformInverse(const Vec4& in) const
    {
        return Inverse().Transform(in);
    }

    UGE_INLINE Vec3 Quaternion::TransformInverse(const Vec3& in) const
    {
        return Inverse().Transform(in);
    }

    UGE_INLINE Vec4 Quaternion::TransformConjugate(const Vec4& in) const
    {
        return Conjugate().Transform(in);
    }

    UGE_INLINE Vec3 Quaternion::TransformConjugate(const Vec3& in) const
    {
        return Conjugate().Transform(in);
    }

    template<>
    UGE_INLINE Vec3 Quaternion::GetAxis( const EQuaternionAxis axis) const
    {
        const Quaternion& q = Normalized();
        switch (axis)
        {
            case EQuaternionAxis::EQuaternionAxis_X:
                return { 1.f - 2.f*q.j*q.j - 2.f*q.k*q.k, 2.f*q.i*q.j + 2.f*q.k*q.r, 2.f*q.i*q.k - 2.f*q.j*q.r };
            case EQuaternionAxis::EQuaternionAxis_Y:
                return { 2.f*q.i*q.j - 2.f*q.k*q.r, 1.f - 2.f*q.i*q.i - 2.f*q.k*q.k, 2.f * q.j * q.k + 2.f * q.i * q.r };
            case EQuaternionAxis::EQuaternionAxis_Z:
                return { 2.f * q.i * q.k + 2.f*q.j*q.r, 2.f*q.j*q.k - 2.f*q.i*q.r, 1.f - 2.f*q.i*q.i - 2.f*q.j*q.j };
            default:
                UGE_ASSERT(false, "Invalid quaternion axis");
                return Vec3::Zero;
        }
    }

    template<>
    UGE_INLINE Vec4 Quaternion::GetAxis( const EQuaternionAxis axis) const
    {
        return Vec4(GetAxis<Vec3>(axis), 0.f);
    }

    template<> 
    UGE_INLINE Vec3 Quaternion::GetDirection( const EQuaternionDirection direction ) const
    {
        switch (direction)
        {
            case EQuaternionDirection_Right:
                return GetAxis<Vec3>(EQuaternionAxis_X);
            case EQuaternionDirection::EQuaternionDirection_Forward:
                return GetAxis<Vec3>(EQuaternionAxis_Y);
            case EQuaternionDirection_Up:
                return GetAxis<Vec3>(EQuaternionAxis_Z);
            default:
                UGE_ASSERT(false, "Invalid quaternion direction");
                return Vec3::Zero;
        }
    }

    template<>
    UGE_INLINE Vec4 Quaternion::GetDirection( const EQuaternionDirection direction ) const
    {
        return Vec4(GetDirection<Vec3>(direction), 0.f);
    }

    template<>
    UGE_INLINE Vec3 Quaternion::GetAxis() const
    {
        Vec3 axis(i, j, k);
        axis.Normalize();

        if (r < 0.f)
        {
            axis *= -1.f;
        }

        return axis;
    }

    template<>
    UGE_INLINE Vec4 Quaternion::GetAxis() const
    {
        Vec4 axis(i, j, k, 0.f);

        axis.Normalize();

        if (r < 0.f)
        {
            axis *= -1.f;
        }

        return axis;
    }

    UGE_INLINE Float Quaternion::GetPitch() const
    {
        const Float y2 = j * j;
        const Float z2 = k * k;

        const Float unitLength = r*r + i*i + y2 + z2;
        const Float wxyz = r*i + j*k;
        const Float eps = 0.001;

        if (wxyz > (0.5f - eps) * unitLength)
        {
            return RadToDeg(M_PI_2);
        }
        else if (wxyz < (-0.5f + eps) * unitLength)
        {
            return RadToDeg(-M_PI_2);
        }
        else
        {
            return RadToDeg(ASin(2.f * (wxyz / unitLength)));
        }
    }

    UGE_INLINE Float Quaternion::GetYaw() const
    {
        const Float x2 = i*i;
		const Float z2 = k*k;

		const Float unitLength = r*r + x2 + j*j + z2; 
		const Float wxyz = r*i + j*k;
		const Float eps = 0.001f;

        if (wxyz > (0.5f - eps) * unitLength)
        {
            return RadToDeg(2.f * Atan2(j, r));
        }
        else if (wxyz < (-0.5f + eps) * unitLength)
        {
            return RadToDeg(-2.f * Atan2(j, r));
        }
        else
        {
            return RadToDeg(Atan2(2.f*(r*k-i*j), 1.f - 2.f*(z2+x2)));
        }
    }

    UGE_INLINE Float Quaternion::GetRoll() const
    {
        const Float x2 = i*i;
        const Float y2 = j*j;

        const Float unitLength = r*r + x2 + y2 + k*k;
        const Float wxyz = r*i + j*k;
        const Float eps = 0.001f;

		if (wxyz > (0.5f-eps)*unitLength || wxyz < (-0.5f+eps)*unitLength)
		{
			return 0.f;
		}
        else
        {
            return RadToDeg(Atan2(2.f*(r*j-k*i), 1.f - 2.f*(y2+x2)));
        }
    }

    UGE_INLINE Float Quaternion::GetAngle() const
    {
        return ACos(r) * 2.f;
    }

    UGE_INLINE Matrix Quaternion::ToMatrix() const
    {
        const Quaternion q = Normalized();
        Matrix m;

        m.SetRow(0, Vec4(q.GetAxis<Vec3>(EQuaternionAxis_X), 0.f));
        m.SetRow(1, Vec4(q.GetAxis<Vec3>(EQuaternionAxis_Y), 0.f));
        m.SetRow(2, Vec4(q.GetAxis<Vec3>(EQuaternionAxis_Z), 0.f));
        m.SetRow(3, Vec4::ZeroW());

        return m;
    }

    UGE_INLINE EulerAngles Quaternion::ToEulerAngles() const
    {
        const Float x2 = i*i;
        const Float y2 = j*j;
        const Float z2 = k*k;

        const Float unitLength = r*r + x2 + y2 + z2;
        const Float abcd = r*i + j*k;
        const Float eps = 0.001f;

        Float yaw, pitch, roll;

        if (abcd > (0.5f - eps) * unitLength)
        {
            yaw = RadToDeg(2.f * Atan2(j, r));
            pitch = RadToDeg(M_PI_2);
            roll = 0.f;
        }
        else if (abcd < (-0.5f + eps) * unitLength)
        {
            yaw = RadToDeg(-2.f * Atan2(j, r));
            pitch = RadToDeg(-M_PI_2);
            roll = 0.f;
        }
        else
        {
            const Float adbc = r*k - i*j;
            const Float acbd = r*j - i*k;
            yaw = RadToDeg(Atan2(2.f*adbc, 1.f - 2.f*(z2+x2)));
            pitch = RadToDeg(ASin(2.f*abcd/unitLength));
            roll = RadToDeg(Atan2(2.f*acbd, 1.f - 2.f*(y2+x2)));
        }

        return EulerAngles(roll, pitch, yaw);
    }

    UGE_INLINE Quaternion Quaternion::Lerp(const Quaternion& q1, const Quaternion& q2, const Float t) const
    {
        return Quaternion( VectorHelpers::QuatLerp( q1.vec.vec, q2.vec.vec, t));
    }

    UGE_INLINE Quaternion Quaternion::Slerp(const Quaternion& q1, const Quaternion& q2, const Float t, const Float tolerance) const
    {
        return Quaternion( VectorHelpers::QuatSlerp( q1.vec.vec, q2.vec.vec, t, tolerance));
    }

    UGE_INLINE Quaternion& Quaternion::Scale(const Vec4& scale)
    {
        i *= scale.x;
        j *= scale.y;
        k *= scale.z;
        return *this;
    }

    UGE_INLINE Bool Quaternion::IsOk() const
    {
        const Float tolerance = 0.01f;
        Bool valid = std::isfinite(i) && std::isfinite(j) && std::isfinite(k) && std::isfinite(r);
        Float length = Magnitude();
        Float err = length - 1.f;
        Bool validLength = Abs(err) < tolerance;
        valid = valid && validLength;
        return valid;
    }


}

#endif  // __COREMATH_MATH_QUATERNION_INL__