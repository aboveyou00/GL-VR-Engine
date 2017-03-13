#include "stdafx.h"
#include "WidgetObject.h"
#include "AmbientMaterial.h"
#include "AmbientLightSource.h"
#include "Texture.h"

WidgetObject::WidgetObject(std::string name)
    : GlEngine::VboGraphicsObject(name)
{
}
WidgetObject::~WidgetObject()
{
}

bool WidgetObject::InitializeAsync()
{
    if (!GlEngine::VboGraphicsObject::InitializeAsync()) return false;

    auto tex = GlEngine::Texture::FromFile("Textures/point-light-widget.png"s, GlEngine::TextureFlag::Translucent);
    auto mat = new GlEngine::AmbientMaterial(tex);// ({ 1.f, 1.f, 1.f });
    AddPropertyProvider(new GlEngine::AmbientLightSource(Vector<3> { 1, 1, 1 }));
    SetMaterial(mat);

    static const float x = -.1f, y = -.1f, z = -.1f;
    static const float w = 1.2f, h = 1.2f, d = 1.2f;
    int idx0, idx1, idx2, idx3;

    //Render face Xm
    idx0 = AddVertex({ x, y,     z }, { 0, 0 }, { -1, 0, 0 });
    idx1 = AddVertex({ x, y + h, z }, { 1, 0 }, { -1, 0, 0 });
    idx2 = AddVertex({ x, y + h, z + d }, { 1, 1 }, { -1, 0, 0 });
    idx3 = AddVertex({ x, y,     z + d }, { 0, 1 }, { -1, 0, 0 });

    AddTriangle({ idx0, idx1, idx2 });
    AddTriangle({ idx0, idx2, idx3 });

    //Render face Xp
    idx0 = AddVertex({ x + w, y,     z }, { 0, 0 }, { 1, 0, 0 });
    idx1 = AddVertex({ x + w, y + h, z }, { 1, 0 }, { 1, 0, 0 });
    idx2 = AddVertex({ x + w, y + h, z + d }, { 1, 1 }, { 1, 0, 0 });
    idx3 = AddVertex({ x + w, y,     z + d }, { 0, 1 }, { 1, 0, 0 });

    AddTriangle({ idx0, idx2, idx1 });
    AddTriangle({ idx0, idx3, idx2 });

    //Render face Ym
    idx0 = AddVertex({ x,     y, z }, { 0, 0 }, { 0, -1, 0 });
    idx1 = AddVertex({ x + w, y, z }, { 1, 0 }, { 0, -1, 0 });
    idx2 = AddVertex({ x + w, y, z + d }, { 1, 1 }, { 0, -1, 0 });
    idx3 = AddVertex({ x,     y, z + d }, { 0, 1 }, { 0, -1, 0 });

    AddTriangle({ idx0, idx2, idx1 });
    AddTriangle({ idx0, idx3, idx2 });

    //Render face Yp
    idx0 = AddVertex({ x,     y + h, z }, { 0, 0 }, { 0, 1, 0 });
    idx1 = AddVertex({ x + w, y + h, z }, { 1, 0 }, { 0, 1, 0 });
    idx2 = AddVertex({ x + w, y + h, z + d }, { 1, 1 }, { 0, 1, 0 });
    idx3 = AddVertex({ x,     y + h, z + d }, { 0, 1 }, { 0, 1, 0 });

    AddTriangle({ idx0, idx1, idx2 });
    AddTriangle({ idx0, idx2, idx3 });

    //Render face Zm
    idx0 = AddVertex({ x,     y,     z }, { 0, 0 }, { 0, 0, -1 });
    idx1 = AddVertex({ x + w, y,     z }, { 1, 0 }, { 0, 0, -1 });
    idx2 = AddVertex({ x + w, y + h, z }, { 1, 1 }, { 0, 0, -1 });
    idx3 = AddVertex({ x,     y + h, z }, { 0, 1 }, { 0, 0, -1 });

    AddTriangle({ idx0, idx1, idx2 });
    AddTriangle({ idx0, idx2, idx3 });

    //Render face Zp
    idx0 = AddVertex({ x,     y,     z + d }, { 0, 0 }, { 0, 0, 1 });
    idx1 = AddVertex({ x + w, y,     z + d }, { 1, 0 }, { 0, 0, 1 });
    idx2 = AddVertex({ x + w, y + h, z + d }, { 1, 1 }, { 0, 0, 1 });
    idx3 = AddVertex({ x,     y + h, z + d }, { 0, 1 }, { 0, 0, 1 });

    AddTriangle({ idx0, idx2, idx1 });
    AddTriangle({ idx0, idx3, idx2 });

    return true;
}
