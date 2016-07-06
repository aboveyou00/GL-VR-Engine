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
                VboFactory<VboType::Float, Vector<3>, Vector<3>, Vector<3>> factory(BufferMode::Array);
                //Position, Color, Normal

                factory.AddVertex({ 0.4f, 0.f,  0.5f }, { 1, .5, .5 }, Vector<3>({ -1, -1, -1 }).Normalized());
                factory.AddVertex({ 0.4f, 0.4f, 0.5f }, { 1, .5, .5 }, Vector<3>({ 1, 1, -1 }).Normalized());
                factory.AddVertex({ 0.f,  0.4f, 0.5f }, { 1, .5, .5 }, Vector<3>({ -1, 1, -1 }).Normalized());

                factory.AddVertex({ -0.6f, 0.f,  0.5f }, { .5, 1, .5 }, Vector<3>({ 1, -1, -1 }).Normalized());
                factory.AddVertex({ -0.6f, 0.4f, 0.5f }, { .5, 1, .5 }, Vector<3>({ 1, 1, -1 }).Normalized());
                factory.AddVertex({ -1.f,  0.4f, 0.5f }, { .5, 1, .5 }, Vector<3>({ -1, -1, -1 }).Normalized());

                arrayVbo = factory.Compile();
                if (!arrayVbo.Initialize()) return false;
            }
            
            if (!elementVbo)
            {
                VboFactory<VboType::UnsignedShort, uint16_t, uint16_t, uint16_t> elFactory(BufferMode::ElementArray);

                elFactory.AddVertex(0, 1, 2);
                elFactory.AddVertex(3, 4, 5);

                elementVbo = elFactory.Compile();
                if (!elementVbo.Initialize()) return false;
            }

            if (!shader)
            {
                shader = Shader("Shaders", "direct_light");
                if (!shader.Initialize()) return false;
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

        //uniform vec3 direct_light_direction;
        //uniform vec3 direct_light_color;
        //uniform vec3 ambient_light_color;

		void GraphicsObjectImpl::Render()
		{
            if (arrayVbo)
            {
                arrayVbo.MakeCurrent();
                if (shader)
                {
                    shader.MakeCurrent();
                    glUniform3f(0, 1.f, 1.f, 1.f);
                    glUniform3f(1, .8f, .8f, .8f);
                    glUniform3f(2, .2f, .2f, .2f);
                }
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
