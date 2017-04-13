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

    void CubeSpatialPartitions::AddMesh(Mesh* mesh)
    {
    }
    void CubeSpatialPartitions::RemoveMesh(Mesh* mesh)
    {
    }
    void CubeSpatialPartitions::UpdateMesh(Mesh* mesh)
    {
    }

    Mesh* CubeSpatialPartitions::RayCast(Ray ray, float* outDistance)
    {
        return nullptr;
    }
}

