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

#ifdef _DEBUG
        virtual std::string debugString(Vector<3> position);
#endif // _DEBUG
    };
}