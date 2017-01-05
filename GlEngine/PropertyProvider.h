#pragma once

#include "Property.h"

namespace GlEngine
{
    namespace ShaderFactory
    {
        class PropertyProvider
        {
        public:
            PropertyProvider();
            ~PropertyProvider();

            bool HasPropertyValue(ShaderProp* prop);
        };
    }
}
