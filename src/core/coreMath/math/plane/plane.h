#ifndef __COREMATH_MATH_PLANE_H__
#define __COREMATH_MATH_PLANE_H__

namespace uge::math
{
    struct Vec4;
    struct Plane
    {
        enum EPlaneSide
        {
            EPlaneSide_None = 0,
            EPlaneSide_Front = 1,
            EPlaneSide_Back = 2,
            EPlaneSide_Both = EPlaneSide_Front | EPlaneSide_Back
        };

        Plane() = default;
        Plane(const Vec4& normal);
        Plane(const Vec4& normal, const Vec4& point);
        Plane(const Vec4& normal, Float& distance);
        Plane(const Vec4& point0, const Vec4& point1, const Vec4& point2);

        void Set(const Vec4& normal);
        void Set(const Vec4& normal, const Vec4& point);
        void Set(const Vec4& point0, const Vec4& point1, const Vec4& point2);

        Float DistanceTo(const Vec4& point) const;
        static Float DistanceTo(const Vec4& point, const Vec4& plane);

        EPlaneSide GetSide(const Vec4& point) const;
        //EPlaneSide GetSide(const Box& box) const;
        EPlaneSide GetSide(const Vec4& boxCenter, const Vec4& boxExtent) const;
        const Vec4& GetNormal() const;

        Vec4 Project(const Vec4& point) const;
        Bool Intersects(const Vec4& origin, const Vec4& direction, Vec4& intersectionPoint, Vec4& intersectionDistance) const;
        EPlaneSide IntersectsSide(const Vec4& origin, const Vec4& direction, Vec4& intersectionPoint, Vec4& intersectionDistance) const;
        static Bool IntersectsPlane(const Plane& plane0, const Plane& plane1, Vec4& outOrigin, Vec4& outDirection);

        Bool IsOk() const;

        Plane operator-() const; 

        Vec4 Normal;
    };
}

#endif // __COREMATH_MATH_PLANE_H__