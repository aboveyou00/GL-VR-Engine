#pragma once

#include "RenderTargetImpl.h"
#include "Texture.h"

namespace GlEngine
{
	namespace Impl
	{
		class TextureRenderTargetImpl : public RenderTargetImpl
		{
		public:
			TextureRenderTargetImpl(unsigned width, unsigned height, bool hasAlphaChannel = false);
			~TextureRenderTargetImpl();

			virtual bool Initialize() override;
			virtual void Shutdown() override;

			virtual const char *name() override;

			bool alive = true;

			virtual void MakeCurrentTarget() override;

			virtual void Prepare() override;
			virtual void Push(RenderTargetLayer layer) override;
			virtual void Pop(RenderTargetLayer layer) override;

			virtual void Flip() override;

		protected:
			Texture * texture;
			GLuint frameBuffer;
			GLuint depthRenderBuffer;
		};
	}
}