#include "stdafx.h"
#include "Material.h"

namespace GlEngine
{
    Material::Material(std::string name, bool is2d)
        : _name(name), is2d(is2d)
    {
    }
    Material::~Material()
    {
    }

    bool Material::InitializeAsync()
    {
        return true;
    }
    void Material::ShutdownAsync()
    {
    }
    bool Material::InitializeGraphics()
    {
        return true;
    }
    void Material::ShutdownGraphics()
    {
    }

    bool Material::isReady()
    {
        return true;
    }

    std::string Material::name()
    {
        return _name;
    }

    RenderStage* Material::GetRenderStage()
    {
        if (is2d) return renderStage_2d;
        else if (IsOpaque()) return renderStage_opaque;
        else return renderStage_translucent;
    }
}
