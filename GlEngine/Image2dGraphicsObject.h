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
        Image2dGraphicsObject(std::string name, Texture *tex = nullptr, bool readonly = false);
        ~Image2dGraphicsObject();

        static Image2dGraphicsObject *Create(std::string name, Texture *tex);
        static Image2dGraphicsObject *Create(std::string name, const char *path);
        
        virtual bool InitializeAsync() override;
        virtual void ShutdownAsync() override;

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