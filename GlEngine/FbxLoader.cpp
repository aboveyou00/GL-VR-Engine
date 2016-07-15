#include "stdafx.h"
#include "FbxLoader.h"

#include "fbxsdk.h"
#include "VBOFactory.h"
#include "VbObject.h"

namespace GlEngine
{
	std::vector<std::tuple<Vector<3>, Vector<2>, Vector<3>>> FbxLoader::glVertices;

	int FbxLoader::FindOrAddGlVertex(Vector<3> position, Vector<2> texCoord, Vector<3> normal)
	{
		std::tuple<Vector<3>, Vector<2>, Vector<3>> glVertex(position, texCoord, normal);

		auto index = std::find(glVertices.begin(), glVertices.end(), glVertex);
		if (index == glVertices.end())
		{
			glVertices.push_back(glVertex);
			return glVertices.size() - 1;
		}
		else
		{
			return index - glVertices.begin();
		}
	}

	bool FbxLoader::ConvertMesh(fbxsdk::FbxMesh* mesh, FbxGraphicsObject * out)
	{
		std::cout << "Loading mesh: " << mesh->GetName() << std::endl;

		std::vector<int> triangleIndeces;

		for (int p = 0; p < mesh->GetPolygonCount(); p++)
		{
			if (mesh->GetPolygonSize(p) != 3)
			{
				// Non-tris not supported
				assert(false);
			}
			for (int pi = 0; pi < mesh->GetPolygonSize(p); pi++)
			{
				fbxsdk::FbxVector4 vertex = mesh->GetControlPointAt(mesh->GetPolygonVertex(p, pi));
				
				fbxsdk::FbxVector4 normal;
				mesh->GetPolygonVertexNormal(p, pi, normal);

				fbxsdk::FbxVector2 texCoord;
				auto uvs = mesh->GetLayer(0)->GetUVs();
				if (uvs)
				{
					auto uvName = uvs->GetName();
					bool unMapped;
					mesh->GetPolygonVertexUV(p, pi, uvName, texCoord, unMapped);
				}
				int vIndex = FindOrAddGlVertex({ vertex[0], vertex[1], vertex[2] }, { texCoord[0], texCoord[1] }, { normal[0], normal[1], normal[2] });
				triangleIndeces.push_back(vIndex);
			}
		}

		//Below for Gl thread

		VboFactory<VboType::Float, Vector<3>, Vector<2>, Vector<3>> verticesFactory(BufferMode::Array);
		verticesFactory.Allocate(glVertices.size());
		for (auto vertex : glVertices)
		{
			Vector<3> position; Vector<2> texCoord; Vector<3> normal;
			std::tie(position, texCoord, normal) = vertex;
			verticesFactory.AddVertex(position, texCoord, normal);
		}

		VboFactory<VboType::UnsignedShort, uint16_t, uint16_t, uint16_t> trianglesFactory(BufferMode::ElementArray);
		trianglesFactory.Allocate(mesh->GetPolygonCount());
		for (unsigned i = 0; i < triangleIndeces.size() / 3; i++)
		{
			trianglesFactory.AddVertex((uint16_t)triangleIndeces[3 * i + 2], (uint16_t)triangleIndeces[3 * i + 1], (uint16_t)triangleIndeces[3 * i]);
		}

		VboGraphicsObject sub;
		sub.arrayVbo = verticesFactory.Compile();
		sub.elementVbo = trianglesFactory.Compile();
		sub.triCount = triangleIndeces.size() / 3;
		sub.shader = Shader("Shaders", "simple");

		out->AddSubObject(sub);


		std::cout << "Finished mesh: " << mesh->GetName() << std::endl;
		return true;
	}

	bool FbxLoader::Convert(fbxsdk::FbxNode* rootNode, FbxGraphicsObject * out)
	{
		static int depth = 0;
		for (int i = 0; i < depth; i++)
			std::cout << "  ";
		std::cout << rootNode->GetName()<<std::endl;
		depth++;
		
		for (int i = 0; i < rootNode->GetChildCount(); i++)
		{
			auto subNode = rootNode->GetChild(i);
			if (auto mesh = subNode->GetMesh())
				ConvertMesh(mesh, out);
			if (!Convert(subNode, out))
				return false;
		}
		depth--;
		return true;
	}

	bool FbxLoader::Load(const char * const filename, FbxGraphicsObject * out)
	{
		FbxManager *lSdkManager = FbxManager::Create();
		FbxIOSettings * ios = FbxIOSettings::Create(lSdkManager, IOSROOT);

		ios->SetBoolProp(IMP_FBX_MATERIAL, true);
		ios->SetBoolProp(IMP_FBX_TEXTURE, true);

		auto scene = FbxScene::Create(lSdkManager, "");
		auto importer = FbxImporter::Create(lSdkManager, "");
		importer->Initialize(filename, -1, ios);
		importer->Import(scene);
		importer->Destroy();

		auto rootNode = scene->GetRootNode();
		return Convert(rootNode, out);
	}
}
