#pragma once

#include "MeshComponent.h"

namespace GlEngine
{
    class ENGINE_SHARED SpatialPartitions
    {
    public:
        SpatialPartitions();
        ~SpatialPartitions();

        virtual void AddMesh(MeshComponent* mesh) = 0;
        virtual void RemoveMesh(MeshComponent* mesh) = 0;
        virtual void UpdateMesh(MeshComponent* mesh) = 0;

        virtual MeshComponent* RayCast(Ray ray, float* outDistance = nullptr) = 0;
    };
}