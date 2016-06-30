#pragma once

namespace GlEngine
{
    enum class VboType : unsigned
    {
        Float = 0x1406,
        Double = 0x140A,
        Int = 0x1404,
        UnsignedInt = 0x1405,

        Byte = 0x1400,
        UnsignedByte = 0x1401,
        Short = 0x1402,
        UnsignedShort = 0x1403
    };

    template <VboType type>
    struct vbo_type_attribs
    {
        typedef void type;
    };

    template <>
    struct vbo_type_attribs<VboType::Float>
    {
        typedef float type;
    };
    template <>
    struct vbo_type_attribs<VboType::Double>
    {
        typedef double type;
    };
    template <>
    struct vbo_type_attribs<VboType::Int>
    {
        typedef int32_t type;
    };
    template <>
    struct vbo_type_attribs<VboType::UnsignedInt>
    {
        typedef uint32_t type;
    };

    template <>
    struct vbo_type_attribs<VboType::Byte>
    {
        typedef int8_t type;
    };
    template <>
    struct vbo_type_attribs<VboType::UnsignedByte>
    {
        typedef uint8_t type;
    };
    template <>
    struct vbo_type_attribs<VboType::Short>
    {
        typedef int16_t type;
    };
    template <>
    struct vbo_type_attribs<VboType::UnsignedShort>
    {
        typedef uint16_t type;
    };

}
