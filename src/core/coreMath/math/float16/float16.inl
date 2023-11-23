#ifndef __COREMATH_FLOAT16_INL__
#define __COREMATH_FLOAT16_INL__

namespace uge::math
{
    UGE_FORCE_INLINE Half::Half(const Half& other)
        : value(other.value)
    {
    }

    UGE_FORCE_INLINE Half::Half(const UInt16 other)
        : value(other)
    {
    }

    UGE_FORCE_INLINE Half::Half(const Float x)
    {
        value = Float16Compressor::compress(x);
    }
    
    UGE_FORCE_INLINE Float Half::ToFloat() const
    {
        return Float16Compressor::decompress(value);
    }

    UGE_FORCE_INLINE Half& Half::operator=(const Half& other)
    {
        value = other.value;
        return *this;
    }

    UGE_FORCE_INLINE Bool Half::operator==(const Half& other) const
    {
        return value == other.value;
    }

    UGE_FORCE_INLINE Half2::Half2(const Half2& other)
        : x(other.x), y(other.y)
    {
    }

    UGE_FORCE_INLINE Half2::Half2(const Half x, const Half y)
        : x(x), y(y)
    {
    }

    UGE_FORCE_INLINE Half2::Half2(const Float x, const Float y)
    {
        components[0] = Float16Compressor::compress(x);
        components[1] = Float16Compressor::compress(y);
    }

    UGE_FORCE_INLINE Half2::Half2(const Float f[2])
    {
        components[0] = Float16Compressor::compress(f[0]);
        components[1] = Float16Compressor::compress(f[1]);
    }

    UGE_FORCE_INLINE Half2::Half2(const Float f)
    {
        components[0] = Float16Compressor::compress(f);
        components[1] = Float16Compressor::compress(f);
    }

    UGE_FORCE_INLINE Half2& Half2::operator=(const Half2& other)
    {
        x = other.x;
        y = other.y;
        return *this;
    }

    UGE_FORCE_INLINE Bool Half2::operator==(const Half2& other) const
    {
        return x == other.x && y == other.y;
    }

    UGE_FORCE_INLINE Bool Half2::operator!=(const Half2& other) const
    {
        return x != other.x || y != other.y;
    }

    UGE_FORCE_INLINE Half& Half2::operator[](const size_t i)
    {
        UGE_ASSERT(i < 2, "Index out of bounds");
        return components[i];
    }

    UGE_FORCE_INLINE const Half& Half2::operator[](const size_t i) const
    {
        UGE_ASSERT(i < 2, "Index out of bounds");
        return components[i];
    }

    UGE_FORCE_INLINE Vec2 Half2::ToVec2() const
    {
        return Vec2(x.ToFloat(), y.ToFloat());
    }

    UGE_FORCE_INLINE Half3::Half3(const Half3& other)
        : x(other.x), y(other.y), z(other.z)
    {
    }

    UGE_FORCE_INLINE Half3::Half3(const Half x, const Half y, const Half z)
        : x(x), y(y), z(z)
    {
    }

    UGE_FORCE_INLINE Half3::Half3(const Float x, const Float y, const Float z)
    {
        components[0] = Float16Compressor::compress(x);
        components[1] = Float16Compressor::compress(y);
        components[2] = Float16Compressor::compress(z);
    }

    UGE_FORCE_INLINE Half3::Half3(const Float f[3])
    {
        components[0] = Float16Compressor::compress(f[0]);
        components[1] = Float16Compressor::compress(f[1]);
        components[2] = Float16Compressor::compress(f[2]);
    }

    UGE_FORCE_INLINE Half3::Half3(const Float f)
    {
        components[0] = Float16Compressor::compress(f);
        components[1] = Float16Compressor::compress(f);
        components[2] = Float16Compressor::compress(f);
    }

    UGE_FORCE_INLINE Half3& Half3::operator=(const Half3& other)
    {
        x = other.x;
        y = other.y;
        z = other.z;
        return *this;
    }

    UGE_FORCE_INLINE Bool Half3::operator==(const Half3& other) const
    {
        return x == other.x && y == other.y && z == other.z;
    }

    UGE_FORCE_INLINE Bool Half3::operator!=(const Half3& other) const
    {
        return x != other.x || y != other.y || z != other.z;
    }

    UGE_FORCE_INLINE Half& Half3::operator[](const size_t i)
    {
        UGE_ASSERT(i < 3, "Index out of bounds");
        return components[i];
    }

    UGE_FORCE_INLINE const Half& Half3::operator[](const size_t i) const
    {
        UGE_ASSERT(i < 3, "Index out of bounds");
        return components[i];
    }

    UGE_FORCE_INLINE Vec3 Half3::ToVec3() const
    {
        return Vec3(x.ToFloat(), y.ToFloat(), z.ToFloat());
    }

    UGE_FORCE_INLINE Half4::Half4(const Half4& other)
        : x(other.x), y(other.y), z(other.z), w(other.w)
    {
    }

    UGE_FORCE_INLINE Half4::Half4(const Half x, const Half y, const Half z, const Half w)
        : x(x), y(y), z(z), w(w)
    {
    }

    UGE_FORCE_INLINE Half4::Half4(const Float x, const Float y, const Float z, const Float w)
    {
        components[0] = Float16Compressor::compress(x);
        components[1] = Float16Compressor::compress(y);
        components[2] = Float16Compressor::compress(z);
        components[3] = Float16Compressor::compress(w);
    }

    UGE_FORCE_INLINE Half4::Half4(const Float f[4])
    {
        components[0] = Float16Compressor::compress(f[0]);
        components[1] = Float16Compressor::compress(f[1]);
        components[2] = Float16Compressor::compress(f[2]);
        components[3] = Float16Compressor::compress(f[3]);
    }

    UGE_FORCE_INLINE Half4::Half4(const Float f)
    {
        components[0] = Float16Compressor::compress(f);
        components[1] = Float16Compressor::compress(f);
        components[2] = Float16Compressor::compress(f);
        components[3] = Float16Compressor::compress(f);
    }

    UGE_FORCE_INLINE Half4& Half4::operator=(const Half4& other)
    {
        x = other.x;
        y = other.y;
        z = other.z;
        w = other.w;
        return *this;
    }

    UGE_FORCE_INLINE Bool Half4::operator==(const Half4& other) const
    {
        return x == other.x && y == other.y && z == other.z && w == other.w;
    }

    UGE_FORCE_INLINE Bool Half4::operator!=(const Half4& other) const
    {
        return x != other.x || y != other.y || z != other.z || w != other.w;
    }

    UGE_FORCE_INLINE Half& Half4::operator[](const size_t i)
    {
        UGE_ASSERT(i < 4, "Index out of bounds");
        return components[i];
    }

    UGE_FORCE_INLINE const Half& Half4::operator[](const size_t i) const
    {
        UGE_ASSERT(i < 4, "Index out of bounds");
        return components[i];
    }

    UGE_FORCE_INLINE Vec4 Half4::ToVec4() const
    {
        return Vec4(x.ToFloat(), y.ToFloat(), z.ToFloat(), w.ToFloat());
    }
}

#endif // __COREMATH_FLOAT16_INL__