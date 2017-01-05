#include "stdafx.h"
#include "PropertySource.h"
#include "FactoryUtils.h"

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
            return ShaderFactory::PropertyName(prop, true);
        }
    }
}
