#pragma once

#include "VboGraphicsObject.h"

namespace GlEngine
{
	class ENGINE_SHARED ObjGraphicsObject : public VboGraphicsObject
	{
	public:
		ObjGraphicsObject() : VboGraphicsObject() {}
		ObjGraphicsObject(const char *const filename);
        ObjGraphicsObject(const char *const filename, VbObject arrayVbo, VbObject elementVbo);
        ObjGraphicsObject(const char *const filename, VbObject arrayVbo, VbObject elementVbo, Shader *shader, Texture *texture);

        static ObjGraphicsObject *Create(const char *name, const char *shader_path, const char *shader_name, const char *texture_filename = nullptr);

		bool Initialize() override;

        const char *name() override;

	private:
		const char * filename;
	};
}
