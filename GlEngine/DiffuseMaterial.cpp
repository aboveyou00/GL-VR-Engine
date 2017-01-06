#include "stdafx.h"
#include "DiffuseMaterial.h"
#include "Shader.h"

#include "OpenGl.h"

namespace GlEngine
{
    DiffuseMaterial *DiffuseMaterial::Create(Vector<3> color)
    {
        static std::vector<DiffuseMaterial*> cache;
        for (auto ptr = cache.begin(); ptr != cache.end(); ptr++)
        {
            auto &mat = **ptr;
            if (mat.color == color) return &mat;
        }

        auto diffuse = new DiffuseMaterial(color);
        cache.push_back(diffuse);
        return diffuse;
    }

    DiffuseMaterial::DiffuseMaterial(Vector<3> color)
        : color(color), instancedShader(Shader::Create("Shaders", "diffuse.inst")), singleShader(Shader::Create("Shaders", "diffuse"))
    {
    }
    DiffuseMaterial::~DiffuseMaterial()
    {
    }

    void DiffuseMaterial::Push(bool instanced)
    {
        auto shader = instanced ? instancedShader : singleShader;
        if (shader && *shader) shader->Push();
        glUniform3f(5, color[0], color[1], color[2]);
    }
    void DiffuseMaterial::Pop(bool instanced)
    {
        auto shader = instanced ? instancedShader : singleShader;
        if (shader && *shader) shader->Pop();
    }

    bool DiffuseMaterial::IsOpaque()
    {
        return true;
    }

    TesselationType DiffuseMaterial::GetTesselationType()
    {
        return TesselationType::Disabled;
    }

    const char *DiffuseMaterial::name()
    {
        return "DiffuseMaterial";
    }
    DiffuseMaterial::operator bool()
    {
        return instancedShader && *instancedShader && singleShader && *singleShader;
    }
}
