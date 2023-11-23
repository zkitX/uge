#ifndef __COREMATH_MATH_SEGMENT_INL__
#define __COREMATH_MATH_SEGMENT_INL__

namespace uge::math
{
    UGE_FORCE_INLINE Segment::Segment(const Segment& other)
    : Origin(other.Origin), Direction(other.Direction)
    {
    }

    UGE_FORCE_INLINE Segment::Segment(const Vec4& origin, const Vec4& direction)
    : Origin(origin), Direction(direction)
    {
    }

    UGE_FORCE_INLINE Segment Segment::operator+(const Vec4& dir) const
    {
        return Segment(Origin + dir, Direction);
    }

    UGE_FORCE_INLINE Segment Segment::operator-(const Vec4& dir) const
    {
        return Segment(Origin - dir, Direction);
    }

    UGE_FORCE_INLINE void Segment::operator+=(const Vec4& dir)
    {
        Origin += dir;
    }

    UGE_FORCE_INLINE void Segment::operator-=(const Vec4& dir)
    {
        Origin -= dir;
    }

    UGE_FORCE_INLINE Vec4 Segment::GetPosistion() const
    {
        return Origin;
    }
}

#endif // __COREMATH_MATH_SEGMENT_INL__