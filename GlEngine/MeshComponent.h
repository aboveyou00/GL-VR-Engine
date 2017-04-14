#pragma once

#include "Ray.h"
#include "GameComponent.h"
#include "IBoundingBox.h"

namespace GlEngine
{
    class ENGINE_SHARED MeshComponent : public GameComponent, public IBoundingBox
    {
    public:
        MeshComponent(std::vector<Vector<3>> *vertices, std::vector<Vector<3, unsigned>> *triangles, std::vector<Vector<2>> *texCoords = {}, std::vector<Vector<3>> *normals = {}, bool isStatic = true);
        MeshComponent(std::vector<Vector<3>> *vertices, std::vector<Vector<4, unsigned>> *quads, std::vector<Vector<2>> *texCoords = {}, std::vector<Vector<3>> *normals = {}, bool isStatic = true);
        MeshComponent(std::vector<Vector<3>> *vertices, std::vector<Vector<3, unsigned>> *triangles, std::vector<Vector<4, unsigned>> *quads, std::vector<Vector<2>> *texCoords = {}, std::vector<Vector<3>> *normals = {}, bool isStatic = true);
        ~MeshComponent();

        std::vector<Vector<3>> *vertices;
        std::vector<Vector<3, unsigned>> *triangles;
        std::vector<Vector<4, unsigned>> *quads;
        
        std::vector<Vector<3, unsigned>> *allTriangles;

        std::vector<Vector<3>> *normals;
        std::vector<Vector<2>> *texCoords;

        bool isStatic;

        virtual inline float minX() override { return _minX; }
        virtual inline float maxX() override { return _maxX; }
        virtual inline float minY() override { return _minY; }
        virtual inline float maxY() override { return _maxY; }
        virtual inline float minZ() override { return _minZ; }
        virtual inline float maxZ() override { return _maxZ; }

        bool RayIntersection(Ray ray, float* outDistance = nullptr);

        virtual void GameObjectChanged() override;
        void CalculateBounds();
        void CalculateNormals();

    private:
        bool RayIntersectionInternal(Ray ray);
        bool RayIntersectionInternal(Ray ray, float* outDistance);

        float _minX, _maxX, _minY, _maxY, _minZ, _maxZ;
    };
}