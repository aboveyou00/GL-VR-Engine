#include "stdafx.h"
#include "MeshMaterialGraphicsObject.h"

namespace GlEngine
{
    MeshMaterialGraphicsObject::MeshMaterialGraphicsObject(MeshComponent* mesh, Material* material, CreateFactoryFn createFactory)
        : VboGraphicsObject("MeshMaterialGraphicsObject", createFactory), _mesh(mesh), _material(material)
    {
    }
    MeshMaterialGraphicsObject::~MeshMaterialGraphicsObject()
    {
    }

    MeshComponent* MeshMaterialGraphicsObject::mesh()
    {
        return _mesh;
    }

    Material* MeshMaterialGraphicsObject::material()
    {
        return _material;
    }

    bool MeshMaterialGraphicsObject::InitializeAsync()
    {
        assert(_mesh != nullptr);

        for (size_t i = 0; i < _mesh->vertices->size(); i++)
        {
            AddVertex((*_mesh->vertices)[i], (*_mesh->texCoords)[i], (*_mesh->normals)[i]);
        }
        for (auto it = _mesh->_faces->begin(); it != _mesh->_faces->end(); it++)
        {
            Material *mat;
            MeshFaces *faces;
            std::tie(mat, faces) = *it;
            if (mat == nullptr) mat = material();
            SetMaterial(mat);

            for (Vector<3, unsigned> triangle : *faces->triangleIndices)
            {
                AddTriangle(triangle[0], triangle[1], triangle[2]);
            }
            for (Vector<4, unsigned> quad : *faces->quadIndices)
            {
                AddQuad(quad[0], quad[1], quad[2], quad[3]);
            }
        }

        return VboGraphicsObject::InitializeAsync();
    }
}
