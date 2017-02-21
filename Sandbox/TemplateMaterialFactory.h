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
    template <typename T, typename U>
    TemplateMaterialFactory *ProvideConst(GlEngine::ShaderFactory::Property<T> *prop, U value)
    {
        return provide_const_impl(prop, value);
    }
    template <typename T, unsigned SIZE>
    TemplateMaterialFactory *ProvideArray(GlEngine::ShaderFactory::Property<GlEngine::ShaderFactory::Array<T, SIZE>> *prop, T*& value, size_t count = SIZE)
    {
        return provide_array_impl(prop, value, count);
    }

    template <>
    TemplateMaterialFactory *Provide(GlEngine::ShaderFactory::Property<GlEngine::Texture*> *prop, GlEngine::Texture *&value)
    {
        if (value != nullptr) Await(value);
        return provide_impl(prop, value);
    }
    template <>
    TemplateMaterialFactory *ProvideConst(GlEngine::ShaderFactory::Property<GlEngine::Texture*> *prop, GlEngine::Texture *value)
    {
        if (value != nullptr) Await(value);
        return provide_const_impl(prop, value);
    }
    TemplateMaterialFactory *Await(GlEngine::IAsyncInitializable *c);

private:
    bool finalized;
    std::string _name;
    std::vector<std::function<void(TemplateMaterial*, GlEngine::ShaderFactory::ShaderFactory&)>> _pushFns;
    std::vector<GlEngine::ShaderFactory::ShaderProp*> _props;
    std::vector<GlEngine::ShaderFactory::Attribute*> _attrs;
    std::vector<GlEngine::IAsyncInitializable*> _awaiting;

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
    template <typename T, typename U>
    TemplateMaterialFactory *provide_const_impl(GlEngine::ShaderFactory::Property<T> *prop, U value)
    {
        assert(!finalized);
        this->_props.push_back(prop);
        _pushFns.push_back([prop, value](TemplateMaterial*, GlEngine::ShaderFactory::ShaderFactory &factory)
        {
            T t = dynamic_cast<T>(value);
            factory.ProvideProperty(*prop, t);
        });
        return this;
    }
    template <typename T, unsigned SIZE>
    TemplateMaterialFactory* provide_array_impl(GlEngine::ShaderFactory::Property<GlEngine::ShaderFactory::Array<T, SIZE>>* prop, T*& value, size_t count)
    {
        assert(!finalized);
        this->_props.push_back(prop);
        _pushFns.push_back([prop, &value, count](TemplateMaterial*, GlEngine::ShaderFactory::ShaderFactory &factory)
        {
            for (size_t i = 0; i < count; i++)
                factory.ProvideArrayProperty(*prop, value[i]);
        });
        return this;
    }
};
