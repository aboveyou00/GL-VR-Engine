#pragma once

#include "SpatialPartitions.h"

namespace GlEngine
{
    class ENGINE_SHARED CubeSpatialPartitions : public SpatialPartitions
    {
    public:
        CubeSpatialPartitions(GameComponent* component);
        ~CubeSpatialPartitions();

        virtual void AddMesh(Mesh* mesh) override;
        virtual void RemoveMesh(Mesh* mesh) override;
        virtual void UpdateMesh(Mesh* mesh) override;

        virtual Mesh * RayCast(Ray ray, float* outDistance = nullptr) override;
    };
}