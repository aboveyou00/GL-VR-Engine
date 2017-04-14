#include "stdafx.h"
#include "Octree.h"
#include "ScopedLock.h"

namespace GlEngine
{
    Octree::Octree(float minX, float maxX, float minY, float maxY, float minZ, float maxZ, unsigned maxDepth, unsigned leafCapacity)
        : _minX(minX), _maxX(maxX), _minY(minY), _maxY(maxY), _minZ(minZ), _maxZ(maxZ),
        centerX((minX + maxX) / 2), centerY((minY + maxY) / 2), centerZ((minZ + maxZ) / 2),
        maxDepth(maxDepth), leafCapacity(leafCapacity), _isLeaf(true)
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

    void Octree::Add(IBoundingBox* element)
    {
        if (_isLeaf)
        {
            AddToSelf(element);
        }
        else
        {
            AddToChildren(element);
        }
    }

    void Octree::Remove(IBoundingBox* element)
    {
        element;
        assert(false); // Not implemented
    }

    void Octree::AddToSelf(IBoundingBox* element)
    {
        ScopedLock _lock(elementsLock);

        elements.insert(element);
        if (maxDepth > 1 && elements.size() > leafCapacity)
            Split();
    }

    void Octree::AddToChildren(IBoundingBox* element)
    {
        bool x_lower = element->minX() < this->centerX;
        bool x_higher = element->maxX() > this->centerX;
        bool y_lower = element->minY() < this->centerY;
        bool y_higher = element->maxY() > this->centerY;
        bool z_lower = element->minZ() < this->centerZ;
        bool z_higher = element->maxZ() > this->centerZ;

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

    void Octree::AddToChild(int idx, IBoundingBox* element)
    {
        Octree* child = GetOrCreateChild(idx);
        child->Add(element);
    }

    void Octree::Split()
    {
        _isLeaf = false;
        for (IBoundingBox* element : elements)
            AddToChildren(element);
        elements.clear();
    }

#ifdef _DEBUG
    std::string Octree::debugString(int indent)
    {
        std::string indentStr(indent * 4, ' ');
        std::string childrenStr;
        if (!_isLeaf)
        {
            for (size_t i = 0; i < 8; i++)
            {
                std::string innerStr = children[i] == nullptr ? indentStr + "    EMPTY\n"s : children[i]->debugString(indent + 1);
                std::string childStr = indentStr + "  {"s + ((i & 4) ? "1"s : "0"s) + ", "s + ((i & 2) ? "1"s : "0"s) + ", "s + ((i & 1) ? "1"s : "0"s) + "}\n"s + innerStr;
                childrenStr += childStr;
            }
        }

        char* result = new char[65536];
        sprintf_s(result, 65536, "%soctree (x: %.3f - %.3f, y: %.3f - %.3f, z: %.3f - %.3f, maxDepth: %ud, leafCapacity: %ud)\n%s",
            indentStr.c_str(), _minX, _maxX, _minY, _maxY, _minZ, _maxZ, maxDepth, leafCapacity, childrenStr.c_str());
        std::string resultStr =std::string(result).substr(0, 4096);
        delete[] result;
        return resultStr;
    }
#endif

    Octree* Octree::GetOrCreateChild(int idx)
    {
        if (children[idx] == nullptr)
        {
            float newMinX, newMaxX, newMinY, newMaxY, newMinZ, newMaxZ;

            /* X */
            if ((idx & 4) == 0)
            {
                newMinX = _minX;
                newMaxX = centerX;
            }
            else
            {
                newMinX = centerX;
                newMaxX = _maxX;
            }

            /* Y */
            if ((idx & 2) == 0)
            {
                newMinY = _minY;
                newMaxY = centerY;
            }
            else
            {
                newMinY = centerY;
                newMaxY = _maxY;
            }

            /* Z */
            if ((idx & 1) == 0)
            {
                newMinZ = _minZ;
                newMaxZ = centerZ;
            }
            else
            {
                newMinZ = centerZ;
                newMaxZ = _maxZ;
            }

            children[idx] = new Octree(newMinX, newMaxX, newMinY, newMaxY, newMinZ, newMaxZ, maxDepth - 1, leafCapacity);
        }
        
        return children[idx];
    }

}

