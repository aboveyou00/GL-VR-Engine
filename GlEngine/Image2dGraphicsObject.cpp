#include "stdafx.h"
#include "Image2dGraphicsObject.h"

#include <unordered_map>

#include "Texture.h"
#include "Image2dMaterial.h"
#include "MatrixStack.h"

namespace GlEngine
{
    Image2dGraphicsObject::Image2dGraphicsObject(std::string name, Texture *tex, bool readonly)
        : VboGraphicsObject(name),
          tex(nullptr), mat(new Image2dMaterial()), readonly(readonly),
          align({ ImageComponentAlignment::Middle, ImageComponentAlignment::Middle })
    {
        if (readonly) assert(!!tex);
        mat->SetTexture(this->tex = tex);
    }
    Image2dGraphicsObject::~Image2dGraphicsObject()
    {
    }

    Image2dGraphicsObject *Image2dGraphicsObject::Create(std::string name, Texture *tex)
    {
        static std::unordered_map<Texture*, Image2dGraphicsObject*> cache;
        auto ptr = cache[tex];
        if (ptr == nullptr) ptr = cache[tex] = new Image2dGraphicsObject(name, tex, true);
        return ptr;
    }
    Image2dGraphicsObject *Image2dGraphicsObject::Create(std::string name, std::string path)
    {
        auto tex = Texture::FromFile(path);
        return Create(name, tex);
    }

    bool Image2dGraphicsObject::InitializeAsync()
    {
        AddVertex({ 0, 0, 0 }, { 0, 0 }, { 0, 0, 1 });
        AddVertex({ 1, 0, 0 }, { 1, 0 }, { 0, 0, 1 });
        AddVertex({ 0, 1, 0 }, { 0, 1 }, { 0, 0, 1 });
        AddVertex({ 1, 1, 0 }, { 1, 1 }, { 0, 0, 1 });

        SetMaterial(mat);
        AddTriangle({ 0, 1, 3 });
        AddTriangle({ 0, 3, 2 });

        return true;
    }
    void Image2dGraphicsObject::ShutdownAsync()
    {
    }

    void Image2dGraphicsObject::PreRender(RenderStage* stage)
    {
        if (stage != renderStage_2d) return;
        auto scale_mat = Matrix<4, 4>::Identity();
        if (tex && tex->isReady()) scale_mat = Matrix<4, 4>::ScaleMatrix({ tex->GetWidth(), tex->GetHeight(), 1 });
        scale_mat = Util::GetAlignmentMatrix(align) * scale_mat;
        GlEngine::MatrixStack::Model.mult(scale_mat);
        VboGraphicsObject::PreRender(stage);
    }
    void Image2dGraphicsObject::PostRender(RenderStage* stage)
    {
        if (stage != renderStage_2d) return;
        VboGraphicsObject::PostRender(stage);
        GlEngine::MatrixStack::Model.pop();
    }

    ImageAlignment Image2dGraphicsObject::GetAlignment()
    {
        return align;
    }
    void Image2dGraphicsObject::SetAlignment(ImageAlignment align)
    {
        this->align = align;
    }
    ImageComponentAlignment Image2dGraphicsObject::GetHorizontalAlignment()
    {
        return align.horiz;
    }
    ImageComponentAlignment Image2dGraphicsObject::GetVerticalAlignment()
    {
        return align.vert;
    }
    void Image2dGraphicsObject::SetHorizontalAlignment(ImageComponentAlignment align)
    {
        this->align.horiz = align;
    }
    void Image2dGraphicsObject::SetVerticalAlignment(ImageComponentAlignment align)
    {
        this->align.vert = align;
    }

    void Image2dGraphicsObject::SetTexture(GlEngine::Texture *tex)
    {
        assert(!readonly);
        if (this->tex != tex) mat->SetTexture(this->tex = tex);
    }

    Texture *Image2dGraphicsObject::GetTexture()
    {
        return tex;
    }
    Material *Image2dGraphicsObject::GetMaterial()
    {
        return mat;
    }
    bool Image2dGraphicsObject::IsReadonly()
    {
        return readonly;
    }
}
