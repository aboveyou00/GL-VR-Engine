#pragma once

#include "FogInterpolationMode.h"
#include "IPropertyProvider.h"

namespace GlEngine
{
    class ENGINE_SHARED FogSource : public ShaderFactory::IPropertyProvider
    {
    public:
        FogSource(float mindist, float maxdist, Vector<4> color, FogInterpolationMode mode = FogInterpolationMode::Linear);
        ~FogSource();

        virtual void Push(ShaderFactory::ShaderFactory &factory) override;

        virtual std::vector<ShaderFactory::ShaderProp*> properties() override;

    private:
        float mindist, maxdist;
        Vector<4> color;
        FogInterpolationMode interpolationMode;
    };
}
