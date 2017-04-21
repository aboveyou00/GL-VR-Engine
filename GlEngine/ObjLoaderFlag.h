#pragma once

namespace GlEngine
{
    enum class ENGINE_SHARED ObjLoaderFlag
    {
        None = 0b0000,
        Mesh = 0b0001,
        Material = 0b0010,
        Graphics = 0b0100
    };
}
