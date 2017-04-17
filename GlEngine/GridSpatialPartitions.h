#pragma once

#include "SpatialPartitions.h"

#include <unordered_map>
#include <unordered_set>

namespace GlEngine
{
    typedef std::unordered_map<Vector<3, int>, std::unordered_set<MeshComponent*>*> PartitionsMap;

    class ENGINE_SHARED GridSpatialPartitions : public SpatialPartitions
    {
    public:
        GridSpatialPartitions(Vector<3> partitionSize);
        ~GridSpatialPartitions();

        virtual void AddMesh(MeshComponent* mesh) override;
        virtual void RemoveMesh(MeshComponent* mesh) override;
        virtual void UpdateMesh(MeshComponent* mesh) override;

        virtual void AddStaticMesh(MeshComponent* mesh) override;

        virtual MeshComponent* RayCast(Ray ray, float* outDistance = nullptr) override;

#ifdef _DEBUG
        size_t meshesChecked;
        virtual std::string debugString(Vector<3> position) override;
#endif // _DEBUG

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
