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
	class ENGINE_SHARED FbxLoader
	{
	public:
		static bool Load(const char * const filename, FbxGraphicsObject * out);


	private:
		static std::vector<std::tuple<Vector<3>, Vector<2>, Vector<3>>> glVertices;
		static std::vector<int> triangleIndeces;

		static int FindOrAddGlVertex(Vector<3> position, Vector<2> texCoord, Vector<3> normal);
		
		static bool Convert(fbxsdk::FbxNode* rootNode);
		static bool ConvertMesh(fbxsdk::FbxMesh* mesh);
		static bool ConvertMaterial(fbxsdk::FbxSurfaceMaterial* mat);

		static bool CreateObject(FbxGraphicsObject* out);
	};
}