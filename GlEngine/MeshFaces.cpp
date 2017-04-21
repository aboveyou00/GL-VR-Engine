#include "stdafx.h"
#include "MeshFaces.h"

namespace GlEngine
{
    MeshFaces::MeshFaces()
    {
        triangleIndices = new std::vector<Vector<3, unsigned>>();
        quadIndices = new std::vector<Vector<4, unsigned>>();
    }
    MeshFaces::~MeshFaces()
    {
        SafeDelete(triangleIndices);
        SafeDelete(quadIndices);
    }
}
