#include "stdafx.h"
#include "Octree.h"
#include "ScopedLock.h"
#include "StringUtils.h"

namespace GlEngine
{
    Octree::Octree(float minX, float maxX, float minY, float maxY, float minZ, float maxZ, unsigned maxDepth, unsigned leafCapacity)
        : _minX(minX), _maxX(maxX), _minY(minY), _maxY(maxY), _minZ(minZ), _maxZ(maxZ),
        _centerX((minX + maxX) / 2), _centerY((minY + maxY) / 2), _centerZ((minZ + maxZ) / 2),
        maxDepth(maxDepth), leafCapacity(leafCapacity), _isLeaf(true), _parent(nullptr)
    {
        for (int i = 0; i < 8; i++)
            children[i] = nullptr;
    }
    Octree::~Octree()
    {
        for (int i = 0; i < 8; i++)
        {
            if (children[i] != nullptr)
                delete children[i];
        }
    }

    Octree * Octree::child(bool x, bool y, bool z)
    {
        return children[x * 0b100 + y * 0b010 + z * 0b001];
    }

    Octree * Octree::child(int idx)
    {
        return children[idx];
    }

    void Octree::Add(MeshTriangle* element)
    {
        ScopedLock _lock(elementsLock);

        if (_isLeaf)
        {
            AddToSelf(element);
        }
        else
        {
            AddToChildren(element);
        }
    }

    void Octree::Remove(MeshTriangle* element)
    {
        element;
        assert(false); // Not implemented
    }

    void Octree::AddToSelf(MeshTriangle* element)
    {
        elements.insert(element);
        if (maxDepth > 1 && elements.size() > leafCapacity)
            Split();
    }

    void Octree::AddToChildren(MeshTriangle* element)
    {
        bool x_lower = element->minX() < this->centerX();
        bool x_higher = element->maxX() > this->centerX();
        bool y_lower = element->minY() < this->centerY();
        bool y_higher = element->maxY() > this->centerY();
        bool z_lower = element->minZ() < this->centerZ();
        bool z_higher = element->maxZ() > this->centerZ();

        if (x_lower)
        {
            if (y_lower)
            {
                if (z_lower)
                    AddToChild(0b000, element);
                if (z_higher)
                    AddToChild(0b001, element);
            }
            if (y_higher)
            {
                if (z_lower)
                    AddToChild(0b010, element);
                if (z_higher)
                    AddToChild(0b011, element);
            }
        }
        if (x_higher)
        {
            if (y_lower)
            {
                if (z_lower)
                    AddToChild(0b100, element);
                if (z_higher)
                    AddToChild(0b101, element);
            }
            if (y_higher)
            {
                if (z_lower)
                    AddToChild(0b110, element);
                if (z_higher)
                    AddToChild(0b111, element);
            }
        }
    }

    void Octree::AddToChild(int idx, MeshTriangle* element)
    {
        child(idx)->Add(element);
    }

    void Octree::Split()
    {
        _isLeaf = false;
        for (int i = 0; i < 8; i++)
            CreateChild(i);
        for (MeshTriangle* element : elements)
            AddToChildren(element);
        elements.clear();
    }

    Octree * Octree::neighborX(bool pos)
    {
        return neighborDim(pos, 0b100);
    }

    Octree * Octree::neighborY(bool pos)
    {
        return neighborDim(pos, 0b010);
    }

    Octree * Octree::neighborZ(bool pos)
    {
        return neighborDim(pos, 0b001);
    }

#ifdef _DEBUG
    std::string Octree::debugString()
    {
        int* depths = depthLeafCounts();
        auto sizes = leafSizes();

        std::string depthString = "";
        for (size_t i = 0; i < maxDepth; i++)
        {
            depthString += Util::formatted("%d buckets %d levels deep; ", depths[i], i);
        }

        int totalSize = 0;
        int maxSize = 0;
        for (int size : sizes)
        {
            totalSize += size;
            maxSize = max(maxSize, size);
        }
        double avgSize = (double)totalSize / sizes.size();

        return Util::formatted("octree (x: %.3f - %.3f, y: %.3f - %.3f, z: %.3f - %.3f, maxDepth: %ud, leafCapacity: %ud)\n%s\nAvg tris in bucket: %.3f; Max tris in bucket: %d",
                               _minX, _maxX, _minY, _maxY, _minZ, _maxZ, maxDepth, leafCapacity, depthString.c_str(), avgSize, maxSize);
    }

    int* Octree::depthLeafCounts()
    {
        ScopedLock _lock(elementsLock);

        int* result = new int[256];
        for (int i = 0; i < 256; i++)
            result[i] = 0;

        if (!_isLeaf)
        {
            for (int i = 0; i < 8; i++)
            {
                int* childResult = child(i)->depthLeafCounts();
                for (int j = 1; j < 256; j++)
                    result[j] += childResult[j - 1];
                delete[] childResult;
            }
        }
        result[0] += 1;
        return result;
    }

    std::vector<int> Octree::leafSizes()
    {
        ScopedLock _lock(elementsLock);

        std::vector<int> result;
        if (_isLeaf)
        {
            result.push_back(elements.size());
        }
        else
        {
            for (int i = 0; i < 8; i++)
            {
                auto childResult = child(i)->leafSizes();
                result.insert(result.begin(), childResult.begin(), childResult.end());
            }
        }
        return result;
    }

#endif

    Octree * Octree::neighborDim(bool pos, int dim)
    {
        if (_parent == nullptr)
            return nullptr;

        if (!!(_parentIndex & dim) == pos) // out of parent bounds
        {
            Octree* neighborParent = _parent->neighborDim(pos, dim);
            if (neighborParent == nullptr || neighborParent->_isLeaf)
                return neighborParent;
            return neighborParent->child(_parentIndex ^ dim); // flip in dim
        }
        else
        {
            return _parent->child(_parentIndex ^ dim); // flip in dim
        }
    }

    void Octree::CreateChild(int idx)
    {
        float newMinX, newMaxX, newMinY, newMaxY, newMinZ, newMaxZ;

        /* X */
        if ((idx & 4) == 0)
        {
            newMinX = _minX;
            newMaxX = _centerX;
        }
        else
        {
            newMinX = _centerX;
            newMaxX = _maxX;
        }

        /* Y */
        if ((idx & 2) == 0)
        {
            newMinY = _minY;
            newMaxY = _centerY;
        }
        else
        {
            newMinY = _centerY;
            newMaxY = _maxY;
        }

        /* Z */
        if ((idx & 1) == 0)
        {
            newMinZ = _minZ;
            newMaxZ = _centerZ;
        }
        else
        {
            newMinZ = _centerZ;
            newMaxZ = _maxZ;
        }

        children[idx] = new Octree(newMinX, newMaxX, newMinY, newMaxY, newMinZ, newMaxZ, maxDepth - 1, leafCapacity);
        children[idx]->_parent = this;
        children[idx]->_parentIndex = idx;
    }
}
