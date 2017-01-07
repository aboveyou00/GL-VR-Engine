#include "stdafx.h"
#include "PropertySource.h"
#include "FactoryUtils.h"
#include "ShaderProp.h"

namespace GlEngine
{
    namespace ShaderFactory
    {
        PropertySource::PropertySource()
        {
        }
        PropertySource::~PropertySource()
        {
        }

        std::string PropertySource::PropertyName(ShaderProp * prop)
        {
            return prop->name;
        }
    }
}
