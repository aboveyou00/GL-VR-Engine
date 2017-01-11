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

            void AddPropertyProviders(std::vector<IPropertyProvider*> providers, bool recompile = true);
            
            template<typename... T>
            void AddPropertyProviders(IPropertyProvider* first, T... providers)
            {
                T arr[] = { providers... };
                _providers.insert(_providers.end(), arr, arr + sizeof...(providers) + 1);
                if (RefreshPropertyCache())
                    Recompile();
            }
            
            void RemovePropertyProviders(std::vector<IPropertyProvider*> providers, bool recompile = true);
            
            template<typename... T>
            void RemovePropertyProviders(IPropertyProvider* first, T... providers)
            {
                T arr[] = { first, providers... };
                for (int i = 0; i < sizeof...(providers) + 1; i++)
                {
                    auto it = std::find(_providers.begin(), _providers.end(), arr[i]);
                    if (it != _providers.end())
                        _providers.erase(it);
                }
                if (RefreshPropertyCache())
                    Recompile();
            }
            
            void AddRemovePropertyProviders(std::vector<IPropertyProvider*> addProviders, std::vector<IPropertyProvider*> removeProviders, bool recompile = true);

            Material *material();
            void SetMaterial(Material *mat);

            virtual bool Initialize() override;
            virtual void Shutdown() override;

            virtual bool InitializeGraphics() override;
            virtual void ShutdownGraphics() override;

            void Push();
            void Pop();

            void Recompile();

            template <typename T>
            void ProvideProperty(Property<T> &prop, const T &val)
            {
                assert(!!this);
                auto uniformLocation = _program->FindUniform(&prop);
                if (uniformLocation != -1) PropertyType_attribs<T>::set_gl_uniform(uniformLocation, val);
            }

            virtual operator bool() override;
            
            virtual const char *name() override;
            
        private:
            Material *_mat;
            Program *_program;
            Shader *_shader;
            std::vector<IPropertyProvider*> _providers;
            std::set<ShaderProp*> _properties;

            bool RefreshPropertyCache();
        };
    }
}
