#pragma once

#include "IGraphicsComponent.h"
#include "Property.h"
#include "Program.h"
#include "PropertyType_attribs.h"

namespace GlEngine
{
    class Material;

    namespace ShaderFactory
    {
        class Shader;
        class IPropertyProvider;

        class ENGINE_SHARED ShaderFactory : public IGraphicsComponent
        {
        public:
            ShaderFactory();
            ~ShaderFactory();

            void AddPropertyProviders(std::vector<IPropertyProvider*> providers);
            
            template<typename... T>
            void AddPropertyProviders(IPropertyProvider* first, T... providers)
            {
                IPropertyProvider* arr[] = { first, providers... };
                _providers.insert(_providers.end(), arr, arr + sizeof...(providers) + 1);
                //if (RefreshPropertyCache())
                //    Recompile();
            }
            
            void RemovePropertyProviders(std::vector<IPropertyProvider*> providers);
            
            template<typename... T>
            void RemovePropertyProviders(IPropertyProvider* first, T... providers)
            {
                IPropertyProvider* arr[] = { first, providers... };
                for (int i = 0; i < sizeof...(providers) + 1; i++)
                {
                    auto it = std::find(_providers.begin(), _providers.end(), arr[i]);
                    if (it != _providers.end())
                        _providers.erase(it);
                }
                //if (RefreshPropertyCache())
                //    Recompile();
            }
            
            void AddRemovePropertyProviders(std::vector<IPropertyProvider*> addProviders, std::vector<IPropertyProvider*> removeProviders);

            Material *material();
            void SetMaterial(Material *mat);

            virtual bool Initialize() override;
            virtual void Shutdown() override;

            virtual bool InitializeGraphics() override;
            virtual void ShutdownGraphics() override;

            virtual void Push();
            virtual void Pop();

            virtual void Recompile();

            template <typename T>
            void ProvideProperty(Property<T> &prop, const T &val)
            {
                assert(!!this);
                if (_program == nullptr)
                    return;
                auto uniformLocation = _program->FindUniform(&prop);
                if (uniformLocation != -1) PropertyType_attribs<T>::set_glsl_uniform(uniformLocation, val);
            }

            template <typename TElem, unsigned size_arr, typename... TArgs>
            void ProvideArrayProperty(Property<Array<TElem, size_arr>> &prop, TArgs... args)
            {
                static_assert(sizeof...(args) <= size_arr, "This array isn't big enough to fit so many arguments!");
                assert(!!this);

                auto idx = _arrayIndices[&prop];
                assert(idx + sizeof...(args) <= size_arr);
                _arrayIndices[&prop] += sizeof...(args);

                auto uniformLocation = _program->FindUniform(&prop);
                if (uniformLocation == -1) return;
                constexpr auto uniform_size = PropertyType_attribs<TElem>::glsl_uniform_size();
                uniformLocation += uniform_size * idx;

                //((PropertyType_attribs<TElem>::set_glsl_uniform(uniformLocation, args), uniformLocation += layout_size) + ... + 0);
                compound_PropertyType_attribs<TArgs...>::set_glsl_uniform(uniformLocation, args...);
            }

            template <typename... TArgs>
            void ProvideStructProperty(Property<Struct<TArgs...>> &prop, TArgs... args)
            {
                ProvideProperty(prop, Struct(args...));
            }
            template <typename... TArgs, unsigned size_arr>
            void ProvideStructProperty(Property<Array<Struct<TArgs...>, size_arr>> &prop, TArgs... args)
            {
                ProvideArrayProperty(prop, Struct<TArgs...>(args...));
            }

            virtual operator bool() override;
            
            virtual const char *name() override;

        protected:
            Material *_mat;
            Program *_program;
            Shader *_shader;
            std::vector<IPropertyProvider*> _providers;
            std::set<ShaderProp*> _properties;

            bool RefreshPropertyCache();
            std::map<unsigned, Texture *> _textures;
            std::map<ShaderProp*, unsigned> _arrayIndices;

            rt_mutex _mux;
        };

        template <>
        ENGINE_SHARED void ShaderFactory::ProvideProperty<Texture*>(Property<Texture*> &prop, Texture *const &val);
    }
}
