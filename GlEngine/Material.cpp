#include "stdafx.h"
#include "Material.h"

namespace GlEngine
{
	Material::Material()
		: is2d(false)
    {
    }
    Material::~Material()
    {
    }

    bool Material::Initialize()
    {
        return true;
    }
    void Material::Shutdown()
    {
    }
    bool Material::InitializeGraphics()
    {
        return true;
    }
    void Material::ShutdownGraphics()
    {
    }
	RenderTargetLayer Material::GetRenderTargetLayer()
	{
		if (Is2d())
			return RenderTargetLayer::Layer2d;
		else
			if (IsOpaque())
				return RenderTargetLayer::Layer3dOpaque;
			else
				return RenderTargetLayer::Layer3dTransluscent;
	}
}
