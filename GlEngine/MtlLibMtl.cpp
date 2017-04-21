#include "stdafx.h"
#include "MtlLibMtl.h"
#include "PhongMaterial.h"
#include "Texture.h"

namespace GlEngine
{
    MtlLibMtl::MtlLibMtl()
        : ambient({ .3, .3, .3 }), diffuse({ .3, .3, .3 }), specular({ .3, .3, .3 }), specularExponent(10), opacity(1.f), illum(0)
    {
    }
    MtlLibMtl::~MtlLibMtl()
    {
    }

    Material *MtlLibMtl::CreateMaterial()
    {
        //TODO: this still ignores most material options. (In particular, "diffuse", "opacity", and "illum")
        if (diffuseMap.length() > 0)
        {
            auto diffuseTex = Texture::FromFile(diffuseMap, TextureFlag::Translucent);
            if (alphaMap.length() > 0)
            {
                auto alphaTex = Texture::FromFile(alphaMap, TextureFlag::AlphaMap);
                return new PhongMaterial(diffuseTex, alphaTex, specular, specularExponent);
            }
            else if (bumpMap.length() > 0)
            {
                auto bumpTex = Texture::FromFile(bumpMap);
                return new PhongMaterial(diffuseTex, bumpTex, specular, specularExponent);
            }
            return new PhongMaterial(diffuseTex, specular, specularExponent);
        }
        else
        {
            //if (alphaMap.length() > 0)
            //{
            //    //TODO
            //    auto alphaTex = Texture::FromFile(alphaMap, TextureFlag::AlphaMap);
            //    return new PhongMaterial(diffuse, alphaTex, specular, specularExponent);
            //}
            //else if (bumpMap.length() > 0)
            //{
            //    //TODO
            //    auto bumpTex = Texture::FromFile(bumpMap);
            //    return new PhongMaterial(diffuse, bumpTex, specular, specularExponent);
            //}
            return new PhongMaterial(diffuse, specular, specularExponent);
        }
    }
}
