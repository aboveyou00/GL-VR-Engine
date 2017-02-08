#pragma once

#include "VboGraphicsObject.h"
#include "ImageAlignment.h"

namespace GlEngine
{
    class Texture;
    class Image2dMaterial;

    class ENGINE_SHARED Image2dGraphicsObject : public VboGraphicsObject
    {
    public:
        Image2dGraphicsObject(Texture *tex = nullptr, bool readonly = false);
        ~Image2dGraphicsObject();

        static Image2dGraphicsObject *Create(Texture *tex);
        static Image2dGraphicsObject *Create(const char *path);
        
        virtual bool Initialize() override;
        virtual void Shutdown() override;

        virtual std::string name() override;

        void PreRender(RenderTargetLayer layer) override;
        void PostRender(RenderTargetLayer layer) override;

        ImageAlignment GetAlignment();
        void SetAlignment(ImageAlignment align);
        ImageComponentAlignment GetHorizontalAlignment();
        ImageComponentAlignment GetVerticalAlignment();
        void SetHorizontalAlignment(ImageComponentAlignment align);
        void SetVerticalAlignment(ImageComponentAlignment align);

        void SetTexture(GlEngine::Texture *tex);

        Texture *GetTexture();
        Material *GetMaterial();
        bool IsReadonly();

    private:
        bool readonly;
        Texture *tex;
        Image2dMaterial *mat;
        ImageAlignment align;
    };
}