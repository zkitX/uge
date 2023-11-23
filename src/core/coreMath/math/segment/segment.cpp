#include "build.h"
#include "segment.h"

#define SMALL_NUM   0.00000001 // anything that avoids division overflow

namespace uge::math
{
    // https://web.archive.org/web/20170617190239/http://geomalgorithms.com/a07-_distance.html
    Float Segment::SegmentDistance(const Segment& segment0, const Segment& segment1, Float& t0, Float& t1)
    {
        Vec4 w = segment0.Origin - segment1.Origin;
        Float a = Vec4::Dot(segment0.Direction, segment0.Direction, DotProduct3D);
        Float b = Vec4::Dot(segment0.Direction, segment1.Direction, DotProduct3D);
        Float c = Vec4::Dot(segment1.Direction, segment1.Direction, DotProduct3D);
        Float d = Vec4::Dot(segment0.Direction, w, DotProduct3D);
        Float e = Vec4::Dot(segment1.Direction, w, DotProduct3D);
        Float denom = a * c - b * b;
        Float sc, sN, sD = denom;       // sc = sN / sD, default sD = D >= 0
        Float tc, tN, tD = denom;       // tc = tN / tD, default tD = D >= 0

        // compute the line parameters of the two closest points
        if (denom < SMALL_NUM)
        {
            // the lines are almost parallel
            sN = 0.0f;         // force using point P0 on segment S1
            sD = 1.0f;         // to prevent possible division by 0.0 later
            tN = e;
            tD = c;
        }
        else
        {
            // get the closest points on the infinite lines
            sN = (b * e - c * d);
            tN = (a * e - b * d);
            if (sN < 0.0f)  // sc < 0 => the s=0 edge is visible
            {
                sN = 0.0f;
                tN = e;
                tD = c;
            }
            else if (sN > sD)   // sc > 1  => the s=1 edge is visible
            {
                sN = sD;
                tN = e + b;
                tD = c;
            }
        }

        if (tN < 0.0f)  // tc < 0 => the t=0 edge is visible
        {
            tN = 0.0f;
            // recompute sc for this edge
            if (-d < 0.0f)
            {
                sN = 0.0f;
            }
            else if (-d > a)
            {
                sN = sD;
            }
            else
            {
                sN = -d;
                sD = a;
            }
        }
        else if (tN > tD)   // tc > 1  => the t=1 edge is visible
        {
            tN = tD;
            // recompute sc for this edge
            if ((-d + b) < 0.0f)
            {
                sN = 0;
            }
            else if ((-d + b) > a)
            {
                sN = sD;
            }
            else
            {
                sN = (-d + b);
                sD = a;
            }
        }

        // finally do the division to get t0 and t1
        t0 = (fabs(sN) < SMALL_NUM ? 0.0f : sN / sD);
        t1 = (fabs(tN) < SMALL_NUM ? 0.0f : tN / tD);

        // get the difference of the two closest points
        Vec4 diff = w + (segment0.Direction * t0) - (segment1.Direction * t1);  // =  S1(sc) - S2(tc)

        return diff.Magnitude(DotProduct3D);   // return the closest distance
    }
}