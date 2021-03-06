#include "stdafx.h"
#include "StageGraphicsObject.h"
#include "PhongFogMaterial.h"
#include "Texture.h"

StageGraphicsObject::StageGraphicsObject(std::string name, bool defaultMaterial)
    : GlEngine::VboGraphicsObject(name), defaultMaterial(defaultMaterial)
{
}
StageGraphicsObject::~StageGraphicsObject()
{
}

bool StageGraphicsObject::InitializeAsync()
{
    auto tex1 = GlEngine::Texture::FromFile("Textures/grass0.png"s);
    auto tex2 = GlEngine::Texture::FromFile("Textures/grass1.png"s);
    if (defaultMaterial)
    {
        auto mat = new PhongFogMaterial(tex1, tex2, { .5f, .5f, .5f }, 6);
        SetMaterial(mat);
    }

    static const float x = -20.f, z = -20.f;
    int idx0, idx1, idx2, idx3;

    for (size_t q = 0; q < 40; q += 4)
    {
        for (size_t w = 0; w < 40; w += 4)
        {
            idx0 = AddVertex({ x + q,     0, z + w     }, { q / 10.f,       w / 10.f       }, { 0, 1, 0 });
            idx1 = AddVertex({ x + q + 4, 0, z + w     }, { (q + 4) / 10.f, w / 10.f       }, { 0, 1, 0 });
            idx2 = AddVertex({ x + q + 4, 0, z + w + 4 }, { (q + 4) / 10.f, (w + 4) / 10.f }, { 0, 1, 0 });
            idx3 = AddVertex({ x + q,     0, z + w + 4 }, { q / 10.f,       (w + 4) / 10.f }, { 0, 1, 0 });

            AddTriangle({ idx0, idx1, idx2 });
            AddTriangle({ idx0, idx2, idx3 });
        }
    }

    return true;
}
