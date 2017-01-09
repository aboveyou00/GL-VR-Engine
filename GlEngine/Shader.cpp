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
    namespace ShaderFactory
    {
        Shader::Shader(ShaderSource *source)
            : source(source),
            _vert(0), _frag(0), _tessc(0), _tesse(0), _geom(0), _prog(0)
        {
            assert(!Util::is_empty_or_ws(source->vertex()));
            assert(!Util::is_empty_or_ws(source->fragment()));

            auto resources = Engine::GetInstance().GetServiceProvider().GetService<ResourceLoader>();
            resources->QueueResource(this);
        }
        Shader::~Shader()
        {
            Shutdown();
        }

        Shader *Shader::Create(ShaderSource *source)
        {
            assert(source != nullptr);

            auto hashed = std::hash<ShaderSource*>()(source);
            
            static std::unordered_map<size_t, Shader*> shaders;
            auto cached = shaders[hashed];
            if (cached != nullptr) return cached;
            return shaders[hashed] = new Shader(source);
        }

        bool Shader::Initialize()
        {
            return true;
        }
        void Shader::Shutdown()
        {
        }
        bool Shader::InitializeGraphics()
        {
            auto vertexSource = source->vertex();
            if (!_vert && !Util::is_empty_or_ws(vertexSource))
            {
                _vert = compileShader(GL_VERTEX_SHADER, vertexSource->c_str(), vertexSource->size());
                if (!ensureShaderCompiled(_vert)) return false;
            }

            auto fragmentSource = source->fragment();
            if (!_frag && !Util::is_empty_or_ws(fragmentSource))
            {
                _frag = compileShader(GL_FRAGMENT_SHADER, fragmentSource->c_str(), fragmentSource->size());
                if (!ensureShaderCompiled(_frag)) return false;
            }

            auto tessControlSource = source->tessControl();
            if (!_tessc && !Util::is_empty_or_ws(tessControlSource))
            {
                _tessc = compileShader(GL_TESS_CONTROL_SHADER, tessControlSource->c_str(), tessControlSource->size());
                if (!ensureShaderCompiled(_tessc)) _tessc = 0;
            }

            auto tessEvaluationSource = source->tessEvaluation();
            if (!_tesse && !Util::is_empty_or_ws(tessEvaluationSource))
            {
                _tesse = compileShader(GL_TESS_EVALUATION_SHADER, tessEvaluationSource->c_str(), tessEvaluationSource->size());
                if (!ensureShaderCompiled(_tesse)) _tesse = 0;
            }

            auto geometrySource = source->geometry();
            if (!_geom && !Util::is_empty_or_ws(geometrySource))
            {
                _geom = compileShader(GL_GEOMETRY_SHADER, vertexSource->c_str(), geometrySource->size());
                if (!ensureShaderCompiled(_geom)) _tesse = 0;
            }

            if (!_vert || !_frag) return false;

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

            if (_tessc) glDeleteShader(_tessc);
            _tessc = 0;

            if (_tesse) glDeleteShader(_tesse);
            _tesse = 0;

            if (_geom) glDeleteShader(_geom);
            _geom = 0;
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

            //MatrixStack::Projection.tell_gl();
            //MatrixStack::ModelView.tell_gl();

            //Vector<3> lightDir = { 1, 1.5, 1 };
            //lightDir = lightDir.Normalized();
            //glUniform3f(2, lightDir[0], lightDir[1], lightDir[2]);
            //glUniform3f(3, .4f, .6f, 1.f);
            //glUniform3f(4, .4f, .4f, .4f);

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
            return !!_tessc && !!_tesse;
        }
        bool Shader::UsesGeometry()
        {
            return !!_geom;
        }

        Shader::operator bool()
        {
            return !!_prog && !!_vert && !!_frag;
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
}
