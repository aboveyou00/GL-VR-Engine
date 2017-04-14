#include "stdafx.h"
#include "NullSpatialPartitions.h"

namespace GlEngine
{
    void NullSpatialPartitions::AddMesh(MeshComponent* mesh)
    {
        meshes.insert(mesh);
    }

    void NullSpatialPartitions::RemoveMesh(MeshComponent* mesh)
    {
        meshes.erase(mesh);
    }

    void NullSpatialPartitions::UpdateMesh(MeshComponent*)
    {
    }

    MeshComponent* NullSpatialPartitions::RayCast(Ray ray, float* outDistance)
    {
        MeshComponent* result = nullptr;
        float resultDistance = 0;
        float distance;

        for (MeshComponent* mesh : meshes)
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
