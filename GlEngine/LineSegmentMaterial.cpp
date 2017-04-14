#include "stdafx.h"
#include "LineSegmentMaterial.h"
#include "Attribute.h"

namespace GlEngine
{
    LineSegmentMaterial::LineSegmentMaterial(bool is2d)
        : Material("LineSegmentMaterial"s, is2d)
    {
    }
    LineSegmentMaterial::~LineSegmentMaterial()
    {
    }

    void LineSegmentMaterial::Push(ShaderFactory::ShaderFactory&)
    {
    }
    
    std::vector<ShaderFactory::ShaderProp*> LineSegmentMaterial::properties()
    {
        return { };
    }
    std::vector<ShaderFactory::Attribute*> LineSegmentMaterial::attributes()
    {
        return {
            &ShaderFactory::attr_GlPosition,
            &ShaderFactory::attr_LineSegments
        };
    }

    bool LineSegmentMaterial::IsOpaque()
    {
        return false;
    }
    TesselationType LineSegmentMaterial::GetTesselationType()
    {
        return TesselationType::Disabled;
    }
}
