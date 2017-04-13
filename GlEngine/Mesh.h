#pragma once

#include "Ray.h"

namespace GlEngine
{
    class ENGINE_SHARED Mesh
    {
    public:
        Mesh(std::vector<Vector<3>> vertices, std::vector<Vector<3, unsigned>> triangles);
        ~Mesh();

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