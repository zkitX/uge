#include "build.h"
#include "color.h"

namespace uge::math
{
    GammaToLinearLUT g_gammaToLinearLUT;

    GammaToLinearLUT::GammaToLinearLUT()
    {
        for (UInt32 i = 0; i < LUTSize; ++i)
        {
            const Float gammaSpace = (Float)i / (Float)(LUTSize - 1);
            const Float linearSpace = ToLinearAccu(gammaSpace);

            LUT[i] = linearSpace;
            LUTHalf[i] = Half(linearSpace);
        }
    }
}