#include "stdafx.h"
#include "FbxLoader.h"

#include "fbxsdk.h"
#include "VboFactory.h"
#include "VbObject.h"
#include "Texture.h"
#include "BlinnMaterial.h"

namespace GlEngine
{
	std::vector<std::tuple<Vector<3>, Vector<2>, Vector<3>>> FbxLoader::glVertices;

	Material *FbxLoader::ConvertMaterial(fbxsdk::FbxSurfaceMaterial *mat)
	{
		mat;
		auto diffuseProp = mat->FindProperty(fbxsdk::FbxSurfaceMaterial::sDiffuse);
		int layeredCount = diffuseProp.GetSrcObjectCount<fbxsdk::FbxLayeredTexture>();
        
		if (layeredCount > 0)
		{
			// layered textures
            assert(false);
            return nullptr;
		}
		else
		{
			int textureCount = diffuseProp.GetSrcObjectCount<fbxsdk::FbxTexture>();
            assert(textureCount == 1);

            auto texture = fbxsdk::FbxCast<fbxsdk::FbxTexture>(diffuseProp.GetSrcObject<fbxsdk::FbxTexture>(0));
            auto fileTexture = (fbxsdk::FbxFileTexture*)texture;
            auto filename = fileTexture->GetFileName();

            // TODO: get texture instance from filename;
            auto tex = Texture::FromFile(filename, fileTexture->GetAlphaSource() != fbxsdk::FbxTexture::EAlphaSource::eNone);
            return BlinnMaterial::Create(tex);
		}
	}

	bool FbxLoader::Convert(fbxsdk::FbxNode* rootNode, VboGraphicsObject *out)
	{
		static int depth = 0;
		for (int i = 0; i < depth; i++)
			std::cout << "  ";
		std::cout << rootNode->GetName()<<std::endl;
		depth++;

        int matCount = rootNode->GetMaterialCount();
        Material **materials = nullptr;
        if (matCount > 0)
        {
            materials = new Material*[matCount];
            for (auto q = 0; q < matCount; q++)
            {
                Material *mat = ConvertMaterial(rootNode->GetMaterial(q));
                materials[q] = mat;
            }

            out->SetMaterial(materials[0]);
        }

		for (int i = 0; i < rootNode->GetChildCount(); i++)
		{
			auto subNode = rootNode->GetChild(i);
            if (auto mesh = subNode->GetMesh())
                ConvertMesh(mesh, out);
            if (!Convert(subNode, out))
            {
                SafeDelete(materials);
                return false;
            }
		}
		depth--;
        SafeDelete(materials);
		return true;
	}
    bool FbxLoader::ConvertMesh(fbxsdk::FbxMesh *mesh, VboGraphicsObject *out)
    {
        std::cout << "Loading mesh: " << mesh->GetName() << std::endl;

        std::vector<int> faceIndices;

        auto uvs = mesh->GetLayer(0)->GetUVs();

        auto node = mesh->GetNode();
        int matCount = (node ? node->GetMaterialCount() : 0);
        Material **materials = nullptr;
        if (matCount > 0)
        {
            materials = new Material*[matCount];
            for (auto q = 0; q < matCount; q++)
            {
                Material *mat = ConvertMaterial(node->GetMaterial(q));
                materials[q] = mat;
            }
        }

        auto layerCount = mesh->GetLayerCount();
        assert(layerCount == 1);
        auto layer = mesh->GetLayer(0);
        auto layerMaterials = layer->GetMaterials();
        auto &matIndexArray = layerMaterials->GetIndexArray();

        for (int p = 0; p < mesh->GetPolygonCount(); p++)
        {
            auto polySize = mesh->GetPolygonSize(p);
            auto matIdx = matIndexArray[p];
            auto mat = materials[matIdx];
            out->SetMaterial(mat);
            
            if (polySize != 3 && polySize != 4)
            {
                // N-gons not supported
                assert(false);
            }
            for (int pi = 0; pi < polySize; pi++)
            {
                auto vertexIdx = mesh->GetPolygonVertex(p, pi);
                fbxsdk::FbxVector4 vertex = mesh->GetControlPointAt(vertexIdx);

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
            if (polySize == 3) out->AddTriangle(faceIndices[2], faceIndices[1], faceIndices[0]);
            else if (polySize == 4) out->AddQuad(faceIndices[3], faceIndices[2], faceIndices[1], faceIndices[0]);
            faceIndices.clear();
        }

        SafeDelete(materials);

        std::cout << "Finished mesh: " << mesh->GetName() << std::endl;
        return true;
    }
     
	bool FbxLoader::Load(const char * const filename, VboGraphicsObject *out)
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
