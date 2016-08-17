#include "stdafx.h"
#include "FbxLoader.h"

#include "fbxsdk.h"
#include "VBOFactory.h"
#include "VbObject.h"

#include "Shader.h"
#include "Texture.h"

namespace GlEngine
{
	std::vector<std::tuple<Vector<3>, Vector<2>, Vector<3>>> FbxLoader::glVertices;
	std::vector<int> FbxLoader::triangleIndeces;

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

	bool FbxLoader::ConvertMesh(fbxsdk::FbxMesh* mesh)
	{
		std::cout << "Loading mesh: " << mesh->GetName() << std::endl;

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
		return true;
	}

	bool FbxLoader::ConvertMaterial(fbxsdk::FbxSurfaceMaterial* mat)
	{
		mat;
		//auto diffuseProp = mat->FindProperty(fbxsdk::FbxSurfaceMaterial::sDiffuse);
		//int layeredCount = diffuseProp.GetSrcObjectCount<fbxsdk::FbxLayeredTexture>();

		//if (layeredCount > 0)
		//{
		//	// layered textures
		//}
		//else
		//{
		//	int textureCount = diffuseProp.GetSrcObjectCount<fbxsdk::FbxTexture>();
		//	for (int i = 0; i < textureCount; i++)
		//	{
		//		auto texture = fbxsdk::FbxCast<fbxsdk::FbxTexture>(diffuseProp.GetSrcObject<fbxsdk::FbxTexture>(i));
		//		auto fileTexture = (fbxsdk::FbxFileTexture*)texture;
		//		fileTexture->GetFileName();
		//		// TODO: get texture instance from filename;
		//	}
		//}
		return true;
	}

	bool FbxLoader::Convert(fbxsdk::FbxNode* rootNode)
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
			{
				ConvertMesh(mesh);
				//if (subNode->GetSrcObjectCount<fbxsdk::FbxSurfaceMaterial>() >= 1)
				//{
				//	//auto mat = (fbxsdk::FbxSurfaceMaterial*)subNode->GetSrcObject<fbxsdk::FbxSurfaceMaterial>(0);
				//	//if (mat)
				//	//{

				//	//}
				//}
			}
			if (!Convert(subNode))
				return false;
		}
		depth--;
		return true;
	}

	bool FbxLoader::CreateObject(FbxGraphicsObject* out)
	{
		auto sub = new VboGraphicsObject();
		for (auto vertex : glVertices)
		{
			Vector<3> position; Vector<2> texCoord; Vector<3> normal;
			std::tie(position, texCoord, normal) = vertex;
			sub->AddVertex(position, texCoord, normal);
		}

		//TODO: set the Shader and Texture before we add any faces
		auto shader = GlEngine::Shader::Create("Shaders", "direct_light_tex");
		auto texture = GlEngine::Texture::FromFile("Textures/dirt.png");
		sub->SetGraphics(shader, texture);
		for (unsigned i = 0; i < triangleIndeces.size() / 3; i++)
			sub->AddTriangle({ triangleIndeces[3 * i + 2], triangleIndeces[3 * i + 1], triangleIndeces[3 * i] });

		out->AddSubObject(sub);
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
		if (!Convert(rootNode))
			return false;
		return CreateObject(out);
	}
}
