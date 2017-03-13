#include "stdafx.h"
#include "Texture.h"
#include "LodePNG\lodepng.h"
#include <unordered_map>
#include <sstream>
#include "StringUtils.h"

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
    Texture *Texture::FromFile(std::string path, TextureFlag flags)
    {
        if (Util::is_empty_or_ws(path)) return nullptr;

        auto hashed = ([](std::string str, TextureFlag flags) {
            int h = static_cast<int>(flags);
            for (auto chr : str)
                h = h << 1 ^ chr;
            return h;
        })(path, flags);

        static std::unordered_map<int, Texture*> textures;
        auto cachedIt = textures.find(hashed);
        if (cachedIt != textures.end()) return (*cachedIt).second;
        auto tex = new Texture(path, flags);
        textures.insert(std::pair<unsigned, Texture*>(hashed, tex));
        return tex;
    }

    Texture::Texture(std::string path, TextureFlag flags)
        : path(path), image(nullptr), gl_tex(0), gl_sampler(0), initialized(false), _flags(flags)
    {
        auto resources = Engine::GetInstance().GetServiceProvider().GetService<ResourceLoader>();
        resources->QueueInitialize(this);
    }
    Texture::Texture(unsigned width, unsigned height, TextureFlag flags)
        : path(""s), width(width), height(height), image(nullptr), gl_tex(0), gl_sampler(0), initialized(true), _flags(flags)
    {
    }
    Texture::~Texture()
    {
    }

    bool Texture::InitializeAsync()
    {
        if (initialized) return true;
        if (Util::is_empty_or_ws(path)) return false;
        return initialized = decodeOneStep(path.c_str(), image, width, height);
    }
    void Texture::ShutdownAsync()
    {
        if (initialized && !!image) freePng(image);
        image = nullptr;
        initialized = false;
    }
    bool Texture::InitializeGraphics()
    {
        checkForGlError();

        glGenTextures(1, &gl_tex);
        checkForGlError();
        glBindTexture(GL_TEXTURE_2D, gl_tex);
        checkForGlError();
        glTexStorage2D(GL_TEXTURE_2D, 4, GL_RGBA8, width, height);
        checkForGlError();
        if (image != nullptr)
        {
            glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, image);
            checkForGlError();
        }

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        checkForGlError();
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        checkForGlError();
        auto wrapMode = hasFlag(TextureFlag::Clamp) ? GL_CLAMP : GL_REPEAT;
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
        checkForGlError();
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
        checkForGlError();

        //glGenSamplers(1, &gl_sampler);
        //glBindSampler(0, gl_sampler);

        return true;
    }
    void Texture::ShutdownGraphics()
    {
        glDeleteTextures(1, &gl_tex);
        checkForGlError();
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

    std::string Texture::name()
    {
        std::stringstream stream;
        stream << "Texture (" << path << ")";
        return stream.str();
    }

    bool Texture::isReady()
    {
        return gl_tex != 0;// && gl_sampler != 0;
    }

    std::string Texture::GetSource()
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
        checkForGlError();
        glBindTexture(GL_TEXTURE_2D, gl_tex);
        checkForGlError();
    }
    void Texture::Pop()
    {
        glActiveTexture(GL_TEXTURE0 + gl_index);
        checkForGlError();
        glBindTexture(GL_TEXTURE_2D, 0);
        checkForGlError();
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
