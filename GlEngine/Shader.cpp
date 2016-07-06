#include "stdafx.h"
#include "Shader.h"
#include "OpenGl.h"
#include <fstream>

#include "PathUtils.h"

#include "Engine.h"
#include "ServiceProvider.h"
#include "ILogger.h"

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
        : _path(path), _name(name), _vert(0), _frag(0), _prog(0)
    {
    }
    Shader::~Shader()
    {
        Shutdown();
    }

    bool Shader::Initialize()
    {
        if (_name == nullptr) return false;

        if (!_vert)
        {
            _vert = compileShader(GL_VERTEX_SHADER, "vert");
            if (!ensureShaderCompiled(_vert, "vert")) return false;
        }

        if (!_frag)
        {
            _frag = compileShader(GL_FRAGMENT_SHADER, "frag");
            if (!ensureShaderCompiled(_frag, "frag")) return false;
        }

        if (!_prog)
        {
            _prog = compileProgram();
            if (!ensureProgramCompiled()) return false;
        }

        return true;
    }
    void Shader::Shutdown()
    {
        if (_prog) glDeleteProgram(_prog);
        _prog = 0;

        if (_vert) glDeleteShader(_vert);
        _vert = 0;

        if (_frag) glDeleteShader(_frag);
        _frag = 0;
    }

    void Shader::MakeCurrent()
    {
        assert(!!*this);
        glUseProgram(_prog);
    }

    Shader::operator bool()
    {
        return _prog && _vert && _frag;
    }
    //void Shader::operator=(Shader &other)
    //{
    //    assert(!*this);
    //    _path = other._path;
    //    _name = other._name;
    //    _vert = other._vert;
    //    _frag = other._frag;
    //    _prog = other._prog;
    //}

    unsigned Shader::compileShader(unsigned type, const char *suffix)
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
            return 0;
        }

        //file.seekg(0, std::ios::end);
        auto len = (int)file.tellg();
        file.seekg(0);

        static const int STATIC_BUFFER_SIZE = 512;
        static thread_local char tlSource[STATIC_BUFFER_SIZE];
        char *buff = tlSource;
        if (len + 1 > STATIC_BUFFER_SIZE) buff = new char[len + 1];
        file.read(buff, len);
        buff[len] = '\0';

        auto shader = glCreateShader(type);
        glShaderSource(shader, 1, (const GLchar**)&buff, &len);
        glCompileShader(shader);

        if (len + 1 > STATIC_BUFFER_SIZE) delete[] buff;

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
            logger->Log(LogType::Info, "Shader info log for [%s.%s.shader]:\n%s", _name, suffix, buff);
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
            logger->Log(LogType::Info, "Shader program info log for [%s]:\n%s", _name, buff);
            if (logLength + 1 > STATIC_BUFFER_SIZE) delete[] buff;
        }

        return (result == GL_TRUE);
    }
}
