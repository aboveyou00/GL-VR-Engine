#include "stdafx.h"
#include "Shader.h"
#include "OpenGl.h"
#include <fstream>
#include <unordered_map>

#include "PathUtils.h"
#include "MatrixStack.h"

#include "Engine.h"
#include "ServiceProvider.h"
#include "ILogger.h"
#include "ResourceLoader.h"
#include "StringUtils.h"

namespace GlEngine
{
    Shader::Shader()
        : Shader(nullptr, nullptr)
    {
    }
    Shader::Shader(const char *name)
        : Shader("", name)
    {
    }
    Shader::Shader(const char *path, const char *name)
        : _path(path), _name(name), _vert_text(nullptr), _frag_text(nullptr), _vert(0), _frag(0), _prog(0)
    {
        auto resources = Engine::GetInstance().GetServiceProvider().GetService<ResourceLoader>();
        resources->QueueResource(this);
    }
    Shader::~Shader()
    {
        Shutdown();
    }

    Shader *Shader::Create(const char *shader_path, const char *shader_name)
    {
        if (shader_name == nullptr || shader_name[0] == '\0') return nullptr;

        auto hashed = ([](const char *str1, const char *str2) {
            int h = 2;
            while (*str1)
                h = h << 1 ^ *str1++;
            h = h << 2;
            while (*str2)
                h = h << 1 ^ *str2++;
            return h;
        })(shader_path, shader_name);

        static std::unordered_map<int, Shader*> shaders;
        auto cached = shaders[hashed];
        if (cached != nullptr) return cached;
        return shaders[hashed] = new Shader(shader_path, shader_name);
    }

    bool Shader::Initialize()
    {
        if (_name == nullptr) return false;

        if (!loadShaderText(_vert_text, _vert_text_length, "vert")) return false;
        if (!loadShaderText(_frag_text, _frag_text_length, "frag")) return false;

        return true;
    }
    void Shader::Shutdown()
    {
    }
    bool Shader::InitializeGraphics()
    {
        if (!_vert)
        {
            _vert = compileShader(GL_VERTEX_SHADER, _vert_text, _vert_text_length);
            if (!ensureShaderCompiled(_vert, "vert")) return false;
            delete[] _vert_text;
        }

        if (!_frag)
        {
            _frag = compileShader(GL_FRAGMENT_SHADER, _frag_text, _frag_text_length);
            if (!ensureShaderCompiled(_frag, "frag")) return false;
            delete[] _frag_text;
        }

        if (!_prog)
        {
            _prog = compileProgram();
            if (!ensureProgramCompiled()) return false;
        }

        return true;
    }
    void Shader::ShutdownGraphics()
    {
        if (_prog) glDeleteProgram(_prog);
        _prog = 0;

        if (_vert) glDeleteShader(_vert);
        _vert = 0;

        if (_frag) glDeleteShader(_frag);
        _frag = 0;
    }

    const char *Shader::name()
    {
        return "Shader";
    }

    void Shader::MakeCurrent()
    {
        assert(!!*this);
        glUseProgram(_prog);

        MatrixStack::Projection.tell_gl();
        MatrixStack::ModelView.tell_gl();
    }

    Shader::operator bool()
    {
        return _prog && _vert && _frag;
    }

    bool Shader::loadShaderText(const char *&text, int &text_length, const char *suffix)
    {
        static const int NAME_BUFFER_SIZE = 64;
        static thread_local char nameBuff[NAME_BUFFER_SIZE];
        sprintf_s(nameBuff, "%s.%s.shader", _name, suffix);
        auto fullPath = Util::combinePath(_path, nameBuff);

        std::ifstream file(fullPath, std::ios::in | std::ifstream::ate | std::ifstream::binary);
        if (file.fail() || !file)
        {
            auto &logger = *GlEngine::Engine::GetInstance().GetServiceProvider().GetService<GlEngine::ILogger>();
            logger.Log(LogType::Warning, "Could not open shader file [%s]", fullPath);
            return false;
        }

        auto len = (int)file.tellg();
        file.seekg(0);

        char *buff = new char[len + 1];
        file.read(buff, len);
        buff[len] = '\0';
        text = buff;

        text_length = len;
        return true;
    }

    unsigned Shader::compileShader(unsigned type, const char *text, int text_length)
    {
        auto shader = glCreateShader(type);
        glShaderSource(shader, 1, (const GLchar**)&text, &text_length);
        glCompileShader(shader);

        return shader;
    }
    bool Shader::ensureShaderCompiled(unsigned shader, const char *suffix)
    {
        if (shader == 0) return false;

        GLint result;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &result);

        auto logger = Engine::GetInstance().GetServiceProvider().GetService<ILogger>();
        if (result != GL_TRUE) logger->Log(LogType::WarningC, "Shader failed to compile: [%s.%s.shader]", _name, suffix);

        GLint logLength;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
        if (logLength != 0)
        {
            static const int STATIC_BUFFER_SIZE = 256;
            static thread_local char infoLog[STATIC_BUFFER_SIZE];
            char *buff = infoLog;
            if (logLength + 1 > STATIC_BUFFER_SIZE) buff = new char[logLength + 1];
            GLsizei length;
            glGetShaderInfoLog(shader, max(STATIC_BUFFER_SIZE, logLength + 1), &length, buff);
            if (!Util::is_empty_or_ws(buff)) logger->Log(LogType::Info, "Shader info log for [%s.%s.shader]:\n%s", _name, suffix, buff);
            if (logLength + 1 > STATIC_BUFFER_SIZE) delete[] buff;
        }

        return result == GL_TRUE;
    }

    unsigned Shader::compileProgram()
    {
        auto program = glCreateProgram();
        glAttachShader(program, _vert);
        glAttachShader(program, _frag);
        glLinkProgram(program);
        return program;
    }
    bool Shader::ensureProgramCompiled()
    {
        GLint result;
        glGetProgramiv(_prog, GL_LINK_STATUS, &result);

        auto logger = Engine::GetInstance().GetServiceProvider().GetService<ILogger>();
        if (result != GL_TRUE) logger->Log(LogType::WarningC, "Shader program failed to link: [%s]", _name);

        GLint logLength;
        glGetProgramiv(_prog, GL_INFO_LOG_LENGTH, &logLength);
        if (logLength != 0)
        {
            static const int STATIC_BUFFER_SIZE = 256;
            static char infoLog[STATIC_BUFFER_SIZE];
            char *buff = infoLog;
            if (logLength + 1 > STATIC_BUFFER_SIZE) buff = new char[logLength + 1];
            GLsizei length;
            glGetProgramInfoLog(_prog, max(STATIC_BUFFER_SIZE, logLength + 1), &length, buff);
            if (!Util::is_empty_or_ws(buff)) logger->Log(LogType::Info, "Shader program info log for [%s]:\n%s", _name, buff);
            if (logLength + 1 > STATIC_BUFFER_SIZE) delete[] buff;
        }

        return (result == GL_TRUE);
    }
}
