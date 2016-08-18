#include "stdafx.h"
#include "ImageGraphicsObject.h"
#include <unordered_map>
#include "Material.h"

namespace GlEngine
{
	ImageGraphicsObject::ImageGraphicsObject(Material * material)
		: filename(filename), material(material)
	{
	}

	ImageGraphicsObject::~ImageGraphicsObject()
	{
	}

	ImageGraphicsObject * ImageGraphicsObject::Create(Material * material)
	{
		static std::unordered_map<Material*, ImageGraphicsObject*> cache;
		auto ptr = cache[material];
		if (ptr == nullptr) ptr = cache[material] = new ImageGraphicsObject(material);
		return ptr;
	}

	bool ImageGraphicsObject::Initialize()
	{
		AddVertex({ 0, 0, 0 }, { 0, 0 }, { 0, 0, 1 });
		AddVertex({ 1, 0, 0 }, { 1, 0 }, { 0, 0, 1 });
		AddVertex({ 0, 1, 0 }, { 0, 1 }, { 0, 0, 1 });
		AddVertex({ 1, 1, 0 }, { 1, 1 }, { 0, 0, 1 });

		SetMaterial(material);
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
}