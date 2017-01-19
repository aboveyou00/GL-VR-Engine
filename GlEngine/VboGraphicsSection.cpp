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
        VboGraphicsSection::VboGraphicsSection(Material *material, std::vector<ShaderFactory::IPropertyProvider*> &providers)
            : material(material),
              tris(new std::vector<Vector<3, uint16_t>>()),
              quads(new std::vector<Vector<4, uint16_t>>()),
              _factory(new ShaderFactory::ShaderFactory()),
              finalized(false)
        {
            _factory->AddPropertyProviders(providers);
            _factory->SetMaterial(material);
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

            SafeDelete(tris);
            SafeDelete(quads);
        }

        void VboGraphicsSection::Render(RenderTargetLayer layer)
        {
            if (!*this) return;

            if (layer != material->GetRenderTargetLayer())
                return;

            //material->Push(false);
            _factory->Push();

            auto tesselation = material->GetTesselationType();
            if (tesselation == TesselationType::Disabled)
            {
                if (triCount) glDrawElements(GL_TRIANGLES, triCount * 3, static_cast<GLenum>(VboType::UnsignedShort), BUFFER_OFFSET(triOffset));
                if (quadCount) glDrawElements(GL_QUADS, quadCount * 4, static_cast<GLenum>(VboType::UnsignedShort), BUFFER_OFFSET(quadOffset));
            }
            else if (tesselation == TesselationType::Triangles)
            {
                if (triCount)
                {
                    glPatchParameteri(GL_PATCH_VERTICES, 3);
                    glDrawElements(GL_PATCHES, triCount * 3, static_cast<GLenum>(VboType::UnsignedShort), BUFFER_OFFSET(triOffset));
                }
            }
            else if (tesselation == TesselationType::Quads)
            {
                if (quadCount)
                {
                    glPatchParameteri(GL_PATCH_VERTICES, 4);
                    glDrawElements(GL_PATCHES, quadCount * 4, static_cast<GLenum>(VboType::UnsignedShort), BUFFER_OFFSET(triOffset));
                }
            }
            else assert(false);

            _factory->Pop();
            //material->Pop(false);
        }

        void VboGraphicsSection::RenderInstanced(RenderTargetLayer layer, unsigned instanceCount)
        {
            layer; instanceCount;
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

        ShaderFactory::ShaderFactory &VboGraphicsSection::factory()
        {
            return *_factory;
        }

        VboGraphicsSection::operator bool()
        {
            return finalized && material && *material && _factory && *_factory;
        }
    }
}
