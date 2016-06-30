#pragma once

#include "GraphicsObject.h"
#include <fstream>
#include <vector>
#include <unordered_map>
#include "Vector.h"
#include <array>

namespace GlEngine
{
	class ObjLoader
	{
	public:
		static std::vector<Vector<3>> positions;
		static std::vector<Vector<3>> normals;
		static std::vector<Vector<2>> texCoords;
		
		static std::vector<std::tuple<Vector<3>, Vector<2>, Vector<3>>> glVertices;

		static std::vector<int> triangleIndeces;
		static std::vector<int> quadIndeces;

		static GraphicsObject Load(const char * const filename);
		static GraphicsObject Load(std::istream & in);

	private:
		static int ParseVertex(std::string faceString);
		static int ObjLoader::FindOrAddGlVertex(Vector<3> position, Vector<2> texCoord, Vector<3> normal);
		static GraphicsObject CreateFromData();

	};
}