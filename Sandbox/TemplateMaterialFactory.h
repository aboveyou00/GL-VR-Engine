#pragma once

#include "Attribute.h"
#include "Property.h"
#include "ShaderFactory.h"
#include "Texture.h"

class TemplateMaterial;

class TemplateMaterialFactory
{
private:
    TemplateMaterialFactory();
    ~TemplateMaterialFactory();

public:
    friend class TemplateMaterial;
    TemplateMaterial *Create();

    TemplateMaterialFactory *Name(std::string name);
    TemplateMaterialFactory *Attribute(GlEngine::ShaderFactory::Attribute *attr);
    template <typename T>
    TemplateMaterialFactory *Provide(GlEngine::ShaderFactory::Property<T> *prop, T &value)
    {
        return provide_impl(prop, value);
    }
    template <>
    TemplateMaterialFactory *Provide(GlEngine::ShaderFactory::Property<GlEngine::Texture*> *prop, GlEngine::Texture *&value)
    {
        if (value != nullptr) Await(value);
        return provide_impl(prop, value);
    }
    TemplateMaterialFactory *Await(GlEngine::IGraphicsComponent *c);

private:
    bool finalized;
    std::string _name;
    std::vector<std::function<void(TemplateMaterial*, GlEngine::ShaderFactory::ShaderFactory&)>> _pushFns;
    std::vector<GlEngine::ShaderFactory::ShaderProp*> _props;
    std::vector<GlEngine::ShaderFactory::Attribute*> _attrs;
    std::vector<GlEngine::IGraphicsComponent*> _awaiting;

    template <typename T>
    TemplateMaterialFactory *provide_impl(GlEngine::ShaderFactory::Property<T> *prop, T &value)
    {
        assert(!finalized);
        this->_props.push_back(prop);
        _pushFns.push_back([prop, &value](TemplateMaterial*, GlEngine::ShaderFactory::ShaderFactory &factory)
        {
            factory.ProvideProperty(*prop, value);
        });
        return this;
    }
};
