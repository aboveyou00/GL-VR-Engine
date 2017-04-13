#pragma once

#include "Ray.h"
#include "GameComponent.h"

namespace GlEngine
{
    class ENGINE_SHARED MeshComponent : public GameComponent
    {
    public:
        MeshComponent(std::vector<Vector<3>> vertices, std::vector<Vector<3, unsigned>> triangles);
        ~MeshComponent();

        std::vector<Vector<3>> vertices;
        std::vector<Vector<3, unsigned>> triangles;
        std::vector<Vector<3>> normals;

        bool RayIntersection(Ray ray, float* outDistance = nullptr);

    private:
        void CalculateNormals();

        bool RayIntersectionInternal(Ray ray);
        bool RayIntersectionInternal(Ray ray, float* outDistance);
    };
}