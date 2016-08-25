#include "stdafx.h"
#include "DialogBoxGraphicsObject.h"
#include "DialogBoxMaterial.h"
#include "MatrixStack.h"
#include "Texture.h"

namespace TileRPG
{
    DialogBoxGraphicsObject::DialogBoxGraphicsObject()
        : ImageGraphicsObject(mat = new DialogBoxMaterial()),
          tex(nullptr)
    {
    }
    DialogBoxGraphicsObject::~DialogBoxGraphicsObject()
    {
    }
    
    void DialogBoxGraphicsObject::PreRender(GlEngine::RenderTargetLayer layer)
    {
        if (layer != GlEngine::RenderTargetLayer::Layer2d) return;
        auto scale_mat = Matrix<4, 4>::Identity();
        if (tex && *tex) scale_mat = Matrix<4, 4>::ScaleMatrix({ tex->GetWidth(), tex->GetHeight(), 1 });
        scale_mat = Matrix<4, 4>::TranslateMatrix({ -.5f, -.5f, 0 }) * scale_mat * Matrix<4, 4>::TranslateMatrix({ 0, 180, 0 });
        GlEngine::MatrixStack::ModelView.mult(scale_mat);
        ImageGraphicsObject::PreRender(layer);
    }
    void DialogBoxGraphicsObject::RenderImpl(GlEngine::RenderTargetLayer layer)
    {
        ImageGraphicsObject::RenderImpl(layer);
    }
    void DialogBoxGraphicsObject::PostRender(GlEngine::RenderTargetLayer layer)
    {
        if (layer != GlEngine::RenderTargetLayer::Layer2d) return;
        ImageGraphicsObject::PostRender(layer);
        GlEngine::MatrixStack::ModelView.pop();
    }

    void DialogBoxGraphicsObject::SetTexture(GlEngine::Texture *tex)
    {
        if (this->tex != tex)
        {
            mat->SetTexture(this->tex = tex);
        }
    }
}
