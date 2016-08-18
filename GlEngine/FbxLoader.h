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
    namespace Impl
    {
        class VboGraphicsObjectImpl;
    }

	class ENGINE_SHARED FbxLoader
	{
	public:
		static bool Load(const char * const filename, Impl::VboGraphicsObjectImpl *out);

	private:
		static std::vector<std::tuple<Vector<3>, Vector<2>, Vector<3>>> glVertices;

		static bool Convert(fbxsdk::FbxNode *rootNode, Impl::VboGraphicsObjectImpl *out);
        static bool ConvertMesh(fbxsdk::FbxMesh *mesh, Impl::VboGraphicsObjectImpl *out);
		static bool ConvertMaterial(fbxsdk::FbxSurfaceMaterial *mat, Impl::VboGraphicsObjectImpl *out);
	};
}
