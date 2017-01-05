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
        //: Shader(std::vector<ShaderFactory::Attribute>())
    {
    }
    //Shader::Shader(std::vector<ShaderFactory::Attribute>, std::string vert_src, std::string frag_src, std::string tessc_src, std::string tesse_src, std::string geom_src)
    //    : _prog(0)
    //{
    //    program = ShaderFactory::Program(false, false);


    //    auto resources = Engine::GetInstance().GetServiceProvider().GetService<ResourceLoader>();
    //    resources->QueueResource(this);
    //}
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

        assert(false);
        return nullptr;
        //return shaders[hashed] = new Shader(shader_path, shader_name);
    }

    bool Shader::Initialize()
    {
        return false;
    }
    void Shader::Shutdown()
    {
    }
    bool Shader::InitializeGraphics()
    {
        //if (!_vert && vert_src != "")
        //{
        //    _vert = compileShader(GL_VERTEX_SHADER, vert_src.c_str(), vert_src.size());
        //    if (!ensureShaderCompiled(_vert)) return false;
        //}

        //if (!_frag && frag_src != "")
        //{
        //    _frag = compileShader(GL_FRAGMENT_SHADER, frag_src.c_str(), frag_src.size());
        //    if (!ensureShaderCompiled(_frag)) return false;
        //}

        //if (!_tessc && tessc_src != "")
        //{
        //    _tessc = compileShader(GL_TESS_CONTROL_SHADER, tessc_src.c_str(), tessc_src.size());
        //    if (!ensureShaderCompiled(_tessc)) _tessc = 0;
        //}

        //if (!_tesse && tesse_src != "")
        //{
        //    _tesse = compileShader(GL_TESS_EVALUATION_SHADER, tesse_src.c_str(), tesse_src.size());
        //    if (!ensureShaderCompiled(_tesse)) _tesse = 0;
        //}

        //if (!_geom && geom_src != "")
        //{
        //    _geom = compileShader(GL_GEOMETRY_SHADER, geom_src.c_str(), geom_src.size());
        //    if (!ensureShaderCompiled(_geom)) _tesse = 0;
        //}

        //if (!_prog)
        //{
        //    _prog = compileProgram();
        //    if (!ensureProgramCompiled()) return false;
        //}

        //return true;

        assert(false);
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

        if (_tessc) glDeleteShader(_tessc);
        _tessc = 0;

        if (_tesse) glDeleteShader(_tesse);
        _tesse = 0;
    }

    const char *Shader::name()
    {
        return "Shader";
    }

    void Shader::Push()
    {
        assert(!!*this);
        glUseProgram(_prog);

        /* Use environment here */
        
        
        MatrixStack::Projection.tell_gl();
        MatrixStack::ModelView.tell_gl();

        Vector<3> lightDir = { 1, 1.5, 1 };
        lightDir = lightDir.Normalized();
        glUniform3f(2, lightDir[0], lightDir[1], lightDir[2]);
        glUniform3f(3, .4f, .6f, 1.f);
        glUniform3f(4, .4f, .4f, .4f);

        //theta += .01f;
        //glUniform1f(6, theta);
    }
    void Shader::Pop()
    {
        glUseProgram(0);
    }
    
    bool Shader::UsesVertex()
    {
        return !!_vert;
    }
    bool Shader::UsesFragment()
    {
        return !!_frag;
    }
    bool Shader::UsesTesselation()
    {
        return !!_tesse;
    }
    bool Shader::UsesGeometry()
    {
        return !!_geom;
    }

    Shader::operator bool()
    {
        return _prog && _vert && _frag;
    }

    unsigned Shader::compileShader(unsigned type, const char *text, int text_length)
    {
        auto shader = glCreateShader(type);
        glShaderSource(shader, 1, (const GLchar**)&text, &text_length);
        glCompileShader(shader);

        return shader;
    }
    bool Shader::ensureShaderCompiled(unsigned shader)
    {
        if (shader == 0) return false;

        GLint result;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &result);

        auto logger = Engine::GetInstance().GetServiceProvider().GetService<ILogger>();
        if (result != GL_TRUE) logger->Log(LogType::WarningC, "Shader failed to compile");

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
            if (!Util::is_empty_or_ws(buff)) logger->Log(LogType::Info, "Shader info log:\n%s", buff);
            if (logLength + 1 > STATIC_BUFFER_SIZE) delete[] buff;
        }

        return result == GL_TRUE;
    }

    unsigned Shader::compileProgram()
    {
        auto program = glCreateProgram();
        glAttachShader(program, _vert);
        glAttachShader(program, _frag);
        if (_tessc != 0) glAttachShader(program, _tessc);
        if (_tesse != 0) glAttachShader(program, _tesse);
        glLinkProgram(program);
        return program;
    }
    bool Shader::ensureProgramCompiled()
    {
        GLint result;
        glGetProgramiv(_prog, GL_LINK_STATUS, &result);

        auto logger = Engine::GetInstance().GetServiceProvider().GetService<ILogger>();
        if (result != GL_TRUE) logger->Log(LogType::WarningC, "Shader program failed to link");

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
            if (!Util::is_empty_or_ws(buff)) logger->Log(LogType::Info, "Shader program info log:\n%s", buff);
            if (logLength + 1 > STATIC_BUFFER_SIZE) delete[] buff;
        }

        return (result == GL_TRUE);
    }
}
