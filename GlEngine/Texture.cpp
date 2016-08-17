#include "stdafx.h"
#include "Texture.h"
#include "LodePNG\lodepng.h"
#include <unordered_map>

#include "Engine.h"
#include "ServiceProvider.h"
#include "ILogger.h"
#include "ResourceLoader.h"

#include "OpenGl.h"

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
    Texture *Texture::FromFile(const char *const path, bool hasAlphaChannel)
    {
        if (path == nullptr || path[0] == '\0') return nullptr;

        auto hashed = ([](const char *str, bool alpha) {
            int h = alpha ? 0xDEADBEEF : 0;
            while (*str)
                h = h << 1 ^ *str++;
            return h;
        })(path, hasAlphaChannel);

        static std::unordered_map<int, Texture*> textures;
        auto cached = textures[hashed];
        if (cached != nullptr) return cached;
        return textures[hashed] = new Texture(path, hasAlphaChannel);
    }

    Texture::Texture(const char * const path, bool hasAlphaChannel)
        : path(path), image(nullptr), gl_tex(0), gl_sampler(0), initialized(false), alpha(hasAlphaChannel)
    {
        auto resources = Engine::GetInstance().GetServiceProvider().GetService<ResourceLoader>();
        resources->QueueResource(this);
    }
	Texture::Texture(unsigned width, unsigned height, bool hasAlphaChannel)
		: path(""), width(width), height(height), image(nullptr), gl_tex(0), gl_sampler(0), initialized(false), alpha(hasAlphaChannel)
	{
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
        image = nullptr;
        initialized = false;
    }
    bool Texture::InitializeGraphics()
    {
        glGenTextures(1, &gl_tex);
        glBindTexture(GL_TEXTURE_2D, gl_tex);
        glTexStorage2D(GL_TEXTURE_2D, 4, GL_RGBA8, width, height);
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, image);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        //glGenSamplers(1, &gl_sampler);
        //glBindSampler(0, gl_sampler);

        return true;
    }
    void Texture::ShutdownGraphics()
    {
        glDeleteTextures(1, &gl_tex);
        //glDeleteSamplers(1, &gl_sampler);
    }

    const char *Texture::name()
    {
        return "Texture";
    }

    Texture::operator bool()
    {
        return gl_tex != 0;// && gl_sampler != 0;
    }

    void Texture::Push()
    {
        assert(!!*this);
        glUniform1i(5, 0);
        glActiveTexture(GL_TEXTURE0);
        if (alpha)
        {
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        }
        glBindTexture(GL_TEXTURE_2D, gl_tex);
    }
    void Texture::Pop()
    {
        if (alpha) glDisable(GL_BLEND);
    }

	unsigned Texture::GetWidth()
	{
		return width;
	}

	unsigned Texture::GetHeight()
	{
		return height;
	}

	unsigned Texture::GetGlTexture()
	{
		return gl_tex;
	}
}
