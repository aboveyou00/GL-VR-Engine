#include "stdafx.h"
#include "MeshComponent.h"
#include "MathUtils.h"
#include "Frame.h"
#include "GameObject.h"

namespace GlEngine
{
    MeshComponent::MeshComponent(std::vector<Vector<3>> *vertices, std::vector<Vector<3, unsigned>> *triangles, std::vector<Vector<2>> *texCoords, std::vector<Vector<3>> *normals, bool isStatic)
        : MeshComponent(vertices, triangles, nullptr, texCoords, normals, isStatic)
    {
    }

    MeshComponent::MeshComponent(std::vector<Vector<3>> *vertices, std::vector<Vector<4, unsigned>> *quads, std::vector<Vector<2>> *texCoords, std::vector<Vector<3>> *normals, bool isStatic)
        : MeshComponent(vertices, nullptr, quads, texCoords, normals, isStatic)
    {
    }

    MeshComponent::MeshComponent(std::vector<Vector<3>> *vertices, std::vector<Vector<3, unsigned>> *triangles, std::vector<Vector<4, unsigned>> *quads, std::vector<Vector<2>> *texCoords, std::vector<Vector<3>> *normals, bool isStatic)
        : GameComponent("Mesh"), vertices(vertices), triangles(triangles), quads(quads), texCoords(texCoords), normals(normals), isStatic(isStatic), allTriangles(new std::vector<Vector<3, unsigned>>())
    {
        CalculateBounds();
        if (triangles != nullptr) {
            allTriangles->insert(allTriangles->begin(), triangles->begin(), triangles->end());
        }
        if (quads != nullptr) {
            for (auto quad : *quads)
            {
                allTriangles->push_back(Vector<3, unsigned>{quad[0], quad[1], quad[2]});
                allTriangles->push_back(Vector<3, unsigned>{quad[2], quad[3], quad[0]});
            }
        }
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
        {
            if (isStatic)
                partitions->AddStaticMesh(this);
            else
                partitions->AddMesh(this);
        }
    }

    void MeshComponent::CalculateBounds()
    {
        float dist_sqr = 0;
        for (auto position : *vertices)
            dist_sqr = max(dist_sqr, position.LengthSquared());
        
        float dist = sqrt(dist_sqr);
        _minX = _minY = _minZ = -dist;
        _maxX = _maxY = _maxZ = dist;
    }

    void MeshComponent::CalculateNormals()
    {
        if (normals->size() != 0)
            return;

        assert(triangles != nullptr); //TODO: Why is this not allTriangles?
        for (Vector<3, unsigned> triangle : *triangles)
        {
            Vector<3> point0 = (*vertices)[triangle[0]];
            Vector<3> point1 = (*vertices)[triangle[1]];
            Vector<3> point2 = (*vertices)[triangle[2]];

            normals->push_back((point1 - point0).Cross(point2 - point0).Normalized());
        }
    }

    bool MeshComponent::RayIntersectionInternal(Ray ray)
    {
        Vector<3> origin = ray.origin - gameObject()->globalTransform()->position();
        Vector<3> direction = ray.direction * gameObject()->globalTransform()->orientation().Inverse();

        for (auto triangle : *allTriangles)
            if (Util::triangleRayIntersection((*vertices)[triangle[0]], (*vertices)[triangle[1]], (*vertices)[triangle[2]], origin, direction))
                return true;
        return false;
    }
    
    bool MeshComponent::RayIntersectionInternal(Ray ray, float* outDistance)
    {
        float distance;
        bool result = false;

        Vector<3> origin = ray.origin - gameObject()->globalTransform()->position();
        Vector<3> direction = ray.direction * gameObject()->globalTransform()->orientation().Inverse();

        for (auto triangle : *allTriangles)
        {
            if (Util::triangleRayIntersection((*vertices)[triangle[0]], (*vertices)[triangle[1]], (*vertices)[triangle[2]], origin, direction, &distance))
            {
                if (!result || *outDistance > distance)
                    *outDistance = distance;
                result = true;
            }
        }

        return result;
    }
}
