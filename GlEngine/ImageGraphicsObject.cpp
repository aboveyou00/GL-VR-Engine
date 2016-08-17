#include "stdafx.h"
#include "ImageGraphicsObject.h"
#include <unordered_map>
#include "Shader.h"

namespace GlEngine
{
	ImageGraphicsObject::ImageGraphicsObject(const char * const filename, const char * const shaderName)
		: filename(filename), shaderName(shaderName)
	{
	}
	ImageGraphicsObject::ImageGraphicsObject(Texture * texture, const char * const shaderName)
		: filename(""), texture(texture), shaderName(shaderName)
	{
	}

	ImageGraphicsObject::~ImageGraphicsObject()
	{
	}

	ImageGraphicsObject * ImageGraphicsObject::Create(const char * const filename, const char * const shaderName)
	{
		static std::unordered_map<const char*, ImageGraphicsObject*> cache;
		auto ptr = cache[filename];
		if (ptr == nullptr) ptr = cache[filename] = new ImageGraphicsObject(filename, shaderName);
		return ptr;
	}

	ImageGraphicsObject * ImageGraphicsObject::Create(Texture * texture, const char * const shaderName)
	{
		static std::unordered_map<Texture*, ImageGraphicsObject*> cache;
		auto ptr = cache[texture];
		if (ptr == nullptr) ptr = cache[texture] = new ImageGraphicsObject(texture, shaderName);
		return ptr;
	}

	bool ImageGraphicsObject::Initialize()
	{
		if (strcmp(filename, "") != 0)
			texture = Texture::FromFile(filename);

		AddVertex({ 0, 0, 0 }, { 0, 0 }, { 0, 0, 1 });
		AddVertex({ 1, 0, 0 }, { 1, 0 }, { 0, 0, 1 });
		AddVertex({ 0, 1, 0 }, { 0, 1 }, { 0, 0, 1 });
		AddVertex({ 1, 1, 0 }, { 1, 1 }, { 0, 0, 1 });

		shader = Shader::Create("Shaders", shaderName);

		SetGraphics(shader, texture);
		AddTriangle({ 0, 1, 3 });
		AddTriangle({ 0, 3, 2 });

		return true;
	}

	void ImageGraphicsObject::Shutdown()
	{
	}

	const char * ImageGraphicsObject::name()
	{
		return "ImageGraphicsObject";
	}

	const char * const ImageGraphicsObject::GetFilename()
	{
		return filename;
	}
	const char * const ImageGraphicsObject::GetShaderName()
	{
		return shaderName;
	}
	Texture * ImageGraphicsObject::GetTexture()
	{
		return texture;
	}
	Shader * ImageGraphicsObject::GetShader()
	{
		return shader;
	}
}