#pragma once

#include "GameObject.h"
#include "IPropertyProvider.h"
#include "WidgetObject.h"
#include <map>

#include "PointLightSource.h"
#include "SpotLightSource.h"

template<typename T>
class LightSourceObject : public WidgetObject
{
public:
    LightSourceObject(std::string name, T* lightSource = nullptr)
        : WidgetObject(name), _lightSource(lightSource)
    {
        static_assert(std::is_base_of<GlEngine::ShaderFactory::IPropertyProvider, T>::value, "LightSourceObject template argument does not implement IPropertyProvider");
        if (_lightSource == nullptr) _lightSource = new T();
    }
    ~LightSourceObject()
    {
    }

    static GlEngine::GameObject *Create(GlEngine::Frame *frame, std::string name, T* lightSource = nullptr)
    {
        auto gobj = new GlEngine::GameObject(frame, name);
        gobj->AddComponent(new LightSourceObject<T>(name, lightSource));
        return gobj;
    }

    virtual void Tick(float) override
    {
        gameObject()->transform.position = lightSource()->position();
    }

    virtual std::string name() override
    {
        return "LightSourceObject";
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
