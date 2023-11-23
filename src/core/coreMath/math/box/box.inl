#ifndef __COREMATH_BOX_INL__
#define __COREMATH_BOX_INL__

namespace uge::math
{
    UGE_FORCE_INLINE Box::Box(const Box &box)
        : Min(box.Min)
        , Max(box.Max)
    {
    }

    UGE_FORCE_INLINE Box::Box(const Vec4 &min, const Vec4 &max)
        : Min(min)
        , Max(max)
    {
    }

    UGE_FORCE_INLINE Box::Box(const Vec4 &center, Float radius)
        : Min(center - Vec4(radius, radius, radius, 0))
        , Max(center + Vec4(radius, radius, radius, 0))
    {
    }

    UGE_FORCE_INLINE Bool Box::operator==(const Box &box) const
    {
        return Vec4::Equal3(Min, box.Min) && Vec4::Equal3(Max, box.Max);
    }

    UGE_FORCE_INLINE Bool Box::operator!=(const Box &box) const
    {
        return !(Vec4::Equal3(Min, box.Min) && Vec4::Equal3(Max, box.Max));
    }

    UGE_FORCE_INLINE Bool Box::operator<(const Box &box) const
    {
        return Min < box.Min || (Min == box.Min && Max < box.Max);
    }

    UGE_FORCE_INLINE Box Box::operator+(const Vec4 &dir) const
    {
        return Box(Min + dir, Max + dir);
    }

    UGE_FORCE_INLINE Box Box::operator-(const Vec4 &dir) const
    {
        return Box(Min - dir, Max - dir);
    }

    UGE_FORCE_INLINE Box Box::operator*(const Vec4 &scale) const
    {
        return Box(Min * scale, Max * scale);
    }

    UGE_FORCE_INLINE void Box::operator+=(const Vec4 &dir)
    {
        Min += dir;
        Max += dir;
    }

    UGE_FORCE_INLINE void Box::operator-=(const Vec4 &dir)
    {
        Min -= dir;
        Max -= dir;
    }

    UGE_FORCE_INLINE void Box::operator*=(const Vec4 &scale)
    {
        Min *= scale;
        Max *= scale;
    }

    UGE_INLINE Bool Box::IsEmpty() const
    {
        (Max.x < Min.x) || (Max.y < Min.y) || (Max.z < Min.z);
    }

    UGE_INLINE Bool Box::IsValid() const
    {
        return Min.IsValid() && Max.IsValid();
    }

    UGE_INLINE Box &Box::Clear()
    {
        Min = Vec4::MaxPlus();
        Max = Vec4::MaxMinus();
        return *this;
    }

    UGE_INLINE Bool Box::Contains(const Vec4 &point) const
    {
        return Vec4::LessEqual3(Min, point) && Vec4::LessEqual3(point, Max);
    }

    UGE_INLINE Bool Box::Contains(const Vec3 &point, Float zExtent) const
    {
        const Float step = Max.z - Min.z;
        Vec4 v = point;

        if (step > 0.f)
        {
            for ( Float z = 0.f; z <= zExtent; z += step )
            {
                v.z += z;
                if (Contains(v))
                {
                    return true;
                }
            }
        }
        else if (zExtent > 0.f)
        {
            if (Contains(v))
            {
                return true;
            }
        }

        v.z = point.z + zExtent;
        return Contains(v);
    }

    UGE_INLINE Bool Box::Contains(const Box &box) const
    {
        return Vec4::LessEqual3(Min, box.Min) && Vec4::LessEqual3(box.Max, Max);
    }

    UGE_INLINE Bool Box::ContainsExcludeEdges(const Box &box) const
    {
        return Vec4::Less3(Min, box.Min) && Vec4::Less3(box.Max, Max);
    }
    
    UGE_INLINE Bool Box::ContainsExcludeEdges(const Vec4 &point) const
    {
        if (Vec4::Less3(Min, point) && Vec4::Less3(point, Max))
        {
            return true;
        }
        return false;
    }

    UGE_INLINE Bool Box::Contains2D(const Box &box) const
    {
        return Vec4::LessEqual2(Min, box.Min) && Vec4::LessEqual2(box.Max, Max);
    }

    UGE_INLINE Bool Box::Touches(const Box &box) const
    {
        return Vec4::LessEqual3(Min, box.Max) && Vec4::LessEqual3(box.Min, Max);
    }

    UGE_INLINE Bool Box::Touches(const Vec3 &bMin, const Vec3 &bMax) const
    {
        return Vec4::LessEqual3(Min, bMax) && Vec4::LessEqual3(bMin, Max);
    }

    UGE_INLINE Bool Box::Touches2D(const Box &box) const
    {
        return Vec4::LessEqual2(Min, box.Max) && Vec4::LessEqual2(box.Min, Max);
    }

    UGE_INLINE Box &Box::AddPoint(const Vec4 &point)
    {
        Min = Vec4::Min4(Min, point);
        Max = Vec4::Max4(Max, point);
        return *this;
    }

    UGE_INLINE Box &Box::AddPoint(const Vec3 &point)
    {
        Min.x = math::Min(Min.x, point.x);
        Min.y = math::Min(Min.y, point.y);
        Min.z = math::Min(Min.z, point.z);
        Min.w = 1.f;

        Max.x = math::Max(Max.x, point.x);
        Max.y = math::Max(Max.y, point.y);
        Max.z = math::Max(Max.z, point.z);
        Max.w = 1.f;

        return *this;
    }

    UGE_INLINE Box& Box::AddBox(const Box &box)
    {
        Min = Vec4::Min4(Min, box.Min);
        Max = Vec4::Max4(Max, box.Max);
        return *this;
    }

    UGE_INLINE void Box::CalculateCorners(Vec4* corners) const
    {
        corners[eCorner_NearLowerLeft] = Vec4(Min.x, Min.y, Min.z);
        corners[eCorner_NearLowerRight] = Vec4(Max.x, Min.y, Min.z);
        corners[eCorner_NearUpperLeft] = Vec4(Min.x, Max.y, Min.z);
        corners[eCorner_NearUpperRight] = Vec4(Max.x, Max.y, Min.z);
        corners[eCorner_FarLowerLeft] = Vec4(Min.x, Min.y, Max.z);
        corners[eCorner_FarLowerRight] = Vec4(Max.x, Min.y, Max.z);
        corners[eCorner_FarUpperLeft] = Vec4(Min.x, Max.y, Max.z);
        corners[eCorner_FarUpperRight] = Vec4(Max.x, Max.y, Max.z);
    }

    UGE_INLINE Vec4 Box::CalculateCorner(ECorner corner) const
    {
        switch (corner)
        {
        case eCorner_NearLowerLeft:
            return Vec4(Min.x, Min.y, Min.z);
        case eCorner_NearLowerRight:
            return Vec4(Max.x, Min.y, Min.z);
        case eCorner_NearUpperLeft:
            return Vec4(Min.x, Max.y, Min.z);
        case eCorner_NearUpperRight:
            return Vec4(Max.x, Max.y, Min.z);
        case eCorner_FarLowerLeft:
            return Vec4(Min.x, Min.y, Max.z);
        case eCorner_FarLowerRight:
            return Vec4(Max.x, Min.y, Max.z);
        case eCorner_FarUpperLeft:
            return Vec4(Min.x, Max.y, Max.z);
        case eCorner_FarUpperRight:
            return Vec4(Max.x, Max.y, Max.z);
        default:
            UGE_ASSERT(false, "Invalid corner index");
            return Vec4::Zeros();
        }
    }

    UGE_FORCE_INLINE Vec4 Box::CalculateCenter() const
    {
        return (Min + Max) * 0.5f;
    }

    UGE_FORCE_INLINE Vec4 Box::CalculateExtents() const
    {
        return (Max - Min) * 0.5f;
    }

    UGE_FORCE_INLINE Vec4 Box::CalculateSize() const
    {
        return Max - Min;
    }

    UGE_FORCE_INLINE Float Box::CalculateVolume() const
    {
        const Vec4 size = CalculateSize();
        return size.x * size.y * size.z;
    }

    UGE_INLINE Box& Box::Extrude(const Vec4 &dir)
    {
        Min -= dir;
        Max += dir;
        return *this;
    }

    UGE_INLINE Box& Box::Extrude(Float distance)
    {
        Min -= distance;
        Max += distance;
        return *this;
    }

    UGE_INLINE Box& Box::Expand(const Vec4 &dir)
    {
        const Vec4 center = CalculateCenter();
        *this -= center;
        Extrude(dir);
        *this += center;
        return *this;
    }

    UGE_INLINE Box& Box::Expand(Float distance)
    {
        const Vec4 center = CalculateCenter();
        *this -= center;
        Extrude(distance);
        *this += center;
        return *this;
    }

    UGE_INLINE void Box::Crop(const Box &box)
    {
        Min = Vec4::Min4( Vec4::Max4(Min, box.Min), box.Max );
        Max = Vec4::Min4( Vec4::Max4(Max, box.Max), box.Min );
    }

    UGE_INLINE Box& Box::Normalize(const Box &unitBox)
    {
        UGE_ASSERT(!unitBox.IsEmpty(), "Unit box is empty");

        const Vec4 size = Vec4::Ones() / unitBox.CalculateSize();
        Min = (Min - unitBox.Min) * size;
        Max = (Max - unitBox.Min) * size;
        return *this;
    }

    UGE_INLINE Float Box::Distance(const Vec4 &point) const
    {
        Float sqrDistance = 0.f;
        for (size_t i = 0; i < 3; ++i)
        {
            const Float v = point[i];
            if (v < Min[i])
            {
                sqrDistance += Sqr(Min[i] - v);
            }
            if (v > Max[i])
            {
                sqrDistance += Sqr(v - Max[i]);
            }
        }

        return Sqrt(sqrDistance);
    }

    UGE_INLINE Float Box::SquaredDistance(const Vec4 &point) const
    {
        Float sqrDistance = 0.f;
        for (size_t i = 0; i < 3; ++i)
        {
            const Float v = point[i];
            if (v < Min[i])
            {
                sqrDistance += Sqr(Min[i] - v);
            }
            if (v > Max[i])
            {
                sqrDistance += Sqr(v - Max[i]);
            }
        }

        return sqrDistance;
    }

    UGE_INLINE Float Box::SquaredDistance2D(const Vec4 &point) const
    {
        Float sqrDistance = 0.f;
        for (size_t i = 0; i < 2; ++i)
        {
            const Float v = point[i];
            if (v < Min[i])
            {
                sqrDistance += Sqr(Min[i] - v);
            }
            if (v > Max[i])
            {
                sqrDistance += Sqr(v - Max[i]);
            }
        }

        return sqrDistance;
    }

    UGE_INLINE Float Box::SquaredDistance(const Box &box) const
    {
        Float sqrDistance = 0.f;
        for (size_t i = 0; i < 3; ++i)
        {
            const Float vMin = box.Min[i];
            const Float vMax = box.Max[i];
            if (vMin > Max[i])
            {
                sqrDistance += Sqr(vMin - Max[i]);
            }
            else if (vMax < Min[i])
            {
                sqrDistance += Sqr(Min[i] - vMax);
            }
        }

        return sqrDistance;
    }

    UGE_INLINE Float Box::FarthestDistance(const Vec4 &point) const
    {
        Float sqrDistance = 0.f;
        for (size_t i = 0; i < 3; ++i)
        {
            const Float v = point[i];
            if (v < Min[i])
            {
                sqrDistance += Sqr(Max[i] - v);
            }
            if (v > Max[i])
            {
                sqrDistance += Sqr(v - Min[i]);
            }
        }

        return Sqrt(sqrDistance);
    }

    UGE_INLINE Float Box::SquaredFarthestDistance(const Vec4 &point) const
    {
        Float sqrDistance = 0.f;
        for (size_t i = 0; i < 3; ++i)
        {
            const Float v = point[i];
            if (v < Min[i])
            {
                sqrDistance += Sqr(Max[i] - v);
            }
            if (v > Max[i])
            {
                sqrDistance += Sqr(v - Min[i]);
            }
        }

        return sqrDistance;
    }

    UGE_FORCE_INLINE Box Box::UnitBox()
    {
        return Box(Vec4::Zeros(), Vec4::Ones());
    }

    UGE_FORCE_INLINE Box Box::EmptyBox()
    {
        return Box(Vec4::MaxPlus(), Vec4::MaxMinus());
    }

    UGE_FORCE_INLINE Box Box::FullBox()
    {
        return Box(Vec4::MaxMinus(), Vec4::MaxPlus());
    }
}

#endif // __COREMATH_BOX_INL__