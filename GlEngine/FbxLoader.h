#pragma once
#include "VboGraphicsObject.h"
#include "FbxGraphicsObject.h"
#include <fstream>
#include <vector>
#include <unordered_map>
#include "Vector.h"
#include <array>

namespace fbxsdk
{
    class FbxNode;
    class FbxMesh;
    class FbxSurfaceMaterial;
}

namespace GlEngine
{
    class Material;
    class VboGraphicsObject;

    class ENGINE_SHARED FbxLoader
    {
    public:
        static bool Load(const char * const filename, VboGraphicsObject *out);

    private:
        static std::vector<std::tuple<Vector<3>, Vector<2>, Vector<3>>> glVertices;

        static bool Convert(fbxsdk::FbxNode *rootNode, VboGraphicsObject *out);
        static bool ConvertMesh(fbxsdk::FbxMesh *mesh, VboGraphicsObject *out);

        static Material *ConvertMaterial(fbxsdk::FbxSurfaceMaterial *mat);
    };
}
