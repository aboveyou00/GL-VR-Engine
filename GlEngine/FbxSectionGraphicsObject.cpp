#include "stdafx.h"
#include "FbxSectionGraphicsObject.h"

#include "Shader.h"
#include "Texture.h"

namespace GlEngine
{
    namespace Impl
    {
        FbxSectionGraphicsObject::FbxSectionGraphicsObject(fbxsdk::FbxMesh *fbxMesh)
            : mesh(fbxMesh), glVertices(new std::vector<std::tuple<Vector<3>, Vector<2>, Vector<3>>>())
        {
        }
        FbxSectionGraphicsObject::~FbxSectionGraphicsObject()
        {
            SafeDelete(glVertices);
        }

        bool FbxSectionGraphicsObject::Initialize()
        {
            std::cout << "Loading mesh: " << mesh->GetName() << std::endl;

            std::vector<int> triangleIndices;
            std::vector<int> quadIndices;

            auto uvs = mesh->GetLayer(0)->GetUVs();

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
                    int vIndex = findOrAddGlVertex({ vertex[0], vertex[1], vertex[2] }, { texCoord[0], texCoord[1] }, { normal[0], normal[1], normal[2] });
                    if (polySize == 3) triangleIndices.push_back(vIndex);
                    else if (polySize == 4) quadIndices.push_back(vIndex);
                }
            }

            for (auto vertex : *glVertices)
            {
                Vector<3> position; Vector<2> texCoord; Vector<3> normal;
                std::tie(position, texCoord, normal) = vertex;
                AddVertex(position, texCoord, normal);
            }

            //TODO: set the Shader and Texture before we add any faces
            auto shader = GlEngine::Shader::Create("Shaders", "direct_light_tex");
            auto texture = GlEngine::Texture::FromFile("Textures/dirt.png");
            SetGraphics(shader, texture);
            for (unsigned i = 0; i < triangleIndices.size() / 3; i++)
                AddTriangle({ triangleIndices[3 * i + 2], triangleIndices[3 * i + 1], triangleIndices[3 * i] });
            for (unsigned i = 0; i < quadIndices.size() / 4; i++)
                AddQuad({ quadIndices[4 * i + 3], quadIndices[4 * i + 2], quadIndices[4 * i + 1], quadIndices[4 * i] });

            delete glVertices;

            std::cout << "Finished mesh: " << mesh->GetName() << std::endl;
            return true;
        }
        void FbxSectionGraphicsObject::Shutdown()
        {
        }

        int FbxSectionGraphicsObject::findOrAddGlVertex(Vector<3> position, Vector<2> texCoord, Vector<3> normal)
        {
            std::tuple<Vector<3>, Vector<2>, Vector<3>> glVertex(position, texCoord, normal);

            auto index = std::find(glVertices->begin(), glVertices->end(), glVertex);
            if (index == glVertices->end())
            {
                glVertices->push_back(glVertex);
                return glVertices->size() - 1;
            }
            else
            {
                return index - glVertices->begin();
            }
        }
    }
}
