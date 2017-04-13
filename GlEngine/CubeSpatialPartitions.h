#pragma once

#include "SpatialPartitions.h"

namespace GlEngine
{
    class ENGINE_SHARED CubeSpatialPartitions : public SpatialPartitions
    {
    public:
        CubeSpatialPartitions(GameComponent* component);
        ~CubeSpatialPartitions();

        virtual void AddMesh(MeshComponent* mesh) override;
        virtual void RemoveMesh(MeshComponent* mesh) override;
        virtual void UpdateMesh(MeshComponent* mesh) override;

        virtual MeshComponent * RayCast(Ray ray, float* outDistance = nullptr) override;
    };
}