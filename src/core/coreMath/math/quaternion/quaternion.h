#ifndef __COREMATH_MATH_QUATERNION_H__
#define __COREMATH_MATH_QUATERNION_H__

namespace uge::math
{
    struct Matrix;
    struct EulerAngles;

    enum EQuaternionAxis
    {
        EQuaternionAxis_X,
        EQuaternionAxis_Y,
        EQuaternionAxis_Z
    };

    enum EQuaternionDimension
    {
        EQuaternionDimension_3D,
        EQuaternionDimension_4D
    };

    enum EQuaternionDirection
    {
        EQuaternionDirection_Forward,
        EQuaternionDirection_Right,
        EQuaternionDirection_Up
    };

    UGE_ALIGNED_STRUCT( Quaternion, 16 )
    {
        union
        {
            struct
            {
                Float i, j, k, r;
            };
            Vec4 vec;
        };

        Quaternion();

        Quaternion( const Float i, const Float j, const Float k, const Float r );
        Quaternion( const Float f[4] );
        Quaternion( const Quaternion& q );
        Quaternion( const Vec4& v );

        Quaternion(const Float yaw, const Float pitch, const Float roll);
        Quaternion(const Vec4& axis, const Float angle);
        Quaternion(const Vec3& axis, const Float angle);

        Quaternion& operator=( const Quaternion& q );

        Quaternion operator+( const Quaternion& q ) const;
        Quaternion operator-( const Quaternion& q ) const;
        Quaternion operator*( const Quaternion& q ) const;
        Quaternion operator*( const Float f ) const;
        Quaternion operator/( const Quaternion& q ) const;
        Quaternion operator/( const Float f ) const;

        Quaternion& operator+=( const Quaternion& q );
        Quaternion& operator-=( const Quaternion& q );
        Quaternion& operator*=( const Quaternion& q );
        Quaternion& operator/=( const Quaternion& q );
        Quaternion& operator*=( const Float f );
        Quaternion& operator/=( const Float f );

        Bool operator==( const Quaternion& q ) const;
        Bool operator!=( const Quaternion& q ) const;

        Vec3 operator*( const Vec3& v ) const;
        Vec4 operator*( const Vec4& v ) const;

        static Quaternion Identity();
        static Quaternion I();
        static Quaternion J();
        static Quaternion K();

        void SetIdentity();
        void SetZero();
        void SetInverse();
        void SetNegate();
        void SetConjugate();

        void SetAxisAngle(const Vec4& axis, const Float angle);
        void SetAxisAngle(const Vec3& axis, const Float angle);
        void SetXRotation(const Float angle);
        void SetYRotation(const Float angle);
        void SetZRotation(const Float angle);

        Float Magnitude() const;
        Float MagnitudeSquared() const;

        Quaternion Conjugate() const;
        Quaternion Inverse() const;
        void Normalize();
        Quaternion Normalized() const;

        Vec4 DoTransform(const Vec4& v) const;
        Vec3 DoTransform(const Vec3& v) const;
        Vec4 Transform(const Vec4& v) const;
        Vec3 Transform(const Vec3& v) const;

        Vec4 TransformInverse(const Vec4& in) const;
        Vec3 TransformInverse(const Vec3& in) const;
        Vec4 TransformConjugate(const Vec4& in) const;
        Vec3 TransformConjugate(const Vec3& in) const;

        template <typename T>
        T GetAxis( const EQuaternionAxis axis ) const;

        template <typename T>
        T GetDirection( const EQuaternionDirection direction ) const;

        template <typename T>
        T GetAxis() const;
        
        Float GetPitch() const;
        Float GetYaw() const;
        Float GetRoll() const;
        Float GetAngle() const;

        Matrix ToMatrix() const;
        EulerAngles ToEulerAngles() const;

        Quaternion Lerp(const Quaternion& q1, const Quaternion& q2, const Float t) const;
        Quaternion Slerp(const Quaternion& q1, const Quaternion& q2, const Float t, const Float tolerance) const;

        Quaternion& Scale( const Vec4& scale );
        
        Bool IsOk() const;
    };
}

#include "quaternion.inl"

#endif  // __COREMATH_MATH_QUATERNION_H__