#ifndef __COREMATH_MATH_PLANE_INL__
#define __COREMATH_MATH_PLANE_INL__

namespace uge::math
{
    UGE_INLINE Plane::Plane(const Vec4& normal)
    {
        Set(normal);
    }

    UGE_INLINE Plane::Plane(const Vec4& normal, const Vec4& point)
    {
        Set(normal, point);
    }

    UGE_INLINE Plane::Plane(const Vec4& normal, Float& distance)
    {
        Set(normal, distance);
    }

    UGE_INLINE Plane::Plane(const Vec4& point0, const Vec4& point1, const Vec4& point2)
    {
        Set(point0, point1, point2);
    }

    UGE_INLINE void Plane::Set(const Vec4& normal)
    {
        Normal = normal;
    }

    UGE_INLINE void Plane::Set(const Vec4& normal, const Vec4& point)
    {
        UGE_ASSERT(normal.Magnitude(DotProduct3D) > 0.995f && normal.Magnitude(DotProduct3D) < 1.005f, "Normal must be normalized");
        Normal[0] = normal[0];
        Normal[1] = normal[1];
        Normal[2] = normal[2];
        Normal[3] = -Vec4::Dot(normal, point, DotProduct3D);
    }

    UGE_INLINE void Plane::Set(const Vec4& point0, const Vec4& point1, const Vec4& point2)
    {
        Normal = Vec4::Cross(point1 - point0, point2 - point0);
        Normal.Normalize(DotProduct3D);
        Normal[3] = -Vec4::Dot(Normal, point0, DotProduct3D);
    }

    UGE_INLINE Float Plane::DistanceTo(const Vec4& point) const
    {
        return Vec4::Dot(point, Normal, DotProduct3D) + Normal[3];
    }

    UGE_INLINE Float Plane::DistanceTo(const Vec4& plane, const Vec4& point)
    {
        return Vec4::Dot(point, plane, DotProduct3D) + plane[3];
    }

    UGE_INLINE Plane::EPlaneSide Plane::GetSide(const Vec4& point) const
    {
        Float distance = DistanceTo(point);
        if (distance > 0.0f)
            return EPlaneSide_Front;
        else if (distance < 0.0f)
            return EPlaneSide_Back;
        else
            return EPlaneSide_None;
    }

    UGE_INLINE Plane::EPlaneSide Plane::GetSide(const Vec4& boxCenter, const Vec4& boxExtent) const
    {
        Float distance = DistanceTo(boxCenter);
        Float radius = boxExtent[0] * Abs(Normal[0]) + boxExtent[1] * Abs(Normal[1]) + boxExtent[2] * Abs(Normal[2]);
        if (distance > radius)
            return EPlaneSide_Front;
        else if (distance < -radius)
            return EPlaneSide_Back;
        else
            return EPlaneSide_Both;
    }

    UGE_INLINE const Vec4& Plane::GetNormal() const
    {
        return Normal;
    }

    UGE_INLINE Vec4 Plane::Project(const Vec4& point) const
    {
        return point - Normal * DistanceTo(point);
    }

    UGE_INLINE Bool Plane::Intersects(const Vec4& origin, const Vec4& direction, Vec4& intersectionPoint, Vec4& intersectionDistance) const
    {
        Float proj = Vec4::Dot(direction, Normal, DotProduct3D);
        if (proj > 0.0f)
        {
            intersectionDistance = DistanceTo(origin) / proj;
            intersectionPoint = origin + (direction * intersectionDistance);
            return true;
        }
        return false;
    }

    UGE_INLINE Plane::EPlaneSide Plane::IntersectsSide(const Vec4& origin, const Vec4& direction, Vec4& intersectionPoint, Vec4& intersectionDistance) const
    {
        Float proj = -Vec4::Dot(Normal, direction, DotProduct3D);
        if (Abs(proj) < 0.0001f)
            return EPlaneSide_None;
        intersectionDistance = DistanceTo(origin) / proj;
        intersectionPoint = origin + (direction * intersectionDistance);
        return (proj >= 0.0f) ? EPlaneSide_Front : EPlaneSide_Back;
    }

    UGE_INLINE Bool Plane::IntersectsPlane(const Plane& plane0, const Plane& plane1, Vec4& outOrigin, Vec4& outDirection)
    {
        Vec4 direction = Vec4::Cross(plane0.Normal, plane1.Normal);
        Float length = direction.Magnitude(DotProduct3D);
        if (length == 0.f)
            return false;
        
        outOrigin = ( Vec4::Cross(direction, plane1.Normal) * plane0.Normal[3] + Vec4::Cross(plane0.Normal, direction) * plane1.Normal[3] ) / length;
        return true;
    }

    UGE_INLINE Bool Plane::IsOk() const
    {
        if (!Normal.IsValid())
            return false;

        if (!Normal.IsNormalized(DotProduct3D))
            return false;

        return true;
    }

    UGE_INLINE Plane Plane::operator-() const
    {
        return Plane(-Normal);
    }
}

#endif // __COREMATH_MATH_PLANE_INL__