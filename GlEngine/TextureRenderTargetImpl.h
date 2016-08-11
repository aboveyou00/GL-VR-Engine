#pragma once

#include "RenderTargetImpl.h"
#include "Texture.h"

namespace GlEngine
{
	namespace Impl
	{
		class ENGINE_SHARED TextureRenderTargetImpl : RenderTargetImpl
		{
		public:
			TextureRenderTargetImpl(Texture * texture);
			~TextureRenderTargetImpl();

			virtual bool Initialize() override;
			virtual void Shutdown() override;

			virtual const char *name() override;

			bool alive = true;

			virtual void MakeCurrentTarget() override;

			virtual void Prepare() override;
			virtual void Push() override;
			virtual void Pop() override;

			virtual void Flip() override;

		protected:
			Texture * texture;
			GLuint frameBuffer;
			GLuint depthRenderBuffer;
		};
	}
}