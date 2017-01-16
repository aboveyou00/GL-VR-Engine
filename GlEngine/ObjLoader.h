#pragma once

#include "VboGraphicsObject.h"
#include "ObjGraphicsObject.h"
#include <fstream>
#include <vector>
#include <unordered_map>
#include "Vector.h"
#include <array>

namespace GlEngine
{
    class ENGINE_SHARED ObjLoader
    {
    private:
        ObjLoader();
        ~ObjLoader();

    public:
        static bool Load(const char *const filename, ObjGraphicsObject *out);
        static bool Load(std::istream &in, ObjGraphicsObject *out);

    private:
        std::vector<Vector<3>> positions;
        std::vector<Vector<3>> normals;
        std::vector<Vector<2>> texCoords;
        
        std::vector<std::tuple<Vector<3>, Vector<2>, Vector<3>>> glVertices;

        std::vector<int> triangleIndices;
        std::vector<int> quadIndices;

        bool _Load(std::istream &in, ObjGraphicsObject *out);
        int ParseVertex(std::string faceString);
        int ObjLoader::FindOrAddGlVertex(Vector<3> position, Vector<2> texCoord, Vector<3> normal);
        bool CreateFromData(ObjGraphicsObject * out);
    };
}
