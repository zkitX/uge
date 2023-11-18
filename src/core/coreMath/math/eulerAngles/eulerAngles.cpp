#include "build.h"

#include "eulerAngles.h"

namespace uge::math
{
    Matrix EulerAngles::ToMatrix() const
    {
        Float cosRoll = Cos(DegToRad(Roll));
        Float sinRoll = Sin(DegToRad(Roll));
        Float cosPitch = Cos(DegToRad(Pitch));
        Float sinPitch = Sin(DegToRad(Pitch));
        Float cosYaw = Cos(DegToRad(Yaw));
        Float sinYaw = Sin(DegToRad(Yaw));

        Matrix result;
        result.SetIdentity();
        result[0][0] = cosRoll * cosYaw - sinPitch * sinRoll * sinYaw;
        result[0][1] = sinPitch * sinRoll * cosYaw + cosRoll * sinYaw;
        result[0][2] = -cosPitch * sinRoll;
        result[1][0] = cosPitch * -sinYaw;
        result[1][1] = cosPitch * cosYaw;
        result[1][2] = sinPitch;
        result[2][0] = sinPitch * cosRoll * sinYaw + sinRoll * cosYaw;
        result[2][1] = sinRoll * sinYaw - sinPitch * cosRoll * cosYaw;
        result[2][2] = cosPitch * cosRoll;
        return result;
    }

    void EulerAngles::ToMatrix(Matrix &m) const
    {
        Float cosRoll = Cos(DegToRad(Roll));
        Float sinRoll = Sin(DegToRad(Roll));
        Float cosPitch = Cos(DegToRad(Pitch));
        Float sinPitch = Sin(DegToRad(Pitch));
        Float cosYaw = Cos(DegToRad(Yaw));
        Float sinYaw = Sin(DegToRad(Yaw));

        m[0][0] = cosRoll * cosYaw - sinPitch * sinRoll * sinYaw;
        m[0][1] = sinPitch * sinRoll * cosYaw + cosRoll * sinYaw;
        m[0][2] = -cosPitch * sinRoll;
        m[0][3] = 0.0f;

        m[1][0] = cosPitch * -sinYaw;
        m[1][1] = cosPitch * cosYaw;
        m[1][2] = sinPitch;
        m[1][3] = 0.0f;

        m[2][0] = sinPitch * cosRoll * sinYaw + sinRoll * cosYaw;
        m[2][1] = sinRoll * sinYaw - sinPitch * cosRoll * cosYaw;
        m[2][2] = cosPitch * cosRoll;
        m[2][3] = 0.0f;

        m[3][0] = 0.0f;
        m[3][1] = 0.0f;
        m[3][2] = 0.0f;
        m[3][3] = 1.0f;
    }

    Quaternion EulerAngles::ToQuaternion() const
    {
        Quaternion q;

        const Float c1 = Cos(DegToRad(Yaw) * 0.5f);
        const Float c2 = Cos(DegToRad(Pitch) * 0.5f);
        const Float c3 = Cos(DegToRad(Roll) * 0.5f);

        const Float s1 = Sin(DegToRad(Yaw) * 0.5f);
        const Float s2 = Sin(DegToRad(Pitch) * 0.5f);
        const Float s3 = Sin(DegToRad(Roll) * 0.5f);

        q.r = c1 * c2 * c3 - s1 * s2 * s3;
        q.i = c1 * s2 * c3 - s1 * c2 * s3;
        q.j = s1 * s2 * c3 + c1 * c2 * s3;
        q.k = s1 * c2 * c3 + c1 * s2 * s3;

        return q.Normalized();
    }

    Vec4 EulerAngles::TransformPoint(const Vec4 &v) const
    {
        Matrix m = ToMatrix();
        return m.TransformPoint(v);
    }

    Vec4 EulerAngles::TransformVector(const Vec4 &v) const
    {
        Matrix m = ToMatrix();
        return m.Transform(v);
    }

    void EulerAngles::ToAngleVectors(Vec4 *forward, Vec4 *right, Vec4 *up) const
    {
        Vec4 f(0, 1, 0);
        Vec4 r(1, 0, 0);
        Vec4 u(0, 0, 1);

        Matrix m = ToMatrix();

        if (forward)
        {
            *forward = m.Transform(f);
            forward->Normalize(DotProduct3D);
        }

        if (right)
        {
            *right = m.Transform(r);
            right->Normalize(DotProduct3D);
        }

        if (up)
        {
            *up = m.Transform(u);
            up->Normalize(DotProduct3D);
        }
    }
}