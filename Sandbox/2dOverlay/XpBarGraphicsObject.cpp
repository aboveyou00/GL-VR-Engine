#include "stdafx.h"
#include "XpBarGraphicsObject.h"
#include "Texture.h"

XpBarGraphicsObject::XpBarGraphicsObject(XpBarGameObject *obj)
    : GlEngine::Image2dGraphicsObject(GlEngine::Texture::FromFile("Textures/xp-bar-overlay.png", GlEngine::TextureFlag::Translucent)),
      xpObj(obj)
{
    SetAlignment({ GlEngine::ImageComponentAlignment::Begin, GlEngine::ImageComponentAlignment::End });
}
XpBarGraphicsObject::~XpBarGraphicsObject()
{
}
