#include "stdafx.h"
#include "ObjGraphicsObject.h"

#include "ObjLoader.h"

#include "Shader.h"
#include "Texture.h"
#include <unordered_map>

namespace GlEngine
{
    ObjGraphicsObject::ObjGraphicsObject(std::string name, const char *const filename, std::function<ShaderFactory::ShaderFactory*(Material*)> createFactory)
        : VboGraphicsObject(name, createFactory), filename(filename)
    {
    }

    ObjGraphicsObject *ObjGraphicsObject::Create(std::string name, const char *filename, Material *mat, std::vector<ShaderFactory::IPropertyProvider*> providers)
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

        auto ptr = new ObjGraphicsObject(name, filename);
        for (size_t q = 0; q < providers.size(); q++)
            ptr->AddPropertyProvider(providers[q]);
        ptr->SetMaterial(mat);
        return ptr;
    }

    bool ObjGraphicsObject::InitializeAsync()
    {
        if (!GlEngine::ObjLoader::Load(filename, this))
            return false;
        return VboGraphicsObject::InitializeAsync();
    }
}
