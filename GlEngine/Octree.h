#pragma once

#include <unordered_set>
#include "IBoundingBox.h"

namespace GlEngine
{
    class ENGINE_SHARED Octree : public IBoundingBox
    {
    public:
        Octree(float minX, float maxX, float minY, float maxY, float minZ, float maxZ, unsigned maxDepth, unsigned leafCapacity);
        ~Octree();

        inline bool isLeaf() { return _isLeaf; }

        Octree* child(bool x, bool y, bool z);
        Octree* child(int idx);

        void Add(IBoundingBox* element);
        void Remove(IBoundingBox* element);

        virtual inline float minX() override { return _minX; }
        virtual inline float maxX() override { return _maxX; }
        virtual inline float minY() override { return _minY; }
        virtual inline float maxY() override { return _maxY; }
        virtual inline float minZ() override { return _minZ; }
        virtual inline float maxZ() override { return _maxZ; }

#ifdef _DEBUG
        std::string debugString(int indent = 0);
#endif

    private:
        bool _isLeaf;
        std::unordered_set<IBoundingBox*> elements;
        Octree* children[8]; // xyz xyZ xYz xYZ Xyz XyZ XYz XYZ

        std::recursive_timed_mutex elementsLock;

        Octree* GetOrCreateChild(int idx);
        
        void AddToSelf(IBoundingBox* element);
        void AddToChildren(IBoundingBox* element);
        void AddToChild(int idx, IBoundingBox* element);
        void Split();

        float _minX, _maxX, _minY, _maxY, _minZ, _maxZ;
        float centerX, centerY, centerZ;
        unsigned maxDepth;
        unsigned leafCapacity;
    };
}
