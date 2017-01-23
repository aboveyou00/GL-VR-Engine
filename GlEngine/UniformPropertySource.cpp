#include "stdafx.h"
#include "UniformPropertySource.h"
#include "Program.h"
#include "Snippet.h"

namespace GlEngine
{
    namespace ShaderFactory
    {
        UniformPropertySource::UniformPropertySource(std::vector<ShaderProp*> properties)
        {
            assert(properties.size() >= 1);
            for (size_t q = 0; q < properties.size(); q++)
            {
                assert(properties[q] != nullptr);
                _props.push_back(properties[q]);
            }
        }
        UniformPropertySource::~UniformPropertySource()
        {
        }

        bool UniformPropertySource::HasProperty(ShaderProp *prop)
        {
            return std::find(_props.begin(), _props.end(), prop) != _props.end();
        }

        const std::vector<ShaderProp*> UniformPropertySource::outProperties()
        {
            return _props;
        }

        void UniformPropertySource::Inject(Program*, ComponentType)
        {
        }

        void UniformPropertySource::ProvideInput(Program * program, ShaderProp * prop, ComponentType, ComponentType sourceType)
        {
            assert(HasProperty(prop));

            unsigned idx = program->FindOrCreateUniform(prop);
            program->components[sourceType]->uniforms[idx] = prop;
            if (!prop->isReadonly())
                program->components[sourceType]->AddIdentitySnippet(prop, true, false);
        }
    }
}
