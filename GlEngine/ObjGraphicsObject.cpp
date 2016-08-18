#include "stdafx.h"
#include "ObjGraphicsObject.h"

#include "ObjLoader.h"

#include "Shader.h"
#include "Texture.h"
#include <unordered_map>

namespace GlEngine
{
	ObjGraphicsObject::ObjGraphicsObject(const char *const filename)
        : filename(filename)
	{
	}
    ObjGraphicsObject::ObjGraphicsObject(const char *const filename, VaObject vao)
        : VboGraphicsObject(vao), filename(filename)
    {
    }
    ObjGraphicsObject::ObjGraphicsObject(const char *const filename, VaObject vao, Shader *shader, Texture *texture)
        : ObjGraphicsObject(filename, vao)
    {
        SetGraphics(shader, texture);
    }

    ObjGraphicsObject *ObjGraphicsObject::Create(const char *name, const char *shader_path, const char *shader_name, const char *texture_filename)
    {
        Shader *shader = Shader::Create(shader_path, shader_name);
        Texture *texture = Texture::FromFile(texture_filename);

        auto hashed = ([](const char *str, void *shader, void *texture) {
            int h = 0;
            while (*str)
                h = h << 1 ^ *str++;
            h = h << 1 ^ std::hash<void*>()(shader);
            h = h << 1 ^ std::hash<void*>()(texture);
            return h;
        })(name, shader, texture);

        static std::unordered_map<int, ObjGraphicsObject*> cache;
        auto ptr = cache[hashed];
        if (ptr == nullptr) ptr = cache[hashed] = new ObjGraphicsObject(name, VaObject(), shader, texture);
        return ptr;
    }

	bool ObjGraphicsObject::Initialize()
	{
		if (!GlEngine::ObjLoader::Load(filename, this))
			return false;
		return VboGraphicsObject::Initialize();
	}

    const char *ObjGraphicsObject::name()
    {
        return "ObjGraphicsObject";
    }
}
