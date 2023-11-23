#ifndef __COREMATH_FLOAT16_H__
#define __COREMATH_FLOAT16_H__

namespace uge::math
{
    class Float16Compressor
    {
        union Bits
        {
            Float f;
            Int32 si;
            UInt32 ui;
        };

        static Int32 const shift = 13;
        static Int32 const shiftSign = 16;

        static Int32 const infN = 0x7F800000;  // flt32 infinity
        static Int32 const maxN = 0x477FE000;  // max flt16 normal as a flt32
        static Int32 const minN = 0x38800000;  // min flt16 normal as a flt32
        static Int32 const signN = 0x80000000; // flt32 sign bit

        static Int32 const infC = infN >> shift;
        static Int32 const nanN = (infC + 1) << shift; // minimum flt16 nan as a flt32
        static Int32 const maxC = maxN >> shift;
        static Int32 const minC = minN >> shift;
        static Int32 const signC = signN >> shiftSign; // flt16 sign bit

        static Int32 const mulN = 0x52000000; // (1 << 23) / minN
        static Int32 const mulC = 0x33800000; // minN / (1 << (23 - shift))

        static Int32 const subC = 0x003FF; // max flt32 subnormal down shifted
        static Int32 const norC = 0x00400; // min flt32 normal down shifted

        static Int32 const maxD = infC - maxC - 1;
        static Int32 const minD = minC - subC - 1;

    public:
        UGE_FORCE_INLINE static UInt16 compress(float value)
        {
            Bits v, s;
            v.f = value;
            UInt32 sign = v.si & signN;
            v.si ^= sign;
            sign >>= shiftSign; // logical shift
            s.si = mulN;
            s.si = s.f * v.f; // correct subnormals
            v.si ^= (s.si ^ v.si) & -(minN > v.si);
            v.si ^= (infN ^ v.si) & -((infN > v.si) & (v.si > maxN));
            v.si ^= (nanN ^ v.si) & -((nanN > v.si) & (v.si > infN));
            v.ui >>= shift; // logical shift
            v.si ^= ((v.si - maxD) ^ v.si) & -(v.si > maxC);
            v.si ^= ((v.si - minD) ^ v.si) & -(v.si > subC);
            return static_cast<UInt16>(v.ui | sign);
        }

        UGE_FORCE_INLINE static Float decompress(uint16_t value)
        {
            Bits v;
            v.ui = value;
            int32_t sign = v.si & signC;
            v.si ^= sign;
            sign <<= shiftSign;
            v.si ^= ((v.si + minD) ^ v.si) & -(v.si > subC);
            v.si ^= ((v.si + maxD) ^ v.si) & -(v.si > maxC);
            Bits s;
            s.si = mulC;
            s.f *= v.si;
            int32_t mask = -(norC > v.si);
            v.si <<= shift;
            v.si ^= (s.si ^ v.si) & mask;
            v.si |= sign;
            return v.f;
        }
    };

    struct Half
    {
        union
        {
            struct
            {
                UInt16 mantissa : 10;
                UInt16 exponent : 5;
                UInt16 sign : 1;
            } components;
            UInt16 value;
        };

        Half() = default;
        Half(const Half &other);
        Half(const UInt16 other);
        explicit Half(const Float x);

        Float ToFloat() const;
        operator Float() const
        {
            return ToFloat();
        }
        Half &operator=(const Half &other);
        Bool operator==(const Half &other) const;
    };
    
    struct Half2
    {
        union
        {
            struct
            {
                Half x;
                Half y;
            };
            Half components[2];
        };

        Half2() = default;
        Half2(const Half2 &other);
        Half2(const Half x, const Half y);
        Half2(const Float x, const Float y);
        Half2(const Float f[2]);
        explicit Half2(const Float f);

        Half2 &operator=(const Half2 &other);
        Bool operator==(const Half2 &other) const;
        Bool operator!=(const Half2 &other) const;

        Half &operator[](const size_t i);
        const Half &operator[](const size_t i) const;

        Vec2 ToVec2() const;
    };

    struct Half3
    {
        union
        {
            struct
            {
                Half x;
                Half y;
                Half z;
            };
            Half components[3];
        };

        Half3() = default;
        Half3(const Half3 &other);
        Half3(const Half x, const Half y, const Half z);
        Half3(const Float x, const Float y, const Float z);
        Half3(const Float f[3]);
        explicit Half3(const Float f);

        Half3 &operator=(const Half3 &other);
        Bool operator==(const Half3 &other) const;
        Bool operator!=(const Half3 &other) const;

        Half &operator[](const size_t i);
        const Half &operator[](const size_t i) const;

        Vec3 ToVec3() const;
    };

    struct Half4
    {
        union
        {
            struct
            {
                Half x;
                Half y;
                Half z;
                Half w;
            };
            Half components[4];
        };

        Half4() = default;
        Half4(const Half4 &other);
        Half4(const Half x, const Half y, const Half z, const Half w);
        Half4(const Float x, const Float y, const Float z, const Float w);
        Half4(const Float f[4]);
        explicit Half4(const Float f);

        Half4 &operator=(const Half4 &other);
        Bool operator==(const Half4 &other) const;
        Bool operator!=(const Half4 &other) const;

        Half &operator[](const size_t i);
        const Half &operator[](const size_t i) const;

        Vec4 ToVec4() const;
    };
}

#endif // __COREMATH_FLOAT16_H__