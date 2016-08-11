#pragma once

#include "IComponent.h"

namespace GlEngine
{
    class ENGINE_SHARED Texture : public IGraphicsComponent
    {
    public:
        static Texture *FromFile(const char *const path, bool hasAlphaChannel = false);

    private:
        Texture(const char *const path, bool hasAlphaChannel);
        ~Texture();

    public:
        bool Initialize();
        void Shutdown();
        bool InitializeGraphics();
        void ShutdownGraphics();

        const char *name() override;

        operator bool();

        void Push();
        void Pop();

		unsigned GetWidth();
		unsigned GetHeight();

		unsigned GetGlTexture();

    private:
        bool initialized, alpha;
        const char *const path;
        unsigned char *image;
        unsigned width, height, gl_tex, gl_sampler;
    };
}
