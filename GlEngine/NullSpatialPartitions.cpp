#include "stdafx.h"
#include "NullSpatialPartitions.h"

namespace GlEngine
{
    void NullSpatialPartitions::AddMesh(Mesh* mesh)
    {
        meshes.insert(mesh);
    }

    void NullSpatialPartitions::RemoveMesh(Mesh* mesh)
    {
        meshes.erase(mesh);
    }

    void NullSpatialPartitions::UpdateMesh(Mesh*)
    {
    }

    Mesh* NullSpatialPartitions::RayCast(Ray ray, float* outDistance)
    {
        Mesh* result = nullptr;
        float resultDistance;
        float distance;

        for (Mesh* mesh : meshes)
        {
            if (mesh->RayIntersection(ray, &distance))
            {
                if (result == nullptr || distance < resultDistance)
                {
                    result = mesh;
                    resultDistance = distance;
                }
            }
        }

        if (outDistance != nullptr)
            *outDistance = resultDistance;
        return result;
    }
}