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
#include "OpenGl.h"

#include "Engine.h"
#include "ResourceLoader.h"

namespace GlEngine
{
    namespace ShaderFactory
    {
        ShaderFactory::ShaderFactory()
            : _mat(nullptr), _shader(nullptr), _providers({})
        {
            AddPropertyProvider(&Environment::GetInstance());
        }
        ShaderFactory::~ShaderFactory()
        {
            Shutdown();
        }

        void ShaderFactory::AddPropertyProvider(IPropertyProvider *provider)
        {
            _providers.push_back(provider);
        }
        void ShaderFactory::RemovePropertyProvider(IPropertyProvider *provider)
        {
            auto it = std::find(_providers.begin(), _providers.end(), provider);
            if (it != _providers.end()) _providers.erase(it);
            //TODO: check if program needs to be recompiled. (Have any of the provided properties been added or removed?)
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
            if (this->_mat != nullptr) RemovePropertyProvider(this->_mat);

            this->_mat = mat;
            this->_program = nullptr;
            this->_shader = nullptr;
            
            if (mat != nullptr)
            {
                AddPropertyProvider(mat);
                auto resources = Engine::GetInstance().GetServiceProvider().GetService<ResourceLoader>();
                resources->QueueInitialize(this, true);
            }
        }

        bool ShaderFactory::Initialize()
        {
            ScopedLock lock(_mux);

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

            for (size_t q = 0; q < _providers.size(); q++)
            {
                _providers[q]->Push(*this);
            }
        }
        void ShaderFactory::Pop()
        {
            ScopedLock lock(_mux);
            glEnable(GL_CULL_FACE);
            if (_shader != nullptr) _shader->Pop();
        }

        ShaderFactory::operator bool()
        {
            ScopedLock lock(_mux);
            return _shader != nullptr && !!*_shader;
        }

        const char *ShaderFactory::name()
        {
            return "ShaderFactory";
        }
    }
}
