#include "stdafx.h"
#include "VboPropertySource.h"
#include "Program.h"

namespace GlEngine
{
    namespace ShaderFactory
    {
        bool VboPropertySource::HasProperty(ShaderProp *prop)
        {
            return std::find(_props.begin(), _props.end(), prop) != _props.end();
        }
        void VboPropertySource::ProvideProperty(ShaderProp *prop, Program *program, ComponentType type)
        {
            auto &vboOuts = program->components[ComponentType::Input]->outs;

            auto it = std::find(_props.begin(), _props.end(), prop);
            assert(it != _props.end());
            auto idx = it - _props.begin();
            
            assert(vboOuts[idx] == nullptr);
            vboOuts[idx] = prop;

            program->ConnectComponentsProperty(static_cast<unsigned>(ComponentType::Input), static_cast<unsigned>(type), prop);
        }
    }
}
