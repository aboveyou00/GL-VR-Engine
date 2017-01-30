#pragma once

#include "IComponent.h"
#include "TextureFlag.h"

namespace GlEngine
{
    class ENGINE_SHARED Texture : public IGraphicsComponent
    {
    public:
        static Texture *FromFile(const char *const path, TextureFlag flags = TextureFlag::None);
        Texture(unsigned width, unsigned height, TextureFlag flags = TextureFlag::None);

    private:
        Texture(const char *const path, TextureFlag flags = TextureFlag::None);
        ~Texture();

    public:
        bool Initialize();
        void Shutdown();
        bool InitializeGraphics();
        void ShutdownGraphics();

        bool hasFlag(TextureFlag flag) const;
        void SetFlag(TextureFlag flag, bool val);
        void SetFlag(TextureFlag flag);
        void ResetFlag(TextureFlag flag);

        bool IsOpaque() const;

        const char *name() override;

        operator bool();

        const char *GetSource();

        unsigned GetWidth();
        unsigned GetHeight();

        void Push(unsigned idx);
        void Pop();

        unsigned glslTextureId();
        unsigned glslTextureLocation();

    private:
        bool initialized;
        const char *const path;
        unsigned char *image;
        unsigned width, height, gl_tex, gl_sampler, gl_index;
        TextureFlag _flags;
    };
}
