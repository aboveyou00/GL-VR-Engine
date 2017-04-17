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
        SetMaterial(material());

        for (size_t i = 0; i < _mesh->vertices->size(); i++)
        {
            AddVertex((*_mesh->vertices)[i], (*_mesh->texCoords)[i], (*_mesh->normals)[i]);
        }
        for (Vector<3, unsigned> triangle : *_mesh->triangles)
        {
            AddTriangle(triangle[0], triangle[1], triangle[2]);
        }
        for (Vector<4, unsigned> quad : *_mesh->quads)
        {
            AddQuad(quad[0], quad[1], quad[2], quad[3]);
        }

        return VboGraphicsObject::InitializeAsync();
    }
}
