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
    public:
        static std::vector<Vector<3>> positions;
        static std::vector<Vector<3>> normals;
        static std::vector<Vector<2>> texCoords;
        
        static std::vector<std::tuple<Vector<3>, Vector<2>, Vector<3>>> glVertices;

        static std::vector<int> triangleIndices;
        static std::vector<int> quadIndices;

        static bool Load(const char * const filename, ObjGraphicsObject * out);
        static bool Load(std::istream & in, ObjGraphicsObject * out);

    private:
        static int ParseVertex(std::string faceString);
        static int ObjLoader::FindOrAddGlVertex(Vector<3> position, Vector<2> texCoord, Vector<3> normal);
        static bool CreateFromData(ObjGraphicsObject * out);

    };
}
