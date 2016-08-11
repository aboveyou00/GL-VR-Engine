#include "stdafx.h"
#include "VboGraphicsObject.h"
#include "VboFactory.h"
#include "VboGraphicsSection.h"

namespace GlEngine
{
    VboGraphicsObject::VboGraphicsObject()
        : VboGraphicsObject(VbObject(), VbObject())
	{
	}
	VboGraphicsObject::VboGraphicsObject(VbObject arrayVbo, VbObject elementVbo)
		: arrayVbo(arrayVbo),
          elementVbo(elementVbo),
          finalized(!!arrayVbo && !!elementVbo),
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

        if (!arrayVbo)
        {
            if (verticesFactory == nullptr) return false;
            arrayVbo = verticesFactory->Compile();
            delete verticesFactory;
        }
        if (!elementVbo)
        {
            if (facesFactory == nullptr) return false;
            for (size_t q = 0; q < graphicsSections.size(); q++)
                graphicsSections[q]->Finalize(facesFactory);
            elementVbo = facesFactory->Compile();
            delete facesFactory;
        }

        return arrayVbo.InitializeGraphics() && elementVbo.InitializeGraphics();
    }
    void VboGraphicsObject::ShutdownGraphics()
    {
        arrayVbo.ShutdownGraphics();
        arrayVbo = VbObject();

        elementVbo.ShutdownGraphics();
        elementVbo = VbObject();
    }

    const char *VboGraphicsObject::name()
    {
        return "VboGraphicsObject";
    }

	void VboGraphicsObject::PreRender()
	{
		GraphicsObject::PreRender();
		if (*this)
		{
			arrayVbo.MakeCurrent();
			elementVbo.MakeCurrent();
		}
	}
	void VboGraphicsObject::RenderImpl()
	{
        if (*this)
            for (size_t q = 0; q < graphicsSections.size(); q++)
                graphicsSections[q]->Render();
	}

    VboGraphicsObject::operator bool()
    {
        return finalized && arrayVbo && elementVbo;
    }
}
