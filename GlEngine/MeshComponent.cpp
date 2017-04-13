#include "stdafx.h"
#include "MeshComponent.h"
#include "MathUtils.h"
#include "Frame.h"
#include "GameObject.h"

namespace GlEngine
{
    MeshComponent::MeshComponent(std::vector<Vector<3>> vertices, std::vector<Vector<3, unsigned>> triangles, std::vector<Vector<2>> texCoords, std::vector<Vector<3>> normals)
        : MeshComponent(vertices, triangles, {}, texCoords, normals)
    {
    }

    MeshComponent::MeshComponent(std::vector<Vector<3>> vertices, std::vector<Vector<4, unsigned>> triangles, std::vector<Vector<2>> texCoords, std::vector<Vector<3>> normals)
        : MeshComponent(vertices, {}, quads, texCoords, normals)
    {
    }

    MeshComponent::MeshComponent(std::vector<Vector<3>> vertices, std::vector<Vector<3, unsigned>> triangles, std::vector<Vector<4, unsigned>> quads, std::vector<Vector<2>> texCoords, std::vector<Vector<3>> normals)
        : GameComponent("Mesh"), vertices(vertices), triangles(triangles), quads(quads), texCoords(texCoords), normals(normals)
    {
    }

    MeshComponent::~MeshComponent()
    {
        auto f = frame();
        if (f == nullptr)
            return;

        auto partitions = f->spatialPartitions;
        if (partitions != nullptr)
            partitions->RemoveMesh(this);
    }

    bool MeshComponent::RayIntersection(Ray ray, float *outDistance)
    {
        if (outDistance == nullptr)
            return RayIntersectionInternal(ray);
        else
            return RayIntersectionInternal(ray, outDistance);
    }

    void MeshComponent::GameObjectChanged()
    {
        auto partitions = frame()->spatialPartitions;
        if (partitions != nullptr)
            partitions->AddMesh(this);
    }

    void MeshComponent::CalculateNormals()
    {
        if (normals.size() != 0)
            return;

        for (Vector<3, unsigned> triangle : triangles)
        {
            Vector<3> point0 = vertices[triangle[0]];
            Vector<3> point1 = vertices[triangle[1]];
            Vector<3> point2 = vertices[triangle[2]];

            normals.push_back((point1 - point0).Cross(point2 - point0).Normalized());
        }
    }

    bool MeshComponent::RayIntersectionInternal(Ray ray)
    {
        Vector<3> origin = ray.origin - gameObject()->globalTransform()->position();
        Vector<3> direction = ray.direction * gameObject()->globalTransform()->orientation().Inverse();

        for (auto triangle : triangles)
            if (triangleRayIntersects(vertices[triangle[0]], vertices[triangle[1]], vertices[triangle[2]], origin, direction))
                return true;
        for (auto quad : quads)
        {
            if (triangleRayIntersects(vertices[quad[0]], vertices[quad[1]], vertices[quad[2]], origin, direction))
                return true;
            if (triangleRayIntersects(vertices[quad[2]], vertices[quad[3]], vertices[quad[0]], origin, direction))
                return true;
        }
        return false;
    }
    
    bool MeshComponent::RayIntersectionInternal(Ray ray, float* outDistance)
    {
        float distance;
        bool result = false;

        Vector<3> origin = ray.origin - gameObject()->globalTransform()->position();
        Vector<3> direction = ray.direction * gameObject()->globalTransform()->orientation().Inverse();

        for (auto triangle : triangles)
        {
            if (triangleRayIntersects(vertices[triangle[0]], vertices[triangle[1]], vertices[triangle[2]], origin, direction, &distance))
            {
                if (!result || *outDistance > distance)
                    *outDistance = distance;
                result = true;
            }
        }

        for (auto quad : quads)
        {
            if (triangleRayIntersects(vertices[quad[0]], vertices[quad[1]], vertices[quad[2]], origin, direction, &distance))
            {
                if (!result || *outDistance > distance)
                    *outDistance = distance;
                result = true;
            }
            if (triangleRayIntersects(vertices[quad[2]], vertices[quad[3]], vertices[quad[0]], origin, direction, &distance))
            {
                if (!result || *outDistance > distance)
                    *outDistance = distance;
                result = true;
            }
        }

        return result;
    }
}