#pragma once

namespace GlEngine
{
    class Material;

    struct MtlLibMtl
    {
        MtlLibMtl();
        ~MtlLibMtl();

        std::string name;
        Vector<3> ambient, diffuse, specular;
        float specularExponent, opacity;
        unsigned illum;

        std::string ambientMap, diffuseMap, specularMap, specularExponentMap, alphaMap, bumpMap, displacementMap, decal;

        Material *CreateMaterial();
    };

    typedef std::map<std::string, Material*> MtlNameMap;
}
