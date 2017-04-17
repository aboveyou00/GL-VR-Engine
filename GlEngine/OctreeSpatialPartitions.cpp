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
        octree.Remove(mesh);
    }

    MeshComponent* OctreeSpatialPartitions::RayCast(Ray ray, float* outDistance)
    {
        Octree* currentLeaf = &octree;
        while (!currentLeaf->isLeaf())
        {
            Octree* child = currentLeaf->child(ray.origin[0] > currentLeaf->centerX(), ray.origin[1] > currentLeaf->centerY(), ray.origin[2] > currentLeaf->centerZ());
            if (child == nullptr)
                break;
            currentLeaf = child;
        }

        outDistance;
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
}
