#include "stdafx.h"
#include "DialogBoxObject.h"
#include "Texture.h"
#include "Image2dGraphicsObject.h"

namespace TileRPG
{
    DialogBoxObject::DialogBoxObject()
        : DialogBoxObject((GlEngine::Texture*)nullptr)
    {
    }
    DialogBoxObject::DialogBoxObject(const char *textureSrc)
        : DialogBoxObject(GlEngine::Texture::FromFile(textureSrc))
    {
    }
    DialogBoxObject::DialogBoxObject(GlEngine::Texture *tex)
        : GameObject({ 0, 0/*180*/, 0 }), tex(tex)
    {
    }
    DialogBoxObject::~DialogBoxObject()
    {
    }

    const char *DialogBoxObject::name()
    {
        return "DialogBoxObject";
    }

    void DialogBoxObject::SetTextureSource(const char *textureSrc)
    {
        if (textureSrc == nullptr) SetTexture(nullptr);
        else if (tex == nullptr || strcmp(textureSrc, tex->GetSource()) != 0) SetTexture(GlEngine::Texture::FromFile(textureSrc));
    }
    void DialogBoxObject::SetTexture(GlEngine::Texture *tex)
    {
        this->tex = tex;
    }

    GlEngine::GraphicsObject *DialogBoxObject::CreateGraphicsObject(GlEngine::GraphicsContext&)
    {
        auto gobj = new GlEngine::Image2dGraphicsObject();
        gobj->SetTexture(tex);
        return gobj;
    }
    void DialogBoxObject::UpdateGraphicsObject(GlEngine::GraphicsContext&, GlEngine::GraphicsObject *object)
    {
        auto gobj = dynamic_cast<GlEngine::Image2dGraphicsObject*>(object);
        if (gobj == nullptr) return;
        gobj->SetTexture(tex);
    }
}
