#pragma once

#include "SpatialPartitions.h"

#include <unordered_map>
#include <unordered_set>

namespace GlEngine
{
    typedef std::unordered_map<Vector<3>, std::unordered_set<MeshComponent*>*> PartitionsMap;

    class ENGINE_SHARED CubeSpatialPartitions : public SpatialPartitions
    {
    public:
        CubeSpatialPartitions(Vector<3> partitionSize);
        ~CubeSpatialPartitions();

        virtual void AddMesh(MeshComponent* mesh) override;
        virtual void RemoveMesh(MeshComponent* mesh) override;
        virtual void UpdateMesh(MeshComponent* mesh) override;

        virtual MeshComponent* RayCast(Ray ray, float* outDistance = nullptr) override;

    private:
        Vector<3> partitionSize;
        PartitionsMap partitions;
        std::recursive_timed_mutex partitionsLock;

        std::unordered_map<MeshComponent*, Vector<6, int>> meshBounds;

        void AddMeshToPartition(int x, int y, int z, MeshComponent* mesh);
        void RemoveMeshFromPartition(int x, int y, int z, MeshComponent* mesh);
        MeshComponent* RayCastPartition(int x, int y, int z, Ray ray, float* outDistance = nullptr);

        int xMin, xMax, yMin, yMax, zMin, zMax;

        std::unordered_set<MeshComponent*> raycastChecked;
    };
}
