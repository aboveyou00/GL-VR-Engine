#include "stdafx.h"
#include "CubeSpatialPartitions.h"

namespace GlEngine
{
    CubeSpatialPartitions::CubeSpatialPartitions(GameComponent* component)
        : SpatialPartitions(component)
    {
    }

    CubeSpatialPartitions::~CubeSpatialPartitions()
    {
    }

    void CubeSpatialPartitions::AddMesh(MeshComponent* mesh)
    {
        mesh;
    }
    void CubeSpatialPartitions::RemoveMesh(MeshComponent* mesh)
    {
        mesh;
    }
    void CubeSpatialPartitions::UpdateMesh(MeshComponent* mesh)
    {
        mesh;
    }

    MeshComponent* CubeSpatialPartitions::RayCast(Ray ray, float* outDistance)
    {
        ray; outDistance;
        return nullptr;
    }
}

