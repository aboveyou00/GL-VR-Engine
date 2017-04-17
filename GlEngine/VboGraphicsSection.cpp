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
              lines(new std::vector<Vector<2, array_index_t>>()),
              tris(new std::vector<Vector<3, array_index_t>>()),
              quads(new std::vector<Vector<4, array_index_t>>()),
              _factory(factory == nullptr ? new ShaderFactory::ShaderFactory() : factory),
              finalized(false)
        {
            SetFactory(_factory, providers);
        }
        VboGraphicsSection::~VboGraphicsSection()
        {
            SafeDelete(lines);
            SafeDelete(tris);
            SafeDelete(quads);
        }

        void VboGraphicsSection::AddLine(Vector<2, array_index_t> indices)
        {
            assert(!finalized);
            lines->push_back(indices);
        }
        void VboGraphicsSection::AddTriangle(Vector<3, array_index_t> indices)
        {
            assert(!finalized);
            tris->push_back(indices);
        }
        void VboGraphicsSection::AddQuad(Vector<4, array_index_t> indices)
        {
            assert(!finalized);
            quads->push_back(indices);
        }
        void VboGraphicsSection::Finalize(VboFactory<ElementVboFactoryVboType, array_index_t>* face_factory)
        {
            assert(!finalized);

            finalized = true;
            lineCount = lines->size();
            triCount = tris->size();
            quadCount = quads->size();

            if (face_factory == nullptr)
            {
                assert(lineCount == 0);
                assert(triCount == 0);
                assert(quadCount == 0);
            }
            else
            {
                if (lineCount > 0)
                {
                    auto vec = lines->at(0);
                    lineOffset = sizeof(array_index_t) * face_factory->AddVertex(vec[0]);
                    face_factory->AddVertex(vec[1]);
                    for (int q = 1; q < lineCount; q++)
                    {
                        vec = lines->at(q);
                        face_factory->AddVertex(vec[0]);
                        face_factory->AddVertex(vec[1]);
                    }
                }
                if (triCount > 0)
                {
                    auto vec = tris->at(0);
                    triOffset = sizeof(array_index_t) * face_factory->AddVertex(vec[0]);
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
                    quadOffset = sizeof(array_index_t) * face_factory->AddVertex(vec[0]);
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

            SafeDelete(lines);
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
                if (lineCount)
                {
                    glDrawElements(GL_LINES, lineCount * 2, static_cast<GLenum>(ElementVboFactoryVboType), BUFFER_OFFSET(lineOffset));
                    checkForGlError();
                }
                if (triCount)
                {
                    glDrawElements(GL_TRIANGLES, triCount * 3, static_cast<GLenum>(ElementVboFactoryVboType), BUFFER_OFFSET(triOffset));
                    checkForGlError();
                }
                if (quadCount)
                {
                    glDrawElements(GL_QUADS, quadCount * 4, static_cast<GLenum>(ElementVboFactoryVboType), BUFFER_OFFSET(quadOffset));
                    checkForGlError();
                }
            }
            else if (tesselation == TesselationType::Lines)
            {
                if (triCount)
                {
                    glPatchParameteri(GL_PATCH_VERTICES, 2);
                    checkForGlError();
                    glDrawElements(GL_PATCHES, lineCount * 2, static_cast<GLenum>(ElementVboFactoryVboType), BUFFER_OFFSET(lineOffset));
                    checkForGlError();
                }
                assert(!triCount);
                assert(!quadCount);
            }
            else if (tesselation == TesselationType::Triangles)
            {
                if (triCount)
                {
                    glPatchParameteri(GL_PATCH_VERTICES, 3);
                    checkForGlError();
                    glDrawElements(GL_PATCHES, triCount * 3, static_cast<GLenum>(ElementVboFactoryVboType), BUFFER_OFFSET(triOffset));
                    checkForGlError();
                }
                assert(!triCount);
                assert(!quadCount);
            }
            else if (tesselation == TesselationType::Quads)
            {
                if (quadCount)
                {
                    glPatchParameteri(GL_PATCH_VERTICES, 4);
                    checkForGlError();
                    glDrawElements(GL_PATCHES, quadCount * 4, static_cast<GLenum>(ElementVboFactoryVboType), BUFFER_OFFSET(triOffset));
                    checkForGlError();
                }
                assert(!lineCount);
                assert(!triCount);
            }
            else assert(false);

            _factory->Pop();
        }

        void VboGraphicsSection::RenderInstanced(RenderStage* stage, unsigned instanceCount)
        {
            if (!*this) return;

            if (stage != material->GetRenderStage())
                return;

            _factory->Push();

            auto tesselation = material->GetTesselationType();
            if (tesselation == TesselationType::Disabled)
            {
                if (lineCount)
                {
                    glDrawElementsInstanced(GL_LINES, triCount * 2, static_cast<GLenum>(ElementVboFactoryVboType), BUFFER_OFFSET(lineOffset), instanceCount);
                    checkForGlError();
                }
                if (triCount)
                {
                    glDrawElementsInstanced(GL_TRIANGLES, triCount * 3, static_cast<GLenum>(ElementVboFactoryVboType), BUFFER_OFFSET(triOffset), instanceCount);
                    checkForGlError();
                }
                if (quadCount)
                {
                    glDrawElementsInstanced(GL_QUADS, quadCount * 4, static_cast<GLenum>(ElementVboFactoryVboType), BUFFER_OFFSET(quadOffset), instanceCount);
                    checkForGlError();
                }
            }
            else if (tesselation == TesselationType::Lines)
            {
                if (triCount)
                {
                    glPatchParameteri(GL_PATCH_VERTICES, 2);
                    checkForGlError();
                    glDrawElementsInstanced(GL_PATCHES, lineCount * 2, static_cast<GLenum>(ElementVboFactoryVboType), BUFFER_OFFSET(lineOffset), instanceCount);
                    checkForGlError();
                }
                assert(!triCount);
                assert(!quadCount);
            }
            else if (tesselation == TesselationType::Triangles)
            {
                if (triCount)
                {
                    glPatchParameteri(GL_PATCH_VERTICES, 3);
                    checkForGlError();
                    glDrawElementsInstanced(GL_PATCHES, triCount * 3, static_cast<GLenum>(ElementVboFactoryVboType), BUFFER_OFFSET(triOffset), instanceCount);
                    checkForGlError();
                }
                assert(!lineCount);
                assert(!quadCount);
            }
            else if (tesselation == TesselationType::Quads)
            {
                if (quadCount)
                {
                    glPatchParameteri(GL_PATCH_VERTICES, 4);
                    checkForGlError();
                    glDrawElementsInstanced(GL_PATCHES, quadCount * 4, static_cast<GLenum>(ElementVboFactoryVboType), BUFFER_OFFSET(triOffset), instanceCount);
                    checkForGlError();
                }
                assert(!lineCount);
                assert(!triCount);
            }
            else assert(false);

            _factory->Pop();
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
