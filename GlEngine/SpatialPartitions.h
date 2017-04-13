#pragma once

#include "MeshComponent.h"
#include "GameComponent.h"

namespace GlEngine
{
    class ENGINE_SHARED SpatialPartitions
    {
    public:
        SpatialPartitions(GameComponent* component);
        ~SpatialPartitions();

        virtual void AddMesh(MeshComponent* mesh) = 0;
        virtual void RemoveMesh(MeshComponent* mesh) = 0;
        virtual void UpdateMesh(MeshComponent* mesh) = 0;

        virtual MeshComponent* RayCast(Ray ray, float* outDistance = nullptr) = 0;

        GameComponent* component;
    };
}