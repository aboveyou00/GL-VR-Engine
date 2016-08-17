#include "stdafx.h"
#include "FbxLoader.h"

#include "fbxsdk.h"
#include "VBOFactory.h"
#include "VbObject.h"
#include "Texture.h"
#include "BlinnMaterial.h"

namespace GlEngine
{
	std::vector<std::tuple<Vector<3>, Vector<2>, Vector<3>>> FbxLoader::glVertices;

	bool FbxLoader::ConvertMaterial(fbxsdk::FbxSurfaceMaterial *mat, Impl::VboGraphicsObjectImpl *out)
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

	bool FbxLoader::Convert(fbxsdk::FbxNode* rootNode, Impl::VboGraphicsObjectImpl *out)
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
    bool FbxLoader::ConvertMesh(fbxsdk::FbxMesh *mesh, Impl::VboGraphicsObjectImpl *out)
    {
        std::cout << "Loading mesh: " << mesh->GetName() << std::endl;

        std::vector<int> faceIndices;

        auto uvs = mesh->GetLayer(0)->GetUVs();

        auto texture = GlEngine::Texture::FromFile("Textures/dirt.png");
        auto mat = GlEngine::BlinnMaterial::Create(texture);
        out->SetMaterial(mat);

        for (int p = 0; p < mesh->GetPolygonCount(); p++)
        {
            auto polySize = mesh->GetPolygonSize(p);
            if (polySize != 3 && polySize != 4)
            {
                // N-gons not supported
                assert(false);
            }
            for (int pi = 0; pi < polySize; pi++)
            {
                fbxsdk::FbxVector4 vertex = mesh->GetControlPointAt(mesh->GetPolygonVertex(p, pi));

                fbxsdk::FbxVector4 normal;
                mesh->GetPolygonVertexNormal(p, pi, normal);

                fbxsdk::FbxVector2 texCoord;
                if (uvs)
                {
                    auto uvName = uvs->GetName();
                    bool unMapped;
                    mesh->GetPolygonVertexUV(p, pi, uvName, texCoord, unMapped);
                }
                int vIndex = out->AddVertex({ vertex[0], vertex[1], vertex[2] }, { texCoord[0], texCoord[1] }, { normal[0], normal[1], normal[2] });
                faceIndices.push_back(vIndex);
            }
            if (polySize == 3) out->AddTriangle(faceIndices[0], faceIndices[1], faceIndices[2]);
            else if (polySize == 4) out->AddQuad(faceIndices[0], faceIndices[1], faceIndices[2], faceIndices[3]);
            faceIndices.clear();
        }

        std::cout << "Finished mesh: " << mesh->GetName() << std::endl;
        return true;
    }
     
	bool FbxLoader::Load(const char * const filename, Impl::VboGraphicsObjectImpl *out)
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
