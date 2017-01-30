#pragma once

#include "GameObject.h"
#include "IPropertyProvider.h"
#include "LightSourceGraphicsObject.h"
#include <map>

#include "PointLightSource.h"
#include "SpotLightSource.h"

template<typename T>
class LightSourceObject : public GlEngine::GameObject
{
public:
    LightSourceObject(T* lightSource = nullptr)
        : _lightSource(lightSource)
    {
        static_assert(std::is_base_of<GlEngine::ShaderFactory::IPropertyProvider, T>::value, "LightSourceObject template argument does not implement IPropertyProvider");
        if (_lightSource == nullptr) _lightSource = new T();
        RequireTick(true);
        Scale(.2f);
    }
    ~LightSourceObject()
    {
    }

    virtual void Tick(float delta) override
    {
        delta;
        SetPosition(lightSource()->position());
    }

    const char *name() override
    {
        return "LightSourceObject";
    }

    GlEngine::GraphicsObject *CreateGraphicsObject(GlEngine::GraphicsContext &ctx) override
    {
        ctx;
        return new LightSourceGraphicsObject();
    }

    T* lightSource()
    {
        return _lightSource;
    }

private:
    T* _lightSource;
    float movementSpeed;
};

typedef LightSourceObject<GlEngine::PointLightSource> PointLightSourceObject;
typedef LightSourceObject<GlEngine::SpotlightSource> SpotlightSourceObject;
