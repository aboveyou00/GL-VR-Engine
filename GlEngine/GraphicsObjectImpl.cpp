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
		}
		
		GraphicsObjectImpl::~GraphicsObjectImpl() 
		{
		}

        bool GraphicsObjectImpl::Initialize()
        {
            if (!arrayVbo)
            {
                VboFactory<VboType::Float, Vector<3>, Vector<4>> factory(BufferMode::Array);

                factory.AddVertex({ 0, 0, 0 }, { 1.f, 0.f, 0.5f, 1.f });
                factory.AddVertex({ .5f, 0, 0 }, { 1.f, 0.f, 0.5f, 1.f });
                factory.AddVertex({ 0, .5f, 0 }, { 1.f, 0.f, 0.5f, 1.f });

                factory.AddVertex({ 0, 0, 0 }, { 0.5f, 0.f, 1.f, 1.f });
                factory.AddVertex({ .2f, .5f, 0 }, { 0.5f, 0.f, 1.f, 1.f });
                factory.AddVertex({ .5f, .2f, 0 }, { 0.5f, 0.f, 1.f, 1.f });

                arrayVbo = factory.Compile();
                if (!arrayVbo.Initialize()) return false;
            }

            if (!elementVbo)
            {
                VboFactory<VboType::UnsignedInt, unsigned, unsigned, unsigned> elFactory(BufferMode::ElementArray);

                elFactory.AddVertex(0, 1, 2);
                elFactory.AddVertex(3, 4, 5);

                elementVbo = elFactory.Compile();
                if (!elementVbo.Initialize()) return false;
            }

            return true;
        }
        void GraphicsObjectImpl::Shutdown()
        {
            arrayVbo.Shutdown();
            arrayVbo = VbObject();

            elementVbo.Shutdown();
            elementVbo = VbObject();
        }

		void GraphicsObjectImpl::Render()
		{
            if (arrayVbo && elementVbo)
            {
                arrayVbo.MakeCurrent();
                elementVbo.MakeCurrent();

                //glDrawArrays(GL_TRIANGLES, 0, 2);
                glDrawElements(GL_TRIANGLES, 2, static_cast<GLenum>(VboType::UnsignedInt), nullptr);
            }
		}
	}
}