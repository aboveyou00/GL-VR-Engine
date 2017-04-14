#include "stdafx.h"
#include "CubeSpatialPartitions.h"
#include "GameObject.h"
#include "MathUtils.h"
#include "ScopedLock.h"

namespace GlEngine
{
    CubeSpatialPartitions::CubeSpatialPartitions(Vector<3> partitionSize)
        : SpatialPartitions(), partitionSize(partitionSize), xMin(0), xMax(0), yMin(0), yMax(0), zMin(0), zMax(0)
    {
    }

    CubeSpatialPartitions::~CubeSpatialPartitions()
    {
    }

    void CubeSpatialPartitions::AddMesh(MeshComponent* mesh)
    {
        auto pos = mesh->gameObject()->globalTransform()->position();
        int left   = Util::floor_int((pos[0] + mesh->leftBound)   / partitionSize[0]);
        int right  = Util::floor_int((pos[0] + mesh->rightBound)  / partitionSize[0]);
        int top    = Util::floor_int((pos[0] + mesh->topBound)    / partitionSize[1]);
        int bottom = Util::floor_int((pos[0] + mesh->bottomBound) / partitionSize[1]);
        int back   = Util::floor_int((pos[0] + mesh->backBound)   / partitionSize[2]);
        int front  = Util::floor_int((pos[0] + mesh->frontBound)  / partitionSize[2]);

        meshBounds[mesh] = Vector<6, int>(left, right, top, bottom, back, front);

        for (int x = left; x <= right; x++)
            for (int y = top; y <= bottom; y++)
                for (int z = back; z <= front; z++)
                    AddMeshToPartition(x, y, z, mesh);
    }
    void CubeSpatialPartitions::RemoveMesh(MeshComponent* mesh)
    {
        auto pos = mesh->gameObject()->globalTransform()->position();
        int left   = Util::floor_int((pos[0] + mesh->leftBound)   / partitionSize[0]);
        int right  = Util::floor_int((pos[0] + mesh->rightBound)  / partitionSize[0]);
        int top    = Util::floor_int((pos[0] + mesh->topBound)    / partitionSize[1]);
        int bottom = Util::floor_int((pos[0] + mesh->bottomBound) / partitionSize[1]);
        int back   = Util::floor_int((pos[0] + mesh->backBound)   / partitionSize[2]);
        int front  = Util::floor_int((pos[0] + mesh->frontBound)  / partitionSize[2]);

        meshBounds.erase(mesh);

        for (int x = left; x <= right; x++)
            for (int y = top; y <= bottom; y++)
                for (int z = back; z <= front; z++)
                    RemoveMeshFromPartition(x, y, z, mesh);
    }
    void CubeSpatialPartitions::UpdateMesh(MeshComponent* mesh)
    {
        auto oldMeshBounds = meshBounds[mesh];
        int oldLeft   = oldMeshBounds[0];
        int oldRight  = oldMeshBounds[1];
        int oldTop    = oldMeshBounds[2];
        int oldBottom = oldMeshBounds[3];
        int oldBack   = oldMeshBounds[4];
        int oldFront  = oldMeshBounds[5];

        auto pos = mesh->gameObject()->globalTransform()->position();
        int left = Util::floor_int((pos[0] + mesh->leftBound) / partitionSize[0]);
        int right = Util::floor_int((pos[0] + mesh->rightBound) / partitionSize[0]);
        int top = Util::floor_int((pos[0] + mesh->topBound) / partitionSize[1]);
        int bottom = Util::floor_int((pos[0] + mesh->bottomBound) / partitionSize[1]);
        int back = Util::floor_int((pos[0] + mesh->backBound) / partitionSize[2]);
        int front = Util::floor_int((pos[0] + mesh->frontBound) / partitionSize[2]);

        for (int x = left; x <= right; x++)
        {
            for (int y = top; y <= bottom; y++)
            {
                for (int z = back; z <= front; z++)
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
                    if (left <= x && x <= right && top <= y && y <= bottom && back <= z && z <= front)
                        continue;
                    RemoveMeshFromPartition(x, y, z, mesh);
                }
            }
        }
    }

    MeshComponent* CubeSpatialPartitions::RayCast(Ray ray, float* outDistance)
    {
        if (ray.direction == Vector<3>{0, 0, 0})
            return nullptr;

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

        while (
            ((ray.direction[0] < 0 && x >= xMin) || (ray.direction[0] >= 0 && x <= xMax)) &&
            ((ray.direction[1] < 0 && y >= yMin) || (ray.direction[1] >= 0 && y <= yMax)) &&
            ((ray.direction[2] < 0 && z >= zMin) || (ray.direction[2] >= 0 && z <= zMax)) )
        {
            MeshComponent* result = RayCastPartition(x, y, z, ray, outDistance);
            if (result)
                return result;

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
        return nullptr;
    }

    void CubeSpatialPartitions::AddMeshToPartition(int x, int y, int z, MeshComponent* mesh)
    {
        ScopedLock _lock(partitionsLock);

        Vector<3> key = { x, y, z };
        if (!partitions.count(key) || partitions[key] == nullptr)
            partitions[key] = new std::unordered_set<MeshComponent*>();
        partitions[key]->insert(mesh);

        xMin = min(xMin, x); xMax = max(xMax, x);
        yMin = min(yMin, y); yMax = max(yMax, y);
        zMin = min(zMin, z); zMax = max(zMax, z);
    }

    void CubeSpatialPartitions::RemoveMeshFromPartition(int x, int y, int z, MeshComponent * mesh)
    {
        ScopedLock _lock(partitionsLock);

        Vector<3> key = { x, y, z };
        partitions[key]->erase(mesh);
    }
    
    MeshComponent* CubeSpatialPartitions::RayCastPartition(int x, int y, int z, Ray ray, float * outDistance)
    {
        ScopedLock _lock(partitionsLock);

        MeshComponent* result = nullptr;
        float resultDistance = 0;
        float distance;

        auto meshSet = partitions[{ x, y, z }];
        if (meshSet == nullptr)
            return nullptr;

        for (MeshComponent* mesh : *meshSet)
        {
            if (raycastChecked.count(mesh))
                continue;
            raycastChecked.insert(mesh);

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
}

