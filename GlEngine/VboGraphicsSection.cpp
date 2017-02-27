#include "stdafx.h"
#include "VboGraphicsSection.h"

#include "ShaderFactory.h"
#include "VboFactory.h"
#include "Material.h"
#include "OpenGl.h"

namespace GlEngine
{
    namespace Impl
    {
        VboGraphicsSection::VboGraphicsSection(Material *material, std::vector<ShaderFactory::IPropertyProvider*> &providers, ShaderFactory::ShaderFactory* factory)
            : material(material),
              tris(new std::vector<Vector<3, uint16_t>>()),
              quads(new std::vector<Vector<4, uint16_t>>()),
              _factory(factory == nullptr ? new ShaderFactory::ShaderFactory() : factory),
              finalized(false)
        {
            SetFactory(_factory, providers);
        }
        VboGraphicsSection::~VboGraphicsSection()
        {
            SafeDelete(tris);
            SafeDelete(quads);
        }

        void VboGraphicsSection::AddTriangle(Vector<3, uint16_t> indices)
        {
            assert(!finalized);
            tris->push_back(indices);
        }
        void VboGraphicsSection::AddQuad(Vector<4, uint16_t> indices)
        {
            assert(!finalized);
            quads->push_back(indices);
        }
        void VboGraphicsSection::Finalize(VboFactory<VboType::UnsignedShort, uint16_t>* face_factory)
        {
            assert(!finalized);

            finalized = true;
            triCount = tris->size();
            quadCount = quads->size();

            if (face_factory == nullptr)
            {
                assert(triCount == 0);
                assert(quadCount == 0);
            }
            else
            {
                if (triCount > 0)
                {
                    auto vec = tris->at(0);
                    triOffset = sizeof(uint16_t) * face_factory->AddVertex(vec[0]);
                    face_factory->AddVertex(vec[1]);
                    face_factory->AddVertex(vec[2]);
                    for (int q = 1; q < triCount; q++)
                    {
                        vec = tris->at(q);
                        face_factory->AddVertex(vec[0]);
                        face_factory->AddVertex(vec[1]);
                        face_factory->AddVertex(vec[2]);
                    }
                }
                if (quadCount > 0)
                {
                    auto vec = quads->at(0);
                    quadOffset = sizeof(uint16_t) * face_factory->AddVertex(vec[0]);
                    face_factory->AddVertex(vec[1]);
                    face_factory->AddVertex(vec[2]);
                    face_factory->AddVertex(vec[3]);
                    for (int q = 1; q < quadCount; q++)
                    {
                        vec = quads->at(q);
                        face_factory->AddVertex(vec[0]);
                        face_factory->AddVertex(vec[1]);
                        face_factory->AddVertex(vec[2]);
                        face_factory->AddVertex(vec[3]);
                    }
                }
            }

            SafeDelete(tris);
            SafeDelete(quads);
        }

        void VboGraphicsSection::Render(RenderStage* stage)
        {
            if (!*this) return;

            if (stage != material->GetRenderStage())
                return;

            _factory->Push();

            auto tesselation = material->GetTesselationType();
            if (tesselation == TesselationType::Disabled)
            {
                if (triCount)
                {
                    glDrawElements(GL_TRIANGLES, triCount * 3, static_cast<GLenum>(VboType::UnsignedShort), BUFFER_OFFSET(triOffset));
                    checkForGlError();
                }
                if (quadCount)
                {
                    glDrawElements(GL_QUADS, quadCount * 4, static_cast<GLenum>(VboType::UnsignedShort), BUFFER_OFFSET(quadOffset));
                    checkForGlError();
                }
            }
            else if (tesselation == TesselationType::Triangles)
            {
                if (triCount)
                {
                    glPatchParameteri(GL_PATCH_VERTICES, 3);
                    checkForGlError();
                    glDrawElements(GL_PATCHES, triCount * 3, static_cast<GLenum>(VboType::UnsignedShort), BUFFER_OFFSET(triOffset));
                    checkForGlError();
                }
                assert(!quadCount);
            }
            else if (tesselation == TesselationType::Quads)
            {
                if (quadCount)
                {
                    glPatchParameteri(GL_PATCH_VERTICES, 4);
                    checkForGlError();
                    glDrawElements(GL_PATCHES, quadCount * 4, static_cast<GLenum>(VboType::UnsignedShort), BUFFER_OFFSET(triOffset));
                    checkForGlError();
                }
                assert(!triCount);
            }
            else assert(false);

            _factory->Pop();
        }

        void VboGraphicsSection::RenderInstanced(RenderStage* stage, unsigned instanceCount)
        {
            stage; instanceCount;
            assert(false);

            //if (layer != material->GetRenderTargetLayer())
            //    return;

            //if (!*this) return;

            //material->Push(true);

            //auto tesselation = material->GetTesselationType();
            //if (tesselation == TesselationType::Disabled)
            //{
            //    if (triCount) glDrawElementsInstanced(GL_TRIANGLES, triCount * 3, static_cast<GLenum>(VboType::UnsignedShort), BUFFER_OFFSET(triOffset), instanceCount);
            //    if (quadCount) glDrawElementsInstanced(GL_QUADS, quadCount * 4, static_cast<GLenum>(VboType::UnsignedShort), BUFFER_OFFSET(quadOffset), instanceCount);
            //}
            //else if (tesselation == TesselationType::Triangles)
            //{
            //    if (triCount)
            //    {
            //        glPatchParameteri(GL_PATCH_VERTICES, 3);
            //        glDrawElementsInstanced(GL_PATCHES, triCount * 3, static_cast<GLenum>(VboType::UnsignedShort), BUFFER_OFFSET(triOffset), instanceCount);
            //    }
            //}
            //else if (tesselation == TesselationType::Quads)
            //{
            //    if (quadCount)
            //    {
            //        glPatchParameteri(GL_PATCH_VERTICES, 4);
            //        glDrawElementsInstanced(GL_PATCHES, quadCount * 4, static_cast<GLenum>(VboType::UnsignedShort), BUFFER_OFFSET(triOffset), instanceCount);
            //    }
            //}
            //else assert(false);

            //material->Pop(true);
        }

        void VboGraphicsSection::RenderPoints(RenderStage* stage, unsigned count)
        {
            if (stage != material->GetRenderStage())
                return;

            _factory->Push();
            glDrawArrays(GL_POINTS, 0, count);
            checkForGlError();
            _factory->Pop();
        }

        ShaderFactory::ShaderFactory &VboGraphicsSection::factory()
        {
            return *_factory;
        }

        void VboGraphicsSection::SetFactory(ShaderFactory::ShaderFactory *factory, std::vector<ShaderFactory::IPropertyProvider*> &providers)
        {
            _factory = factory;
            _factory->AddPropertyProviders(providers);
            _factory->SetMaterial(material);
            _factory->Recompile();
        }

        VboGraphicsSection::operator bool()
        {
            return finalized && material && material->isReady() && _factory && _factory->isReady();
        }
    }
}
