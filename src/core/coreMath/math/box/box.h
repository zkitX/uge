#ifndef __COREMATH_BOX_H__
#define __COREMATH_BOX_H__

namespace uge::math
{
    struct Sphere;
    struct Segment;

    struct Box
    {
        enum ECorner
        {
            eCorner_NearLowerLeft = 0,
            eCorner_NearLowerRight,
            eCorner_NearUpperLeft,
            eCorner_NearUpperRight,
            eCorner_FarLowerLeft,
            eCorner_FarLowerRight,
            eCorner_FarUpperLeft,
            eCorner_FarUpperRight,
            eCorner_Count
        };

        Vec4 Min;
        Vec4 Max;

        Box() = default;
        Box(const Box &box);
        Box(const Vec4 &min, const Vec4 &max);
        Box(const Vec4 &center, Float radius);

        Bool operator==(const Box &box) const;
        Bool operator!=(const Box &box) const;
        Bool operator<(const Box &box) const;
        Box &operator=(const Box &box) = default;

        // Box translation
        Box operator+(const Vec4 &dir) const;
        Box operator-(const Vec4 &dir) const;
        // Box scaling
        Box operator*(const Vec4 &scale) const;

        // Box translation
        void operator+=(const Vec4 &dir);
        void operator-=(const Vec4 &dir);
        // Box scaling
        void operator*=(const Vec4 &scale);

        Bool IsEmpty() const;
        Bool IsValid() const;
        Box &Clear();

        Bool Contains(const Vec4 &point) const;
        Bool Contains(const Vec3 &point, Float zExtent) const;
        Bool Contains(const Box &box) const;
        Bool ContainsExcludeEdges(const Box &box) const;
        Bool ContainsExcludeEdges(const Vec4 &point) const;
        Bool Contains2D(const Box &box) const;
        Bool Touches(const Box &box) const;
        Bool Touches(const Vec3 &min, const Vec3 &max) const;
        Bool Touches2D(const Box &box) const;

        Box &AddPoint(const Vec4 &point);
        Box &AddPoint(const Vec3 &point);
        Box &AddBox(const Box &box);

        void CalculateCorners(Vec4 *corners) const;
        Vec4 CalculateCorner(ECorner corner) const;
        Vec4 CalculateCenter() const;
        Vec4 CalculateExtents() const;
        Vec4 CalculateSize() const;
        Float CalculateVolume() const;

        Box &Extrude(const Vec4 &dir);
        Box &Extrude(const Float distance);
        Box &Expand(const Vec4 &dir);
        Box &Expand(const Float distance);
        void Crop(const Box &box);
        Box &Normalize(const Box &unitBox);

        Float Distance(const Vec4 &point) const;
        Float SquaredDistance(const Vec4 &point) const;
        Float SquaredDistance2D(const Vec4 &point) const;
        Float SquaredDistance(const Box &box) const;
        Float FarthestDistance(const Vec4 &point) const;
        Float SquaredFarthestDistance(const Vec4 &point) const;

        static Box UnitBox();
        static Box EmptyBox();
        static Box FullBox();

        // COREMATH_API Bool IntersectSphere( const Sphere& sphere ) const;
        COREMATH_API Bool IntersectSegment(const Segment &segment, Vec4 &entryPoint) const;
        COREMATH_API Bool IntersectSegment(const Segment &segment, Vec4 &entryPoint, Vec4 &exitPoint) const;
        COREMATH_API Bool IntersectLine(const Vec4 &origin, const Vec4 &direction, Float &entryFromOrigin, Float &exitFromOrigin) const;
        COREMATH_API Bool IntersectRay(const Vec4 &origin, const Vec4 &direction, Float &entryFromOrigin, Float *exitFromOrigin) const;
        COREMATH_API Bool IntersectRay(const Vec4 &origin, const Vec4 &direction, Vec4 &entryPoint) const;
    };
}

#include "box.inl"

#endif // __COREMATH_BOX_H__