#pragma once

#include "SpatialPartitions.h"
#include "Octree.h"

namespace GlEngine
{
    class ENGINE_SHARED OctreeSpatialPartitions : public SpatialPartitions
    {
    public:
        OctreeSpatialPartitions(Vector<3> rootSize, Vector<3> rootOffset, unsigned maxDepth, unsigned leafCapacity);
        ~OctreeSpatialPartitions();

        virtual void AddMesh(MeshComponent* mesh) override;
        virtual void RemoveMesh(MeshComponent* mesh) override;
        virtual void UpdateMesh(MeshComponent* mesh) override;

        virtual void AddStaticMesh(MeshComponent* mesh) override;
        virtual void RemoveStaticMesh(MeshComponent* mesh) override;

        virtual MeshComponent* RayCast(Ray ray, float* outDistance = nullptr) override;

        Vector<3> rootSize();
        Vector<3> rootOffset();
        unsigned maxDepth();
        unsigned leafCapacity();

#ifdef _DEBUG
        virtual std::string debugString(Vector<3> position) override;
#endif // _DEBUG

    private:
        Octree octree;

        MeshComponent* RayCastPartition(Octree* leaf, Ray ray, float* outDistance);

        Vector<3> _rootSize;
        Vector<3> _rootOffset;
        unsigned _maxDepth;
        unsigned _leafCapacity;
    };
}
