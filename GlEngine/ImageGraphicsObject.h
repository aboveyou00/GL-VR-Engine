#pragma once

#include "VboGraphicsObject.h"
#include "Texture.h"

namespace GlEngine
{
	class ENGINE_SHARED ImageGraphicsObject : public VboGraphicsObject<>
	{
	public:
		ImageGraphicsObject(const char * const filename, const char * const shaderName = "direct_light_tex");
		ImageGraphicsObject(Texture * texture, const char * const shaderName = "direct_light_tex");
		~ImageGraphicsObject();

		static ImageGraphicsObject * Create(const char * const filename, const char * const shaderName = "direct_light_tex");
		static ImageGraphicsObject * Create(Texture * texture, const char * const shaderName = "direct_light_tex");

		bool Initialize() override;
		void Shutdown() override;

		const char * const GetFilename();
		const char * const GetShaderName();
		Texture * GetTexture();
		Shader * GetShader();

	protected:
		const char * const filename;
		const char * const shaderName;
		Texture * texture;
		Shader * shader;

		virtual const char * name() override;
	};
}