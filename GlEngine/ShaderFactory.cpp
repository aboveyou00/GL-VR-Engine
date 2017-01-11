#include "stdafx.h"

#include "ShaderFactory.h"
#include "PathUtils.h"
#include "LogUtils.h"

#include "Program.h"
#include "VboPropertySource.h"
#include "UniformPropertySource.h"
#include "Material.h"

#include "Shader.h"
#include "Environment.h"

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

        void ShaderFactory::AddPropertyProviders(std::vector<IPropertyProvider*> providers, bool recompile)
        {
            for (auto provider : providers)
                _providers.push_back(provider);

            if (recompile && RefreshPropertyCache())
                Recompile();
        }
        void ShaderFactory::RemovePropertyProviders(std::vector<IPropertyProvider*> providers, bool recompile)
        {
            for (auto provider : providers)
            {
                auto it = std::find(_providers.begin(), _providers.end(), provider);
                if (it != _providers.end()) _providers.erase(it);
            }

            if (recompile && RefreshPropertyCache())
                Recompile();
        }

        void ShaderFactory::AddRemovePropertyProviders(std::vector<IPropertyProvider*> addProviders, std::vector<IPropertyProvider*> removeProviders, bool recompile)
        {
            AddPropertyProviders(addProviders, false);
            RemovePropertyProviders(removeProviders, false);

            if (recompile && RefreshPropertyCache())
                Recompile();
        }

        Material *ShaderFactory::material()
        {
            return _mat;
        }
        void ShaderFactory::SetMaterial(Material *mat)
        {
            if (mat == this->_mat) return;
            if (this->_mat != nullptr) (this->_mat); //?

            if (mat == nullptr) return;
            AddPropertyProviders(mat);

            this->_mat = mat;

            for (auto *attr : mat->attributes())
                this->_program->AddAttribute(attr);

            this->Recompile();
        }

        bool ShaderFactory::Initialize()
        {
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
            assert(!!*this);
            _shader->Push();

            for (size_t q = 0; q < _providers.size(); q++)
            {
                _providers[q]->Push(*this);
            }
        }
        void ShaderFactory::Pop()
        {
            if (_shader != nullptr) _shader->Pop();
        }

        void ShaderFactory::Recompile()
        {
            this->_program = nullptr;
            this->_shader = nullptr;

            this->_program = new Program(false, false);

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

            auto *source = this->_program->Compile();
            this->_shader = Shader::Create(source);

        }

        ShaderFactory::operator bool()
        {
            return _shader != nullptr && !!*_shader;
        }

        const char *ShaderFactory::name()
        {
            return "ShaderFactory";
        }
        bool ShaderFactory::RefreshPropertyCache()
        {
            std::set<ShaderProp*> newProperties;
            for (IPropertyProvider* provider : _providers)
                newProperties.insert(provider->properties().begin(), provider->properties().end());
            if (_properties != newProperties)
            {
                _properties = newProperties;
                return true;
            }
            return false;
        }
    }
}
