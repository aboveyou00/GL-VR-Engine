#pragma once
#include "ComponentArray.h"
#include "PropertySource.h"

namespace GlEngine
{
    namespace ShaderFactory
    {
        class ENGINE_SHARED Attribute
        {
        public:
            Attribute(std::vector<PropertySource*> propertySources, std::vector<PropertySource*> fallbackSources = {}, std::vector<Attribute*> dependentAttrs = {});
            ~Attribute();

            const std::vector<Attribute*> &dependentAttributes() const;
            const std::vector<PropertySource*> propertySources() const;
            const std::vector<PropertySource*> fallbackSources() const;

        private:
            std::vector<Attribute*> _dependentAttrs;
            std::vector<PropertySource*> _propertySources;
            std::vector<PropertySource*> _fallbackSources;
        };

#pragma region outcolor
        extern ENGINE_SHARED Attribute attr_OutColor;
#pragma endregion

#pragma region base-color
        extern ENGINE_SHARED Attribute attr_RgbBaseColor;
        extern ENGINE_SHARED Attribute attr_TextureBaseColor;
        extern ENGINE_SHARED Attribute attr_TwoTextureBaseColor;
        extern ENGINE_SHARED Attribute attr_AlphaMapDiscardBaseColor;
#pragma endregion

#pragma region position
        extern ENGINE_SHARED Attribute attr_GlPosition;
        extern ENGINE_SHARED Attribute attr_ModelViewNormal;
#pragma endregion

#pragma region lighting
        extern ENGINE_SHARED Attribute attr_DiffuseIntesity;

        extern ENGINE_SHARED Attribute attr_SpecularLight;
        extern ENGINE_SHARED Attribute attr_DiffuseLight;
        extern ENGINE_SHARED Attribute attr_DiffuseLightFlat;

        extern ENGINE_SHARED Attribute attr_PointLightDirection;

        extern ENGINE_SHARED Attribute attr_SpecularOnly;
        extern ENGINE_SHARED Attribute attr_DiffuseOnly;
        extern ENGINE_SHARED Attribute attr_AmbientOnly;

        extern ENGINE_SHARED Attribute attr_AmbientDiffuse;

        extern ENGINE_SHARED Attribute attr_Phong;
        extern ENGINE_SHARED Attribute attr_PhongFlat;
        extern ENGINE_SHARED Attribute attr_BlinnPhong;

        extern ENGINE_SHARED Attribute attr_CelShading;

        extern ENGINE_SHARED Attribute attr_Spotlight;

        extern ENGINE_SHARED Attribute attr_LightingFallbacks;

#pragma endregion
    }
}
