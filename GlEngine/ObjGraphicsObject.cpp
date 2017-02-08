#include "stdafx.h"
#include "ObjGraphicsObject.h"

#include "ObjLoader.h"

#include "Shader.h"
#include "Texture.h"
#include <unordered_map>

namespace GlEngine
{
    ObjGraphicsObject::ObjGraphicsObject(const char *const filename, std::function<ShaderFactory::ShaderFactory*(Material*)> createFactory)
        : VboGraphicsObject(createFactory), filename(filename)
    {
    }

    ObjGraphicsObject *ObjGraphicsObject::Create(const char *name, Material *mat, std::vector<ShaderFactory::IPropertyProvider*> providers)
    {
        //auto hashed = ([](const char *name, Material *mat) {
        //    unsigned h = 0;
        //    while (*name)
        //        h = h << 1 ^ *name++;
        //    return ((h << 3) ^ std::hash<Material*>()(mat));
        //})(name, mat);

        //static std::unordered_map<unsigned, ObjGraphicsObject*> cache;
        //auto ptr = cache[hashed];
        //if (ptr == nullptr) ptr = cache[hashed] = new ObjGraphicsObject(name, VaObject(), mat);
        //return ptr;

        auto ptr = new ObjGraphicsObject(name);
        for (size_t q = 0; q < providers.size(); q++)
            ptr->AddPropertyProvider(providers[q]);
        ptr->SetMaterial(mat);
        return ptr;
    }

    bool ObjGraphicsObject::Initialize()
    {
        if (!GlEngine::ObjLoader::Load(filename, this))
            return false;
        return VboGraphicsObject::Initialize();
    }

    std::string ObjGraphicsObject::name()
    {
        return "ObjGraphicsObject";
    }
}
