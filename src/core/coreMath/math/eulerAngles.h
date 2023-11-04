#ifndef __COREMATH_MATH_EULERANGLES_H__
#define __COREMATH_MATH_EULERANGLES_H__

namespace uge::math
{
    struct Matrix;
    struct Quaternion;

    struct EulerAngles
    {
        Float Roll;
        Float Pitch;
        Float Yaw;

        EulerAngles();
        EulerAngles(const Vec3 &v);
        EulerAngles(const Float f[3]);
        EulerAngles(const Float Roll, const Float Pitch, const Float Yaw);
        EulerAngles(const EulerAngles &other);
        EulerAngles &operator=(const EulerAngles &other);

        void Set(Float Roll, Float Pitch, Float Yaw);

        EulerAngles operator-() const;
        EulerAngles operator+(const EulerAngles &other) const;
        EulerAngles operator-(const EulerAngles &other) const;
        EulerAngles operator*(const EulerAngles &other) const;
        EulerAngles operator/(const EulerAngles &other) const;

        EulerAngles &operator+=(const EulerAngles &other);
        EulerAngles &operator-=(const EulerAngles &other);
        EulerAngles &operator*=(const EulerAngles &other);
        EulerAngles &operator/=(const EulerAngles &other);

        EulerAngles operator+(Float scalar) const;
        EulerAngles operator-(Float scalar) const;
        EulerAngles operator*(Float scalar) const;
        EulerAngles operator/(Float scalar) const;

        EulerAngles &operator+=(Float scalar);
        EulerAngles &operator-=(Float scalar);
        EulerAngles &operator*=(Float scalar);
        EulerAngles &operator/=(Float scalar);

        Bool operator==(const EulerAngles &other) const;
        Bool operator!=(const EulerAngles &other) const;

        Float &operator[](UInt32 index);
        const Float &operator[](UInt32 index) const;

        EulerAngles &Normalize();
        static Float NormalizeAngle180(Float angle);
        static Float NormalizeAngle360(Float angle);

        static Float YawFromXY(const Vec2 &v);
        static Double YawFromXY(const Double x, const Double y);
        static Vec4 YawToVector(const Float yaw);
        static Vec2 YawToVector2(const Float yaw);

        static Float AngleDistance(const Float a, const Float b);
        static EulerAngles AngleDistance(const EulerAngles &a, const EulerAngles &b);

        static Float Interpolate(const Float a, const Float b, const Float t);
        static EulerAngles Interpolate(const EulerAngles &a, const EulerAngles &b, const Float t);
        void Interpolate(const EulerAngles &a, const Float t);

        Matrix ToMatrix() const;
        void ToMatrix(Matrix &m) const;
        void ToAngleVectors(Vec4 &forward, Vec4 &right, Vec4 &up) const;
        Quaternion ToQuaternion() const;
        void ToQuaternion(Quaternion &q) const;
        Vec4 TransformPoint(const Vec4 &v) const;
        Vec4 TransformVector(const Vec4 &v) const;

        static const EulerAngles Zero;
    };
}

#include "eulerAngles.inl"

#endif  // __COREMATH_MATH_EULERANGLES_H__