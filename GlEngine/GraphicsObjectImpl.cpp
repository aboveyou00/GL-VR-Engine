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

                factory.AddVertex({ 1.f, 0.f, 0.5f }, { 0, 0, 0 });
                factory.AddVertex({ 1.f, 0.f, 0.5f }, { .5f, 0, 0 });
                factory.AddVertex({ 1.f, 0.f, 0.5f }, { 0, .5f, 0 });

                factory.AddVertex({ 0.5f, 0.f, 1.f }, { 0, 0, 0 });
                factory.AddVertex({ 0.5f, 0.f, 1.f }, { .2f, .5f, 0 });
                factory.AddVertex({ 0.5f, 0.f, 1.f }, { .5f, .2f, 0 });

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
                glPushClientAttrib(GL_CLIENT_VERTEX_ARRAY_BIT);
                glEnableClientState(GL_VERTEX_ARRAY);

                arrayVbo.MakeCurrent();
                glInterleavedArrays(GL_C3F_V3F, sizeof(float) * 6, nullptr);

                //glDrawArrays(GL_TRIANGLES, 0, 18);
                elementVbo.MakeCurrent();
                glDrawElements(GL_TRIANGLES, 18, static_cast<GLenum>(VboType::UnsignedInt), nullptr);

                glPopClientAttrib();



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
}
