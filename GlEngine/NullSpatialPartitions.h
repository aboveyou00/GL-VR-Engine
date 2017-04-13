#pragma once
#include "SpatialPartitions.h"

#include <set>

namespace GlEngine
{
    class ENGINE_SHARED NullSpatialPartitions : SpatialPartitions
    {
    public:
        virtual void AddMesh(Mesh* mesh) override;
        virtual void RemoveMesh(Mesh* mesh) override;
        virtual void UpdateMesh(Mesh* mesh) override;
        
        virtual Mesh * RayCast(Ray ray, float* outDistance = nullptr) override;

    private:
        std::set<Mesh*> meshes;
    };
}