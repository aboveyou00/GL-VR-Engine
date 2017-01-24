#include "stdafx.h"
#include "LightSourceObject.h"
//#include "LightSourceGraphicsObject.h"
//#include "PointLightSource.h"
//
//LightSourceObject::LightSourceObject(GlEngine::ShaderFactory::IPropertyProvider *lightSource, float movementSpeed)
//    : _lightSource(lightSource), movementSpeed(movementSpeed)
//{
//    RequireTick(true);
//    if (_lightSource == nullptr) _lightSource = new GlEngine::PointLightSource();
//    Scale(.2f);
//}
//LightSourceObject::~LightSourceObject()
//{
//}
//
//void LightSourceObject::Tick(float delta)
//{
//    delta;
//    SetPosition(lightSource()->position());
//}
//
//const char *LightSourceObject::name()
//{
//    return "LightSourceObject";
//}
//
//GlEngine::GraphicsObject *LightSourceObject::CreateGraphicsObject(GlEngine::GraphicsContext&)
//{
//    return new LightSourceGraphicsObject();
//}
//
//GlEngine::PointLightSource *LightSourceObject::lightSource()
//{
//    return _lightSource;
//}
