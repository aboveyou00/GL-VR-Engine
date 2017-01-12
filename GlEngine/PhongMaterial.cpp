#include "stdafx.h"
#include "PhongMaterial.h"
#include "Texture.h"
#include "Shader.h"
#include "Property.h"
#include "Attribute.h"
#include "ShaderFactory.h"

namespace GlEngine
{
    PhongMaterial::PhongMaterial(Vector<3> color, Vector<3> reflectionCoef)
        : texture(nullptr), color(color), reflectionCoef(reflectionCoef)
    {
    }
    PhongMaterial::PhongMaterial(Texture *texture, Vector<3> reflectionCoef)
        : texture(texture), reflectionCoef(reflectionCoef)
    {
    }
    PhongMaterial::~PhongMaterial()
    {
    }

    void PhongMaterial::Push(ShaderFactory::ShaderFactory &factory)
    {
        if (texture == nullptr)
        {
            factory.ProvideProperty(ShaderFactory::prop_RgbColor, color);
        }
        else
        {
            assert(false);
        }
        factory.ProvideProperty(ShaderFactory::prop_ReflectionCoefficient, reflectionCoef);

        //auto shader = instanced ? instancedShader : singleShader;
        //if (shader && *shader) shader->Push();
        //texture->Push();
    }
    //void PhongMaterial::Pop(bool instanced)
    //{
    //    instanced;
    //    texture->Pop();
    //    //auto shader = instanced ? instancedShader : singleShader;
    //    //if (shader && *shader) shader->Pop();
    //}

    bool PhongMaterial::IsOpaque()
    {
        if (texture == nullptr) return true;
        else return texture->IsOpaque();
    }

    TesselationType PhongMaterial::GetTesselationType()
    {
        return TesselationType::Disabled;
    }

    std::vector<ShaderFactory::ShaderProp*> PhongMaterial::properties()
    {
        if (texture == nullptr)
        {
            return {
                &ShaderFactory::prop_RgbColor,
                &ShaderFactory::prop_ReflectionCoefficient
            };
        }
        else
        {
            assert(false);
            return {};
            //return {
            //    &ShaderFactory::prop_Texture,
            //    &ShaderFactory::prop_ReflectionCoefficient
            //};
        }
    }
    std::vector<ShaderFactory::Attribute*> PhongMaterial::attributes()
    {
        return {
            &ShaderFactory::attr_GlPosition,
            &ShaderFactory::attr_Phong
        };
    }

    const char *PhongMaterial::name()
    {
        return "PhongMaterial";
    }
    PhongMaterial::operator bool()
    {
        if (texture == nullptr) return true;
        return !!*texture;
    }
}
