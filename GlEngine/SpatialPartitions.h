#pragma once

#include "Mesh.h"
#include "GameComponent.h"

namespace GlEngine
{
    class ENGINE_SHARED SpatialPartitions
    {
    public:
        SpatialPartitions(GameComponent* component);
        ~SpatialPartitions();

        virtual void AddMesh(Mesh* mesh) = 0;
        virtual void RemoveMesh(Mesh* mesh) = 0;
        virtual void UpdateMesh(Mesh* mesh) = 0;

        virtual Mesh* RayCast(Ray ray, float* outDistance = nullptr) = 0;

        GameComponent* component;
    };
}