#pragma once

#include "MeshComponent.h"
#include "IBoundingBox.h"

namespace GlEngine
{
    struct ENGINE_SHARED MeshTriangle : public IBoundingBox
    {
    public:
        MeshTriangle(MeshComponent* mesh, size_t index);
        ~MeshTriangle();

        MeshComponent* mesh;
        size_t index;

        Vector<3> p0, p1, p2;

        virtual inline float minX() override { return _minX; }
        virtual inline float maxX() override { return _maxX; }
        virtual inline float minY() override { return _minY; }
        virtual inline float maxY() override { return _maxY; }
        virtual inline float minZ() override { return _minZ; }
        virtual inline float maxZ() override { return _maxZ; }

        bool RayIntersection(Ray ray, float* outDistance);
        
    private:
        float _minX, _maxX, _minY, _maxY, _minZ, _maxZ;
    };
}