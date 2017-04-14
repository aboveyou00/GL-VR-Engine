#pragma once

namespace GlEngine
{
    class IBoundingBox
    {
    public:
        virtual float minX() = 0;
        virtual float maxX() = 0;
        virtual float minY() = 0;
        virtual float maxY() = 0;
        virtual float minZ() = 0;
        virtual float maxZ() = 0;
    };
}