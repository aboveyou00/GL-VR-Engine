#include "stdafx.h"
#include "RawShaderFactory.h"
#include "VboPropertySource.h"
#include "UniformPropertySource.h"
#include "IPropertyProvider.h"

namespace GlEngine::ShaderFactory
{
    RawShaderFactory::RawShaderFactory(ShaderSource* shaderSource, std::map<size_t, ShaderProp*>* uniforms)
        : _shaderSource(shaderSource), uniforms(uniforms)
    {
    }
    RawShaderFactory::~RawShaderFactory()
    {
    }
    bool RawShaderFactory::Initialize()
    {
        Recompile();
        return true;
    }
    void RawShaderFactory::Shutdown()
    {
    }
    bool RawShaderFactory::InitializeGraphics()
    {
        return true;
    }
    void RawShaderFactory::ShutdownGraphics()
    {
    }
    void RawShaderFactory::Recompile()
    {
        _program = new Program();
        _program->SetUniforms(*uniforms);

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

        _shader = Shader::Create(_shaderSource);
    }
    std::string RawShaderFactory::name()
    {
        return "RawShaderFactory";
    }
}
