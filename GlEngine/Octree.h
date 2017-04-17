#pragma once

#include <unordered_set>
#include "MeshTriangle.h"

namespace GlEngine
{
    class ENGINE_SHARED Octree : public IBoundingBox
    {
    public:
        Octree(float minX, float maxX, float minY, float maxY, float minZ, float maxZ, unsigned maxDepth, unsigned leafCapacity);
        ~Octree();

        inline bool isLeaf() { return _isLeaf; }
        inline Octree* parent() { return _parent; }
        inline int parentIndex() { return _parentIndex; }

        Octree* child(bool x, bool y, bool z);
        Octree* child(int idx);

        void Add(MeshTriangle* element);
        void Remove(MeshTriangle* element);

        virtual inline float minX() override { return _minX; }
        virtual inline float maxX() override { return _maxX; }
        virtual inline float minY() override { return _minY; }
        virtual inline float maxY() override { return _maxY; }
        virtual inline float minZ() override { return _minZ; }
        virtual inline float maxZ() override { return _maxZ; }

        virtual inline float centerX() { return _centerX; }
        virtual inline float centerY() { return _centerY; }
        virtual inline float centerZ() { return _centerZ; }

        Octree* neighborX(bool pos);
        Octree* neighborY(bool pos);
        Octree* neighborZ(bool pos);
            
        std::unordered_set<MeshTriangle*> elements;
        std::recursive_timed_mutex elementsLock;

#ifdef _DEBUG
        std::string debugString();
        int* depthLeafCounts();
        std::vector<int> leafSizes();
#endif

    private:
        bool _isLeaf;
        
        Octree* _parent;
        int _parentIndex;

        Octree* children[8]; // xyz xyZ xYz xYZ Xyz XyZ XYz XYZ

        Octree* neighborDim(bool pos, int dim);

        void CreateChild(int idx);
        
        void AddToSelf(MeshTriangle* element);
        void AddToChildren(MeshTriangle* element);
        void AddToChild(int idx, MeshTriangle* element);
        void Split();

        float _minX, _maxX, _minY, _maxY, _minZ, _maxZ;
        float _centerX, _centerY, _centerZ;
        unsigned maxDepth;
        unsigned leafCapacity;
    };
}
