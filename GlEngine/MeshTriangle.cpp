#include "stdafx.h"
#include "MeshTriangle.h"
#include "GameObject.h"
#include "MathUtils.h"

namespace GlEngine
{
    MeshTriangle::MeshTriangle(MeshComponent* mesh, size_t index)
        : mesh(mesh), index(index)
    {
        auto transform = mesh->gameObject()->globalTransform()->matrix();

        p0 = transform * (*mesh->vertices)[(*mesh->allTriangles)[index][0]];
        p1 = transform * (*mesh->vertices)[(*mesh->allTriangles)[index][1]];
        p2 = transform * (*mesh->vertices)[(*mesh->allTriangles)[index][2]];

        _minX = min(p0[0], min(p1[0], p2[0]));
        _maxX = max(p0[0], max(p1[0], p2[0]));
        _minY = min(p0[1], min(p1[1], p2[1]));
        _maxY = max(p0[1], max(p1[1], p2[1]));
        _minZ = min(p0[2], min(p1[2], p2[2]));
        _maxZ = max(p0[2], max(p1[2], p2[2]));
    }

    MeshTriangle::~MeshTriangle()
    {
    }

    bool MeshTriangle::RayIntersection(Ray ray, float* outDistance)
    {
        return Util::triangleRayIntersection(p0, p1, p2, ray.origin, ray.direction, outDistance);
    }
}
