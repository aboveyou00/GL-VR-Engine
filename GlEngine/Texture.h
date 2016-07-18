#pragma once

#include "IComponent.h"

namespace GlEngine
{
    class ENGINE_SHARED Texture : public IGraphicsComponent
    {
    public:
        static Texture *FromFile(const char *const path);

    private:
        Texture(const char *const path);
        ~Texture();

    public:
        bool Initialize();
        void Shutdown();
        bool InitializeGraphics();
        void ShutdownGraphics();

    private:
        bool initialized;
        const char *const path;
        unsigned char *image;
        unsigned width, height;
    };
}
