#ifndef __COREMATH_MATH_SEGMENT_H__
#define __COREMATH_MATH_SEGMENT_H__

namespace uge::math
{
    struct Vec4;
    struct Segment
    {
        Vec4 Origin;
        Vec4 Direction;

        Segment() = default;
        Segment(const Segment& other);
        Segment(const Vec4& origin, const Vec4& direction);

        Segment operator+(const Vec4& dir) const;
        Segment operator-(const Vec4& dir) const;
        void operator+=(const Vec4& dir);
        void operator-=(const Vec4& dir);

        Vec4 GetPosistion() const;
        COREMATH_API static Float SegmentDistance(const Segment& segment0, const Segment& segment1, Float& t0, Float& t1);
    };
}

#include "segment.inl"

#endif // __COREMATH_MATH_SEGMENT_H__