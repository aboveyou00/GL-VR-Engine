#include "stdafx.h"
#include "GraphicsObjectImpl.h"
#include "OpenGl.h"

#include "VBOFactory.h"

namespace GlEngine
{
	namespace Impl
	{
		GraphicsObjectImpl::GraphicsObjectImpl() 
		{
            VboFactory<VboType::Float, Vector<3>, Vector<4>> factory(BufferMode::Array);

            factory.AddVertex({ 0, 0, 0 }, { 1.f, 0.f, 0.5f, 1.f });
            factory.AddVertex({ .5f, 0, 0 }, { 1.f, 0.f, 0.5f, 1.f });
            factory.AddVertex({ 0, .5f, 0 }, { 1.f, 0.f, 0.5f, 1.f });

            factory.AddVertex({ 0, 0, 0 }, { 0.5f, 0.f, 1.f, 1.f });
            factory.AddVertex({ .2f, .5f, 0 }, { 0.5f, 0.f, 1.f, 1.f });
            factory.AddVertex({ .5f, .2f, 0 }, { 0.5f, 0.f, 1.f, 1.f });

            arrayVbo = factory.Compile();
            


            VboFactory<VboType::UnsignedInt, unsigned, unsigned, unsigned> elFactory(BufferMode::ElementArray);

            elFactory.AddVertex(0, 1, 2);
            elFactory.AddVertex(3, 4, 5);

            elementVbo = elFactory.Compile();
		}
		
		GraphicsObjectImpl::~GraphicsObjectImpl() 
		{
		}

		void GraphicsObjectImpl::Render()
		{
            arrayVbo.MakeCurrent();
            elementVbo.MakeCurrent();


		}
	}
}