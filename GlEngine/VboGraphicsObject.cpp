#include "stdafx.h"
#include "VboGraphicsObject.h"
#include "VboFactory.h"
#include "VboGraphicsSection.h"
#include "VaoFactory.h"

#include "OpenGl.h"

namespace GlEngine
{
    VboGraphicsObject::VboGraphicsObject()
        : VboGraphicsObject(VaObject())
	{
	}
	VboGraphicsObject::VboGraphicsObject(VaObject vao)
		: _vao(vao),
          finalized(!!vao),
          elemIdx(0),
          currentGraphicsSection(nullptr),
          verticesFactory(finalized ? nullptr : new VboFactory<VboType::Float, Vector<3>, Vector<2>, Vector<3>>(BufferMode::Array)),
          facesFactory(finalized ? nullptr : new VboFactory<VboType::UnsignedShort, uint16_t>(BufferMode::ElementArray))
	{
	}
	VboGraphicsObject::~VboGraphicsObject()
	{
	}

    void VboGraphicsObject::SetGraphics(Shader *shader, Texture *texture)
    {
        assert(!finalized);
        if (currentGraphicsSection != nullptr && currentGraphicsSection->HasGraphics(shader, texture)) return;
        for (size_t q = 0; q < graphicsSections.size(); q++)
            if (graphicsSections[q]->HasGraphics(shader, texture))
            {
                currentGraphicsSection = graphicsSections[q];
                return;
            }
        graphicsSections.push_back(currentGraphicsSection = new Impl::VboGraphicsSection(shader, texture));
    }

    int VboGraphicsObject::AddVertex(Vector<3> position, Vector<2> texCoord, Vector<3> normal)
    {
        assert(!finalized);
        verticesFactory->AddVertex(position, texCoord, normal, false);
        return elemIdx++;
    }
    void VboGraphicsObject::AddTriangle(Vector<3, uint16_t> indices)
    {
        assert(!finalized);
        assert(currentGraphicsSection != nullptr);
        for (size_t q = 0; q < 3; q++)
            assert(indices[q] < elemIdx);
        currentGraphicsSection->AddTriangle(indices);
    }
    void VboGraphicsObject::AddQuad(Vector<4, uint16_t> indices)
    {
        assert(!finalized);
        for (size_t q = 0; q < 4; q++)
            assert(indices[q] < elemIdx);
        currentGraphicsSection->AddQuad(indices);
    }

	bool VboGraphicsObject::Initialize()
	{
		return true;
	}
    void VboGraphicsObject::Shutdown()
    {
    }
    bool VboGraphicsObject::InitializeGraphics()
    {
        if (finalized) return false;
        finalized = true;

        if (verticesFactory == nullptr) return false;
        if (facesFactory == nullptr) return false;

        for (size_t q = 0; q < graphicsSections.size(); q++)
            graphicsSections[q]->Finalize(facesFactory);

        _vao = VaoFactory::Begin()
            ->Add(verticesFactory)
            ->Add(facesFactory)
            ->Compile();

        delete verticesFactory;
        verticesFactory = nullptr;
        delete facesFactory;
        facesFactory = nullptr;

        return _vao.InitializeGraphics();
    }
    void VboGraphicsObject::ShutdownGraphics()
    {
        _vao.ShutdownGraphics();
        _vao = VaObject();
    }

    const char *VboGraphicsObject::name()
    {
        return "VboGraphicsObject";
    }

	void VboGraphicsObject::PreRender()
	{
		GraphicsObject::PreRender();
        if (*this) _vao.MakeCurrent();
	}
	void VboGraphicsObject::RenderImpl()
	{
        if (*this)
        {
            for (size_t q = 0; q < graphicsSections.size(); q++)
                graphicsSections[q]->Render();
        }
	}

    VboGraphicsObject::operator bool()
    {
        return finalized && _vao;
    }
}
