#include "stdafx.h"
#include "OctreeSpatialPartitions.h"
#include "MeshTriangle.h"

#pragma warning( push )
#pragma warning( disable : 4127)

namespace GlEngine
{
    const bool OctreeSpatialPartitions::filterDuplicates = false;
    const bool OctreeSpatialPartitions::aggressiveShortCircuit = false;

    OctreeSpatialPartitions::OctreeSpatialPartitions(Vector<3> rootSize, Vector<3> rootOffset, unsigned maxDepth, unsigned leafCapacity)
        : _rootSize(rootSize), _rootOffset(rootOffset), _maxDepth(maxDepth), _leafCapacity(leafCapacity), 
        octree(rootOffset[0] - rootSize[0] / 2, rootOffset[0] + rootSize[0] / 2, 
               rootOffset[1] - rootSize[1] / 2, rootOffset[1] + rootSize[1] / 2, 
               rootOffset[2] - rootSize[2] / 2, rootOffset[2] + rootSize[2] / 2, 
               maxDepth, leafCapacity)
    {
    }
    OctreeSpatialPartitions::~OctreeSpatialPartitions()
    {
    }

    void OctreeSpatialPartitions::AddMesh(MeshComponent* mesh)
    {
        mesh;
        assert(false); // Not supported
    }

    void OctreeSpatialPartitions::RemoveMesh(MeshComponent* mesh)
    {
        mesh;
        assert(false); // Not supported
    }

    void OctreeSpatialPartitions::UpdateMesh(MeshComponent* mesh)
    {
        mesh;
        assert(false); // Not supported
    }

    void OctreeSpatialPartitions::AddStaticMesh(MeshComponent* mesh)
    {
        for (size_t i = 0; i < mesh->allTriangles->size(); i++)
            octree.Add(new MeshTriangle(mesh, i));
    }

    void OctreeSpatialPartitions::RemoveStaticMesh(MeshComponent* mesh)
    {
        //octree.Remove(mesh);
        mesh;
        assert(false); // Not implemented
    }

    MeshComponent* OctreeSpatialPartitions::RayCast(Ray ray, float* outDistance)
    {
        ScopedLock _lock(octree.elementsLock);

        if (filterDuplicates)
            lastRaycastBucket = nullptr;
        
        Octree* currentLeaf = &octree;
        float dist = 0;
        Vector<3> point = ray.origin;

        MeshComponent* result = nullptr;
        float distance = 0;

        while (true)
        {
            if (currentLeaf == nullptr)
                break;

            point = ray.origin + ray.direction * dist;
            while (!currentLeaf->isLeaf())
            {
                currentLeaf = currentLeaf->child(point[0] > currentLeaf->centerX(), point[1] > currentLeaf->centerY(), point[2] > currentLeaf->centerZ());
            }

            float xDist = (ray.direction[0] < 0 ? currentLeaf->minX() : currentLeaf->maxX()) - point[0];
            float yDist = (ray.direction[1] < 0 ? currentLeaf->minY() : currentLeaf->maxY()) - point[1];
            float zDist = (ray.direction[2] < 0 ? currentLeaf->minZ() : currentLeaf->maxZ()) - point[2];

            float xNext = dist + xDist / ray.direction[0];
            float yNext = dist + yDist / ray.direction[1];
            float zNext = dist + zDist / ray.direction[2];

            float currentDistance;
            MeshComponent* currentResult = RayCastPartition(currentLeaf, ray, &currentDistance);
            if (currentResult != nullptr)
            {
                if (aggressiveShortCircuit)
                {
                    result = currentResult;
                    distance = currentDistance;
                    break;
                }
                else
                {
                    if (result == nullptr || currentDistance < distance)
                    {
                        result = currentResult;
                        distance = currentDistance;
                    }
                }
            }

            if (!aggressiveShortCircuit && result != nullptr && distance < xNext && distance < yNext && distance < zNext)
            {
                break;
            }

            if (xNext < yNext)
            {
                if (xNext < zNext)
                {
                    dist = xNext;
                    currentLeaf = currentLeaf->neighborX(ray.direction[0] > 0);
                    continue;
                }
            }
            else if (yNext < zNext)
            {
                dist = yNext;
                currentLeaf = currentLeaf->neighborY(ray.direction[1] > 0);
                continue;
            }
            dist = zNext;
            currentLeaf = currentLeaf->neighborZ(ray.direction[2] > 0);
        }
        
        if (result != nullptr)
            *outDistance = distance;
        return result;
    }

    Vector<3> OctreeSpatialPartitions::rootSize()
    {
        return _rootSize;
    }
    Vector<3> OctreeSpatialPartitions::rootOffset()
    {
        return _rootOffset;
    }
    unsigned OctreeSpatialPartitions::maxDepth()
    {
        return _maxDepth;
    }
    unsigned OctreeSpatialPartitions::leafCapacity()
    {
        return _leafCapacity;
    }

#ifdef _DEBUG
    std::string OctreeSpatialPartitions::debugString(Vector<3> position)
    {
        std::string octreeData = octree.debugString();

        //char* result = new char[256];
        //sprintf_s(result, 256, "current bucket {%d, %d, %d} contains %d meshes\n%d buckets with average of %.3f meshes and max of %d meshes",
        //    key[0], key[1], key[2], currentBucketSize, bucketCount, averageBucketSize, maxBucketSize);

        return octreeData;
    }
#endif // _DEBUG

    MeshComponent * OctreeSpatialPartitions::RayCastPartition(Octree* leaf, Ray ray, float* outDistance)
    {
        ScopedLock _lock(leaf->elementsLock);

        MeshComponent* result = nullptr;
        float resultDistance = 0;
        float distance;

        for (MeshTriangle* tri : leaf->elements)
        {
                if (filterDuplicates && lastRaycastBucket != nullptr && lastRaycastBucket->elements.count(tri))
                    continue;

            if (tri->RayIntersection(ray, &distance))
            {
                if (result == nullptr || distance < resultDistance)
                {
                    result = tri->mesh;
                    resultDistance = distance;
                }
            }
        }
        
        if (filterDuplicates)
            lastRaycastBucket = leaf;

        if (outDistance != nullptr)
            *outDistance = resultDistance;
        return result;
    }
}

#pragma warning( pop ) // 
