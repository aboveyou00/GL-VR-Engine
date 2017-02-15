#include "stdafx.h"

#include "ShaderFactory.h"
#include "PathUtils.h"
#include "LogUtils.h"

#include "Program.h"
#include "VboPropertySource.h"
#include "UniformPropertySource.h"
#include "Material.h"

#include "Shader.h"
#include "Texture.h"
#include "Environment.h"
#include "OpenGl.h"

#include "Engine.h"
#include "ResourceLoader.h"
#include "Attribute.h"
#include <sstream>

namespace GlEngine
{
    namespace ShaderFactory
    {
        ShaderFactory::ShaderFactory()
            : _mat(nullptr), _shader(nullptr), _providers({})
        {
            AddPropertyProviders(&Environment::GetInstance());
        }
        ShaderFactory::~ShaderFactory()
        {
            Shutdown();
        }

        void ShaderFactory::AddPropertySource(PropertySource *source)
        {
            _sources.push_back(source);
        }
        void ShaderFactory::AddPropertyProviders(std::vector<IPropertyProvider*> providers)
        {
            for (auto provider : providers)
                _providers.push_back(provider);

            //if (RefreshPropertyCache())
            //    Recompile();
        }
        void ShaderFactory::RemovePropertyProviders(std::vector<IPropertyProvider*> providers)
        {
            for (auto provider : providers)
            {
                auto it = std::find(_providers.begin(), _providers.end(), provider);
                if (it != _providers.end()) _providers.erase(it);
            }

            //if (RefreshPropertyCache())
            //    Recompile();
        }

        void ShaderFactory::AddRemovePropertyProviders(std::vector<IPropertyProvider*> addProviders, std::vector<IPropertyProvider*> removeProviders)
        {
            AddPropertyProviders(addProviders);
            RemovePropertyProviders(removeProviders);

            //if (RefreshPropertyCache())
            //    Recompile();
        }

        Material *ShaderFactory::material()
        {
            ScopedLock lock(_mux);
            return _mat;
        }
        void ShaderFactory::SetMaterial(Material *mat)
        {
            ScopedLock lock(_mux);

            if (mat == this->_mat) return;
            if (this->_mat != nullptr) RemovePropertyProviders(this->_mat);

            this->_mat = mat;
            this->_program = nullptr;
            this->_shader = nullptr;
            
            if (mat != nullptr)
                AddPropertyProviders(mat);
        }

        bool ShaderFactory::Initialize()
        {
            ScopedLock lock(_mux);

            this->_program = new Program();

            for (size_t q = 0; q < _sources.size(); q++)
                this->_program->AddPropertySource(_sources[q]);
            //this->_program->AddPropertySource(new VboPropertySource(&prop_Position, &prop_UV, &prop_Normal));
            //this->_program->AddPropertySource(new VboPropertySource(&prop_Position));

            std::vector<ShaderProp*> properties;
            for (size_t q = 0; q < _providers.size(); q++)
            {
                auto provider_props = _providers[q]->properties();
                for (size_t w = 0; w < provider_props.size(); w++)
                {
                    properties.push_back(provider_props[w]);
                }
            }
            this->_program->AddPropertySource(new UniformPropertySource(properties));

            for (auto *attr : this->_mat->attributes())
                this->_program->AddAttribute(attr);

            auto *source = this->_program->Compile();
            this->_shader = Shader::Create(source);

            return true;
        }
        void ShaderFactory::Shutdown()
        {
        }
        bool ShaderFactory::InitializeGraphics()
        {
            return true;
        }
        void ShaderFactory::ShutdownGraphics()
        {
        }

        void ShaderFactory::Push()
        {
            ScopedLock lock(_mux);
            assert(!!*this);

            glDisable(GL_CULL_FACE); //TODO: remove this! This is temporary!

            _shader->Push();
            _textures.clear();
            _subroutines.clear();
            _arrayIndices.clear();
            for (size_t q = 0; q < _providers.size(); q++)
            {
                _providers[q]->Push(*this);
            }

            unsigned texIdx = 0;
            auto blend = false;
            for (auto &it : _textures)
            {
                if (!it.second->IsOpaque()) blend = true;
                it.second->Push(texIdx++);
                PropertyType_attribs<Texture*>::set_glsl_uniform(it.first, it.second);
            }
            if (blend)
            {
                glEnable(GL_BLEND);
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            }

            for (auto &it : _subroutines)
            {
                std::string name = it.second->name();
                unsigned idx = glGetSubroutineIndex(_shader->glslProgramIndex(), GL_FRAGMENT_SHADER, name.c_str());
                it.second->Push(idx);
                PropertyType_attribs<Subroutine*>::set_glsl_uniform(it.first, it.second);
            }

            //TODO: provide default values for unused indices in arrays
        }
        void ShaderFactory::Pop()
        {
            ScopedLock lock(_mux);

            glEnable(GL_CULL_FACE);
            glDisable(GL_BLEND);
            for (auto &it : _textures)
                it.second->Pop();

            if (_shader != nullptr) _shader->Pop();
        }

        void ShaderFactory::Recompile()
        {
            if (this_thread_type() != ThreadType::ResourceLoader)
            {
                auto resources = Engine::GetInstance().GetServiceProvider().GetService<ResourceLoader>();
                resources->QueueInitialize(this, true);
                return;
            }

            this->_program = nullptr;
            this->_shader = nullptr;

            this->_program = new Program();

            this->_program->AddPropertySource(new VboPropertySource(&prop_Position, &prop_UV, &prop_Normal));

            std::vector<ShaderProp*> properties;
            for (size_t q = 0; q < _providers.size(); q++)
            {
                auto provider_props = _providers[q]->properties();
                for (size_t w = 0; w < provider_props.size(); w++)
                {
                    properties.push_back(provider_props[w]);
                }
            }
            this->_program->AddPropertySource(new UniformPropertySource(properties));

            for (auto *attr : _mat->attributes())
                this->_program->AddAttribute(attr);

            auto *source = this->_program->Compile();
            this->_shader = Shader::Create(source);
        }

        ShaderFactory::operator bool()
        {
            ScopedLock lock(_mux);
            return _shader != nullptr && !!*_shader;
        }

        std::string ShaderFactory::name()
        {
            std::stringstream stream;
            stream << "ShaderFactory {";
            for (auto *attr : _mat->attributes())
                stream << " " << attr->name();
            stream << " }";
            return stream.str();
        }

        bool ShaderFactory::RefreshPropertyCache()
        {
            std::set<ShaderProp*> newProperties;
            for (IPropertyProvider* provider : _providers)
            {
                auto props = provider->properties();
                newProperties.insert(props.begin(), props.end());
            }
            if (_properties != newProperties)
            {
                _properties = newProperties;
                return true;
            }
            return false;
        }

        template <>
        void ShaderFactory::ProvideProperty<Texture*>(Property<Texture*> &prop, Texture *const &val)
        {
            assert(!!this);
            auto uniformLocation = _program->FindUniform(&prop);
            if (uniformLocation != -1) _textures[uniformLocation] = val;
        }

        template <>
        void ShaderFactory::ProvideProperty<Subroutine*>(Property<Subroutine*> &prop, Subroutine *const &val)
        {
            assert(!!this);
            auto uniformLocation = _program->FindUniform(&prop);
            if (uniformLocation != -1) _subroutines[uniformLocation] = val;
        }
    }
}
