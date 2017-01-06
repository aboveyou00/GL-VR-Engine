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
    ObjGraphicsObject::ObjGraphicsObject(const char *const filename, VaObject vao, Material *mat)
        : ObjGraphicsObject(filename, vao)
    {
        SetMaterial(mat);
    }

    ObjGraphicsObject *ObjGraphicsObject::Create(const char *name, Material *mat)
    {
        auto hashed = ([](const char *name, Material *mat) {
            unsigned h = 0;
            while (*name)
                h = h << 1 ^ *name++;
            return ((h << 3) ^ std::hash<Material*>()(mat));
        })(name, mat);

        static std::unordered_map<unsigned, ObjGraphicsObject*> cache;
        auto ptr = cache[hashed];
        if (ptr == nullptr) ptr = cache[hashed] = new ObjGraphicsObject(name, VaObject(), mat);
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
