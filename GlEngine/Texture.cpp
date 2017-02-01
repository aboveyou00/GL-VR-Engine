#include "stdafx.h"
#include "Texture.h"
#include "LodePNG\lodepng.h"
#include <unordered_map>
#include <sstream>

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
    Texture *Texture::FromFile(const char *const path, TextureFlag flags)
    {
        if (path == nullptr || path[0] == '\0') return nullptr;

        auto hashed = ([](const char *str, TextureFlag flags) {
            int h = static_cast<int>(flags);
            while (*str)
                h = h << 1 ^ *str++;
            return h;
        })(path, flags);

        static std::unordered_map<int, Texture*> textures;
        auto cachedIt = textures.find(hashed);
        if (cachedIt != textures.end()) return (*cachedIt).second;
        auto tex = new Texture(path, flags);
        textures.insert(std::pair<unsigned, Texture*>(hashed, tex));
        return tex;
    }

    Texture::Texture(const char *const path, TextureFlag flags)
        : path(path), image(nullptr), gl_tex(0), gl_sampler(0), initialized(false), _flags(flags)
    {
        auto resources = Engine::GetInstance().GetServiceProvider().GetService<ResourceLoader>();
        resources->QueueInitialize(this);
    }
    Texture::Texture(unsigned width, unsigned height, TextureFlag flags)
        : path(nullptr), width(width), height(height), image(nullptr), gl_tex(0), gl_sampler(0), initialized(true), _flags(flags)
    {
    }
    Texture::~Texture()
    {
    }

    bool Texture::Initialize()
    {
        if (initialized) return true;
        if (path == nullptr) return false;
        return initialized = decodeOneStep(path, image, width, height);
    }
    void Texture::Shutdown()
    {
        if (initialized && !!image) freePng(image);
        image = nullptr;
        initialized = false;
    }
    bool Texture::InitializeGraphics()
    {
        glGenTextures(1, &gl_tex);
        glBindTexture(GL_TEXTURE_2D, gl_tex);
        glTexStorage2D(GL_TEXTURE_2D, 4, GL_RGBA8, width, height);
        if (image != nullptr) glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, image);

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

    bool Texture::hasFlag(TextureFlag flag) const
    {
        return (_flags & flag) != TextureFlag::None;
    }
    void Texture::SetFlag(TextureFlag flag, bool val)
    {
        if (val) _flags |= flag;
        else _flags &= ~flag;
    }
    void Texture::SetFlag(TextureFlag flag)
    {
        SetFlag(flag, true);
    }
    void Texture::ResetFlag(TextureFlag flag)
    {
        SetFlag(flag, false);
    }

    bool Texture::IsOpaque() const
    {
        return !hasFlag(TextureFlag::Translucent);
    }

    const char *Texture::name()
    {
        std::stringstream stream;
        stream << "Texture (" << path << ")";
        return stream.str().c_str();
    }

    Texture::operator bool()
    {
        return gl_tex != 0;// && gl_sampler != 0;
    }

    const char *Texture::GetSource()
    {
        return path;
    }

    unsigned Texture::GetWidth()
    {
        return width;
    }
    unsigned Texture::GetHeight()
    {
        return height;
    }

    void Texture::Push(unsigned texIdx)
    {
        assert(texIdx < 32);
        gl_index = texIdx;
        glActiveTexture(GL_TEXTURE0 + gl_index);
        glBindTexture(GL_TEXTURE_2D, gl_tex);
    }
    void Texture::Pop()
    {
        glActiveTexture(GL_TEXTURE0 + gl_index);
        glBindTexture(GL_TEXTURE_2D, 0);
        gl_index = 0;
    }

    unsigned Texture::glslTextureId()
    {
        return gl_tex;
    }
    unsigned Texture::glslTextureLocation()
    {
        return gl_index;
    }
}
