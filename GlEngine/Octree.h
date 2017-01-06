#pragma once

namespace GlEngine
{
    template<typename ElemT>
    class ENGINE_SHARED Octree
    {
    public:
        Octree(float minX, float maxX, float minY, float maxY, float minZ, float maxZ, unsigned maxDepth)
            : minX(minX), maxX(maxX), minY(minY), maxY(maxY), minZ(minZ), maxZ(maxZ), centerX((minX + maxX) / 2), centerY((minY + maxY) / 2), centerZ((minZ + maxZ) / 2), maxDepth(maxDepth)
        {
            for (int i = 0; i < maxElements; i++)
                elementsUsed[i] = false;
            _nextAvailableActor = 0;

            for (int i = 0; i < 8; i++)
                subTrees[i] = nullptr;
        }
        ~Octree()
        {
            for (int i = 0; i < 8; i++)
            {
                if (subTrees[i] != nullptr)
                    delete subTrees[i];
            }
        }

        Octree* Add(ElemT* element, float minX, float maxX, float minY, float maxY, float minZ, float maxZ)
        {
            if (minX > minX_a || maxX < maxX_a ||
                minY > minY_a || maxY < maxY_a ||
                minZ > minZ_a || maxZ < maxZ_a)
            {
                //Log
                return;
            }

            if (maxDepth == 0)
                return AddDirect(element);

            int z_b = (maxZ_a < centerZ) * 0b01       + (minZ_a > centerZ) * 0b10;
            int y_b = (maxY_a < centerY) * 0b0001     + (minY_a > centerY) * 0b0100;
            int x_b = (maxZ_a < centerX) * 0b00000001 + (minX_a > centerX) * 0b00010000;
            int subIndeces = z_b * y_b * x_b;
            
            int i = 0;
            while (subIndeces)
            {
                if (subIndeces & 1)
                    subTrees[i]->Add(element, minX_a, maxX_a, minY_a, maxY_a, minZ_a, maxZ_a);
                subIndeces >> 1;
            }
            return nullptr; // figure this out
        }
        void Remove(ElemT* element)
        {
            for (int i = 0; i < maxElements; i++)
            {
                if (elements[i] = element)
                    elementsUsed[i] = false;
            }
        }

        Octree* GetSubTree(int idx)
        {
            if (subTrees[idx] == nullptr)
            {
                float newMinX, newMaxX, newMinY, newMaxY, newMinZ, newMaxZ;

                /* X */
                if (idx & 4 == 0)
                {
                    newMinX = minX;
                    newMaxX = centerX;
                }
                else
                {
                    newMinX = centerX;
                    newMaxX = maxX;
                }

                /* Y */
                if (idx & 2 == 0)
                {
                    newMinY = minY;
                    newMaxY = centerY;
                }
                else
                {
                    newMinY = centerY;
                    newMaxY = maxY;
                }

                /* Z */
                if (idx & 1 == 0)
                {
                    newMinZ = minZ;
                    newMaxZ = centerZ;
                }
                else
                {
                    newMinZ = centerZ;
                    newMaxZ = maxZ;
                }

                subTrees[idx] = new Octree(newMinX, newMaxX, newMinY, newMaxY, newMinZ, newMaxZ, maxDepth - 1);
            }
            return subTrees[idx];
        }

    private:
        static const int maxElements = 32;
        ElemT* elements[maxElements];
        bool elementsUsed[maxElements];

        Octree* AddDirect(ElemT* element)
        {
            elements[NextAvailableIndex()] = element;
            return this;
        }

        Octree* subTrees[8]; // xyz xyZ xYz xYZ Xyz XyZ XYz XYZ

        int _nextAvailableActor;
        int NextAvailableIndex()
        {
            for (int i = 0; i < maxElement; i++)
            {
                int idx = (_nextAvailableActor + i) % maxElement;
                if (elementsUsed[idx] == 0)
                {
                    _nextAvailableActor = idx;
                    return _nextAvailableActor++;
                }
            }
            //Log
            return _nextAvailableActor++;
        }

        float minX, maxX, minY, maxY, minZ, maxZ;
        float centerX, centerY, centerZ;
        unsigned maxDepth;
    };
}