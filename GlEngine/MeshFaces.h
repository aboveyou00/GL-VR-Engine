#pragma once

namespace GlEngine
{
    class Material;

    struct MeshFaces
    {
        MeshFaces();
        ~MeshFaces();

        std::vector<Vector<3, unsigned>> *triangleIndices;
        std::vector<Vector<4, unsigned>> *quadIndices;
    };

    typedef std::map<Material*, MeshFaces*> MtlFacesMap;
}
