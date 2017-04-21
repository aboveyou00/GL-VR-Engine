#pragma once

#include "IAsyncInitializable.h"
#include "TextureFlag.h"

namespace GlEngine
{
    class ENGINE_SHARED Texture : public IAsyncInitializable
    {
    public:
        static Texture *FromFile(std::string path, TextureFlag flags = TextureFlag::None);
        Texture(unsigned width, unsigned height, TextureFlag flags = TextureFlag::None);
        ~Texture();

    private:
        Texture(std::string path, TextureFlag flags = TextureFlag::None);

    public:
        virtual bool InitializeAsync() override;
        virtual void ShutdownAsync() override;
        virtual bool InitializeGraphics() override;
        virtual void ShutdownGraphics() override;

        bool hasFlag(TextureFlag flag) const;
        void SetFlag(TextureFlag flag, bool val);
        void SetFlag(TextureFlag flag);
        void ResetFlag(TextureFlag flag);

        bool IsOpaque() const;

        virtual std::string name() override;

        virtual bool isReady() override;

        std::string GetSource();

        unsigned GetWidth();
        unsigned GetHeight();

        void Push(unsigned idx);
        void Pop();

        unsigned glslTextureId();
        int glslTextureLocation();

    protected:
        unsigned gl_tex, gl_sampler;

    private:
        bool initialized;
        std::string path;
        unsigned char *image;
        unsigned width, height;
        int gl_index;
        TextureFlag _flags;
    };
}
