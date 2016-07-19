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

		static int FindOrAddGlVertex(Vector<3> position, Vector<2> texCoord, Vector<3> normal);
		
		static bool Convert(fbxsdk::FbxNode* rootNode, FbxGraphicsObject * out);
		static bool ConvertMesh(fbxsdk::FbxMesh* mesh, FbxGraphicsObject * out);
		static bool ConvertMaterial(fbxsdk::FbxSurfaceMaterial* mat, FbxGraphicsObject * out);

	};
}