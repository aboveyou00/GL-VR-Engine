#include "stdafx.h"
#include "OctreeSpatialPartitions.h"
#include "MeshTriangle.h"

namespace GlEngine
{
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
        Octree* currentLeaf = &octree;
        while (!currentLeaf->isLeaf())
        {
            currentLeaf = currentLeaf->child(ray.origin[0] > currentLeaf->centerX(), ray.origin[1] > currentLeaf->centerY(), ray.origin[2] > currentLeaf->centerZ());
        }

        float xDist = (ray.direction[0] < 0 ? currentLeaf->minX() : currentLeaf->maxX()) - ray.origin[0];
        float yDist = (ray.direction[1] < 0 ? currentLeaf->minY() : currentLeaf->maxY()) - ray.origin[1];
        float zDist = (ray.direction[2] < 0 ? currentLeaf->minZ() : currentLeaf->maxZ()) - ray.origin[2];

        float xNext = xDist / ray.direction[0];
        float yNext = yDist / ray.direction[1];
        float zNext = zDist / ray.direction[2];

        float dist = 0;

        while (true)
        {
            MeshComponent* result = RayCastPartition(currentLeaf, ray, outDistance);
            if (result != nullptr)
                return result;

            if (xNext < yNext)
            {
                if (xNext < zNext)
                {
                    dist = xNext;
                    currentLeaf = currentLeaf->neighborX(ray.direction[0] > 0);
                    goto calcNext;
                }
            }
            else if (yNext < zNext)
            {
                dist = yNext;
                currentLeaf = currentLeaf->neighborY(ray.direction[1] > 0);
                goto calcNext;
            }
            dist = zNext;
            currentLeaf = currentLeaf->neighborZ(ray.direction[2] > 0);

        calcNext:;

            if (currentLeaf == nullptr)
                break;

            auto point = ray.origin + ray.direction * dist;
            while (!currentLeaf->isLeaf())
            {
                currentLeaf = currentLeaf->child(point[0] > currentLeaf->centerX(), point[1] > currentLeaf->centerY(), point[2] > currentLeaf->centerZ());
            }

            xDist = (ray.direction[0] < 0 ? currentLeaf->minX() : currentLeaf->maxX()) - point[0];
            yDist = (ray.direction[1] < 0 ? currentLeaf->minY() : currentLeaf->maxY()) - point[1];
            zDist = (ray.direction[2] < 0 ? currentLeaf->minZ() : currentLeaf->maxZ()) - point[2];

            xNext = dist + xDist / ray.direction[0];
            yNext = dist + yDist / ray.direction[1];
            zNext = dist + zDist / ray.direction[2];
        }
        
        return nullptr;
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
            if (tri->RayIntersection(ray, &distance))
            {
                if (result == nullptr || distance < resultDistance)
                {
                    result = tri->mesh;
                    resultDistance = distance;
                }
            }
        }

        if (outDistance != nullptr)
            *outDistance = resultDistance;
        return result;
    }
}
