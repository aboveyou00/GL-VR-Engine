#pragma once

#include "ComponentArray.h"
#include "Snippet.h"

namespace GlEngine
{
    namespace ShaderFactory
    {
        class ENGINE_SHARED Attribute
        {
        public:
            Attribute(ComponentArray<std::vector<Snippet*>> snippets, std::vector<Attribute*> dependentAttrs = {});
            ~Attribute();

            const std::vector<Attribute*> &dependentAttributes() const;
            const ComponentArray<std::vector<Snippet*>> &snippets() const;

        private:
            std::vector<Attribute*> _dependentAttrs;
            ComponentArray<std::vector<Snippet*>> _snippets;
        };

#pragma region position
        extern ENGINE_SHARED Attribute attr_GlPosition;
#pragma endregion

#pragma region lighting
        extern ENGINE_SHARED Attribute attr_SpecularLight;
        extern ENGINE_SHARED Attribute attr_DiffuseLight;
        extern ENGINE_SHARED Attribute attr_DiffuseLightFlat;

        extern ENGINE_SHARED Attribute attr_SpecularOnly;
        extern ENGINE_SHARED Attribute attr_DiffuseOnly;
        extern ENGINE_SHARED Attribute attr_AmbientOnly;

        extern ENGINE_SHARED Attribute attr_AmbientDiffuse;

        extern ENGINE_SHARED Attribute attr_Phong;
        extern ENGINE_SHARED Attribute attr_PhongFlat;
        extern ENGINE_SHARED Attribute attr_BlinnPhong;

        extern ENGINE_SHARED Attribute attr_LightingFallbacks;
#pragma endregion
    }
}
