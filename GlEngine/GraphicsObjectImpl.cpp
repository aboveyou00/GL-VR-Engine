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
                VboFactory<VboType::Float, Vector<3>, Vector<3>> factory(BufferMode::Array);

                factory.AddVertex({ 0.4f, 0.f,  0.5f }, { 1, 0, 0 });
                factory.AddVertex({ 0.4f, 0.4f, 0.5f }, { 0, 1, 0 });
                factory.AddVertex({ 0.f,  0.4f, 0.5f }, { 0, 0, 1 });

                factory.AddVertex({ -0.6f, 0.f,  0.5f }, { 1, 1, 0 });
                factory.AddVertex({ -0.6f, 0.4f, 0.5f }, { 0, 1, 1 });
                factory.AddVertex({ -1.f,  0.4f, 0.5f }, { 1, 0, 1 });

                arrayVbo = factory.Compile();
                if (!arrayVbo.Initialize()) return false;
            }

            if (!shader)
            {
                shader = Shader("Shaders", "simple");
                if (!shader.Initialize()) return false;
            }

            if (!elementVbo)
            {
                VboFactory<VboType::UnsignedShort, uint16_t, uint16_t, uint16_t> elFactory(BufferMode::ElementArray);

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
            if (arrayVbo)
            {
                arrayVbo.MakeCurrent();
                if (shader) shader.MakeCurrent();
                if (elementVbo)
                {
                    elementVbo.MakeCurrent();
                    glDrawElements(GL_TRIANGLES, 6, static_cast<GLenum>(VboType::UnsignedShort), nullptr);
                }
                else glDrawArrays(GL_TRIANGLES, 0, 6);
            }
		}
	}
}
