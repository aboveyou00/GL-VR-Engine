#include "stdafx.h"
#include "VboPropertySource.h"
#include "Program.h"

namespace GlEngine
{
    namespace ShaderFactory
    {
        VboPropertySource::VboPropertySource(const std::vector<ShaderProp*> properties, PropertySourceFlag flags)
            : PropertySource(flags, { ComponentType::Input })
        {
            assert(properties.size() >= 1);
            for (size_t q = 0; q < properties.size(); q++)
            {
                assert(properties[q] != nullptr);
                _props.push_back(properties[q]);
            }
        }
        VboPropertySource::~VboPropertySource()
        {
        }

        bool VboPropertySource::HasProperty(ShaderProp *prop)
        {
            return std::find(_props.begin(), _props.end(), prop) != _props.end();
        }
        const std::vector<ShaderProp*> VboPropertySource::outProperties()
        {
            return _props;
        }
        void VboPropertySource::Inject(Program *program, ComponentType type)
        {
            auto &vboOuts = program->components[ComponentType::Input]->outs;

            for (auto prop : _props)
            {
                auto it = std::find(_props.begin(), _props.end(), prop);
                assert(it != _props.end());
                auto idx = it - _props.begin();
            
                assert(vboOuts[idx] == nullptr);
                vboOuts[idx] = prop;

                program->ConnectComponentsProperty(ComponentType::Input, type, prop);
            }
        }
    }
}
