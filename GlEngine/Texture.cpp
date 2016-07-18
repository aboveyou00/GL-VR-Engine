#include "stdafx.h"
#include "Texture.h"
#include "LodePNG\lodepng.h"
#include <unordered_map>

#include "Engine.h"
#include "ServiceProvider.h"
#include "ILogger.h"
#include "ResourceLoader.h"

static bool decodeOneStep(const char *filename, unsigned char *&image, unsigned &width, unsigned &height)
{
    unsigned error;
    error = lodepng_decode32_file(&image, &width, &height, filename);
    if (error)
    {
        auto logger = GlEngine::Engine::GetInstance().GetServiceProvider().GetService<GlEngine::ILogger>();
        logger->Log(GlEngine::LogType::ErrorC, "Error loading PNG texture: %u: %s\n", error, lodepng_error_text(error));
        return false;
    }

    return true;
}
static void freePng(unsigned char *&image)
{
    free(image);
}

namespace GlEngine
{
    Texture *Texture::FromFile(const char *const path)
    {
        static std::unordered_map<int, Texture*> textures;
        auto hashed = ([](const char *str) {
            int h = 0;
            while (*str)
                h = h << 1 ^ *str++;
            return h;
        })(path);
        auto cached = textures[hashed];
        if (cached != nullptr) return cached;
        return textures[hashed] = new Texture(path);
    }

    Texture::Texture(const char * const path)
        : path(path)
    {
        auto resources = Engine::GetInstance().GetServiceProvider().GetService<ResourceLoader>();
        resources->QueueResource(this);
    }
    Texture::~Texture()
    {
    }

    bool Texture::Initialize()
    {
        if (initialized) return true;
        return initialized = decodeOneStep(path, image, width, height);
    }
    void Texture::Shutdown()
    {
        if (initialized) freePng(image);
        initialized = false;
    }
    bool Texture::InitializeGraphics()
    {
        return false;
    }
    void Texture::ShutdownGraphics()
    {
    }
}
