#pragma once

#include "VboGraphicsObject.h"

namespace GlEngine
{
	class Material;

	class ENGINE_SHARED ImageGraphicsObject : public VboGraphicsObject<>
	{
	public:
		~ImageGraphicsObject();

		static ImageGraphicsObject * Create(Material * material);
		
		bool Initialize() override;
		void Shutdown() override;

		inline Material * GetMaterial() 
		{
			return material;
		}

	protected:
		ImageGraphicsObject(Material * material = nullptr);
		const char * const filename;
		Material * material;

		virtual const char * name() override;
	};
}