#include "stdafx.h"
#include "FbxLoader.h"

#include "fbxsdk.h"
#include "VBOFactory.h"
#include "VbObject.h"

#include "FbxSectionGraphicsObject.h"
#include "Shader.h"
#include "Texture.h"

namespace GlEngine
{
	std::vector<std::tuple<Vector<3>, Vector<2>, Vector<3>>> FbxLoader::glVertices;

	bool FbxLoader::ConvertMaterial(fbxsdk::FbxSurfaceMaterial* mat, FbxGraphicsObject * out)
	{
		mat; out;
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
                out->AddSubObject(new Impl::FbxSectionGraphicsObject(mesh));
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
