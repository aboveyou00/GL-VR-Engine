#pragma once
#include "SpatialPartitions.h"

#include <set>

namespace GlEngine
{
    class ENGINE_SHARED NullSpatialPartitions : SpatialPartitions
    {
    public:
        virtual void AddMesh(MeshComponent* mesh) override;
        virtual void RemoveMesh(MeshComponent* mesh) override;
        virtual void UpdateMesh(MeshComponent* mesh) override;
        
        virtual MeshComponent * RayCast(Ray ray, float* outDistance = nullptr) override;

    private:
        std::set<MeshComponent*> meshes;
    };
}