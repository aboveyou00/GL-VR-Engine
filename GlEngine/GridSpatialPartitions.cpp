#include "stdafx.h"
#include "GridSpatialPartitions.h"
#include "GameObject.h"
#include "MathUtils.h"
#include "ScopedLock.h"

namespace GlEngine
{
    GridSpatialPartitions::GridSpatialPartitions(Vector<3> partitionSize)
        : SpatialPartitions(), partitionSize(partitionSize), xMin(0), xMax(0), yMin(0), yMax(0), zMin(0), zMax(0)
    {
    }

    GridSpatialPartitions::~GridSpatialPartitions()
    {
    }

    void GridSpatialPartitions::AddMesh(MeshComponent* mesh)
    {
        auto pos = mesh->gameObject()->globalTransform()->position();
        int left   = Util::floor_int((pos[0] + mesh->minX()) / partitionSize[0]);
        int right  = Util::floor_int((pos[0] + mesh->maxX()) / partitionSize[0]);
        int top    = Util::floor_int((pos[0] + mesh->minY()) / partitionSize[1]);
        int bottom = Util::floor_int((pos[0] + mesh->maxY()) / partitionSize[1]);
        int back   = Util::floor_int((pos[0] + mesh->minZ()) / partitionSize[2]);
        int front  = Util::floor_int((pos[0] + mesh->maxZ()) / partitionSize[2]);

        meshBounds[mesh] = Vector<6, int>(left, right, top, bottom, back, front);

        for (int x = left; x <= right; x++)
            for (int y = top; y <= bottom; y++)
                for (int z = back; z <= front; z++)
                    AddMeshToPartition(x, y, z, mesh);
    }
    void GridSpatialPartitions::RemoveMesh(MeshComponent* mesh)
    {
        auto pos = mesh->gameObject()->globalTransform()->position();
        int left   = Util::floor_int((pos[0] + mesh->minX()) / partitionSize[0]);
        int right  = Util::floor_int((pos[0] + mesh->maxX()) / partitionSize[0]);
        int top    = Util::floor_int((pos[0] + mesh->minY()) / partitionSize[1]);
        int bottom = Util::floor_int((pos[0] + mesh->maxY()) / partitionSize[1]);
        int back   = Util::floor_int((pos[0] + mesh->minZ()) / partitionSize[2]);
        int front  = Util::floor_int((pos[0] + mesh->maxZ()) / partitionSize[2]);

        meshBounds.erase(mesh);

        for (int x = left; x <= right; x++)
            for (int y = top; y <= bottom; y++)
                for (int z = back; z <= front; z++)
                    RemoveMeshFromPartition(x, y, z, mesh);
    }
    void GridSpatialPartitions::UpdateMesh(MeshComponent* mesh)
    {
        auto oldMeshBounds = meshBounds[mesh];
        int oldLeft   = oldMeshBounds[0];
        int oldRight  = oldMeshBounds[1];
        int oldTop    = oldMeshBounds[2];
        int oldBottom = oldMeshBounds[3];
        int oldBack   = oldMeshBounds[4];
        int oldFront  = oldMeshBounds[5];

        auto pos = mesh->gameObject()->globalTransform()->position();
        int minX = Util::floor_int((pos[0] + mesh->minX()) / partitionSize[0]);
        int maxX = Util::floor_int((pos[0] + mesh->maxX()) / partitionSize[0]);
        int minY = Util::floor_int((pos[0] + mesh->minY()) / partitionSize[1]);
        int maxY = Util::floor_int((pos[0] + mesh->maxY()) / partitionSize[1]);
        int minZ = Util::floor_int((pos[0] + mesh->minZ()) / partitionSize[2]);
        int maxZ = Util::floor_int((pos[0] + mesh->maxZ()) / partitionSize[2]);

        meshBounds[mesh] = Vector<6, int>(minX, maxX, minY, maxY, minZ, maxZ);

        for (int x = minX; x <= maxX; x++)
        {
            for (int y = minY; y <= maxY; y++)
            {
                for (int z = minZ; z <= maxZ; z++)
                {
                    if (oldLeft <= x && x <= oldRight && oldTop <= y && y <= oldBottom && oldBack <= z && z <= oldFront)
                        continue;
                    AddMeshToPartition(x, y, z, mesh);
                }
            }
        }

        for (int x = oldLeft; x <= oldRight; x++)
        {
            for (int y = oldTop; y <= oldBottom; y++)
            {
                for (int z = oldBack; z <= oldFront; z++)
                {
                    if (minX <= x && x <= maxX && minY <= y && y <= maxY && minZ <= z && z <= maxZ)
                        continue;
                    RemoveMeshFromPartition(x, y, z, mesh);
                }
            }
        }
    }

    void GridSpatialPartitions::AddStaticMesh(MeshComponent* mesh)
    {
        auto pos = mesh->gameObject()->globalTransform()->position();
        int minX = Util::floor_int((pos[0] + mesh->minX()) / partitionSize[0]);
        int maxX = Util::floor_int((pos[0] + mesh->maxX()) / partitionSize[0]);
        int minY = Util::floor_int((pos[1] + mesh->minY()) / partitionSize[1]);
        int maxY = Util::floor_int((pos[1] + mesh->maxY()) / partitionSize[1]);
        int minZ = Util::floor_int((pos[2] + mesh->minZ()) / partitionSize[2]);
        int maxZ = Util::floor_int((pos[2] + mesh->maxZ()) / partitionSize[2]);

        for (int x = minX; x <= maxX; x++)
        {
            for (int y = minY; y <= maxY; y++)
            {
                for (int z = minZ; z <= maxZ; z++)
                {
                    for (auto triangle : *mesh->allTriangles)
                    {
                        auto transform = mesh->gameObject()->globalTransform()->matrix();
                        auto p0 = transform * (*mesh->vertices)[triangle[0]];
                        auto p1 = transform * (*mesh->vertices)[triangle[1]];
                        auto p2 = transform * (*mesh->vertices)[triangle[2]];

                        if (Util::triangleAABBIntersection(
                            p0, p1, p2,
                            {x * partitionSize[0], y * partitionSize[1], z * partitionSize[2]},
                            partitionSize))
                        {
                            AddMeshToPartition(x, y, z, mesh);
                            break;
                        }
                    }
                }
            }
        }
    }

    MeshComponent* GridSpatialPartitions::RayCast(Ray ray, float* outDistance)
    {
        if (ray.direction == Vector<3>{0, 0, 0})
            return nullptr;

#if _DEBUG
        meshesChecked = 0;
#endif

        raycastChecked.clear();

        int x = Util::floor_int(ray.origin[0] / partitionSize[0]);
        int y = Util::floor_int(ray.origin[1] / partitionSize[1]);
        int z = Util::floor_int(ray.origin[2] / partitionSize[2]);

        float xStep = partitionSize[0] / ray.direction[0];
        float yStep = partitionSize[1] / ray.direction[1];
        float zStep = partitionSize[2] / ray.direction[2];

        float xNext = ((ray.direction[0] < 0 ? x : x + 1) * partitionSize[0] - ray.origin[0]) / ray.direction[0];
        float yNext = ((ray.direction[1] < 0 ? y : y + 1) * partitionSize[1] - ray.origin[1]) / ray.direction[1];
        float zNext = ((ray.direction[2] < 0 ? z : z + 1) * partitionSize[2] - ray.origin[2]) / ray.direction[2];
        
        xNext = abs(xNext); yNext = abs(yNext); zNext = abs(zNext);
        xStep = abs(xStep); yStep = abs(yStep); zStep = abs(zStep);

        MeshComponent* result = nullptr;
        float distance = 0, currentDistance;

        while (
            ((ray.direction[0] < 0 && x >= xMin) || (ray.direction[0] >= 0 && x <= xMax)) &&
            ((ray.direction[1] < 0 && y >= yMin) || (ray.direction[1] >= 0 && y <= yMax)) &&
            ((ray.direction[2] < 0 && z >= zMin) || (ray.direction[2] >= 0 && z <= zMax)) )
        {
            MeshComponent* currentResult = RayCastPartition(x, y, z, ray, &currentDistance);
            if (currentResult && (result == nullptr || currentDistance < distance))
            {
                result = currentResult;
                distance = currentDistance;
                if (currentDistance < xNext && currentDistance < yNext && currentDistance < zNext)
                    break;
            }

            if (xNext < yNext)
            {
                if (xNext < zNext)
                {
                    x += (ray.direction[0] > 0 ? 1 : -1);
                    xNext += xStep;
                    continue;
                }
            }
            else if (yNext < zNext)
            {
                y += (ray.direction[1] > 0 ? 1 : -1);
                yNext += yStep;
                continue;
            }
            z += (ray.direction[2] > 0 ? 1 : -1);
            zNext += zStep;
        }

        if (result && outDistance)
            *outDistance = distance;
        return result;
    }

    void GridSpatialPartitions::AddMeshToPartition(int x, int y, int z, MeshComponent* mesh)
    {
        ScopedLock _lock(partitionsLock);

        Vector<3, int> key = { x, y, z };
        if (!partitions.count(key) || partitions[key] == nullptr)
            partitions[key] = new std::unordered_set<MeshComponent*>();
        partitions[key]->insert(mesh);

        xMin = min(xMin, x); xMax = max(xMax, x);
        yMin = min(yMin, y); yMax = max(yMax, y);
        zMin = min(zMin, z); zMax = max(zMax, z);
    }

    void GridSpatialPartitions::RemoveMeshFromPartition(int x, int y, int z, MeshComponent * mesh)
    {
        ScopedLock _lock(partitionsLock);

        Vector<3, int> key = { x, y, z };
        partitions[key]->erase(mesh);
    }
    
    MeshComponent* GridSpatialPartitions::RayCastPartition(int x, int y, int z, Ray ray, float * outDistance)
    {
        ScopedLock _lock(partitionsLock);

        MeshComponent* result = nullptr;
        float resultDistance = 0;
        float distance;

        auto meshSet = partitions[Vector<3, int>{ x, y, z }];
        if (meshSet == nullptr)
            return nullptr;

        for (MeshComponent* mesh : *meshSet)
        {
            if (raycastChecked.count(mesh))
                continue;
            raycastChecked.insert(mesh);

#if _DEBUG
            meshesChecked++;
#endif

            if (mesh->RayIntersection(ray, &distance))
            {
                if (result == nullptr || distance < resultDistance)
                {
                    result = mesh;
                    resultDistance = distance;
                }
            }
        }

        if (outDistance != nullptr)
            *outDistance = resultDistance;
        return result;
    }

#ifdef _DEBUG
    std::string GridSpatialPartitions::debugString(Vector<3> position)
    {
        ScopedLock _lock(partitionsLock);

        Vector<3, int> key = {
            Util::floor_int(position[0] / partitionSize[0]), 
            Util::floor_int(position[1] / partitionSize[1]), 
            Util::floor_int(position[2] / partitionSize[2])
        };
        auto currentMeshes = partitions[key];
        size_t currentBucketSize = currentMeshes == nullptr ? 0 : currentMeshes->size();
        
        unsigned maxBucketSize = 0;
        unsigned totalBucketSize = 0;
        auto bucketCount = 0;
        for (auto meshes : partitions)
        {
            if (meshes.second == nullptr)
                continue;

            bucketCount++;
            size_t bucketSize = meshes.second->size();
            maxBucketSize = max(maxBucketSize, bucketSize);
            totalBucketSize += bucketSize;
        }
        float averageBucketSize = (float)totalBucketSize / bucketCount;

        char* result = new char[256];
        sprintf_s(result, 256, "current bucket {%d, %d, %d} contains %d meshes\n%d buckets with average of %.3f meshes and max of %d meshes\nlast raytrace checked %d meshes", 
            key[0], key[1], key[2], currentBucketSize, bucketCount, averageBucketSize, maxBucketSize, meshesChecked);

        return std::string(result);
    }
#endif // _DEBUG
}

