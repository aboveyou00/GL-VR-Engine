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

                //factory.AddVertex({ 1.f, 0.f, 0.5f }, { 0, 0, 0 });
                //factory.AddVertex({ 1.f, 0.f, 0.5f }, { .5f, 0, 0 });
                //factory.AddVertex({ 1.f, 0.f, 0.5f }, { 0, .5f, 0 });

                //factory.AddVertex({ 0.5f, 0.f, 1.f }, { 0, 0, 0 });
                //factory.AddVertex({ 0.5f, 0.f, 1.f }, { .2f, .5f, 0 });
                //factory.AddVertex({ 0.5f, 0.f, 1.f }, { .5f, .2f, 0 });

                factory.AddVertex({ 0.4f, 0.f,  0.5f }, { 0, 0, 0 });
                factory.AddVertex({ 0.4f, 0.4f, 0.5f }, { .2f, .5f, 0 });
                factory.AddVertex({ 0.f,  0.4f, 0.5f }, { .5f, .2f, 0 });

                factory.AddVertex({ -0.6f, 0.f,  0.5f }, { 0, 0, 0 });
                factory.AddVertex({ -0.6f, 0.4f, 0.5f }, { .2f, .5f, 0 });
                factory.AddVertex({ -1.f,  0.4f, 0.5f }, { .5f, .2f, 0 });

                arrayVbo = factory.Compile();
                if (!arrayVbo.Initialize()) return false;



                //float vals[] = { 0.4f, 0,    0.5f, 0, 0, 0,
                //                 0.4f, 0.4f, 0.5f, 0, 0, 0,
                //                 0,    0.4f, 0.5f, 0, 0, 0 };

                //unsigned vboId;
                //glGenBuffers(1, &vboId);
                //glBindBuffer(static_cast<unsigned>(BufferMode::Array), vboId);

                //glBufferData(static_cast<unsigned>(BufferMode::Array), 3 * 6 * sizeof(float), vals, GL_STATIC_DRAW);

                //unsigned vao;
                //glGenVertexArrays(1, &vao);
                //glBindVertexArray(vao);

                //glVertexAttribPointer(0, 3, static_cast<unsigned>(VboType::Float), GL_FALSE, 6 * sizeof(float), nullptr);
                //glEnableVertexAttribArray(0);

                //arrayVbo = VbObject(vao, vboId, BufferMode::Array);
            }

            //if (!elementVbo)
            //{
            //    VboFactory<VboType::UnsignedInt, unsigned, unsigned, unsigned> elFactory(BufferMode::ElementArray);

            //    elFactory.AddVertex(0, 1, 2);
            //    elFactory.AddVertex(3, 4, 5);

            //    elementVbo = elFactory.Compile();
            //    if (!elementVbo.Initialize()) return false;
            //}

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
                glDrawArrays(GL_TRIANGLES, 0, 6);
            }

            //if (arrayVbo /*&& elementVbo*/)
            //{
            //    //glPushClientAttrib(GL_CLIENT_VERTEX_ARRAY_BIT);
            //    //glEnableClientState(GL_VERTEX_ARRAY);

            //    //arrayVbo.MakeCurrent();
            //    //glInterleavedArrays(GL_C3F_V3F, sizeof(float) * 6, nullptr);

            //    //glDrawArrays(GL_TRIANGLES, 0, 6);
            //    ////elementVbo.MakeCurrent();
            //    ////glDrawElements(GL_TRIANGLES, 6, static_cast<GLenum>(VboType::UnsignedInt), nullptr);

            //    //glPopClientAttrib();
            //    
            //    arrayVbo.MakeCurrent();
            //    glDrawArrays(GL_TRIANGLES, 0, 6);
            //}

            //glBegin(GL_TRIANGLES);
            //    
            //glColor3d(0.0, 1.0, 0.0);
            //    
            //glVertex3d(0.4, 0, 0.5);
            //glVertex3d(0.4, 0.4, 0.5);
            //glVertex3d(0, 0.4, 0.5);
            //    
            //glEnd();
		}
	}
}
