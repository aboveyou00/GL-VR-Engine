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
#include "Property.h"

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
            resources->QueueInitialize(this);
        }
        Shader::~Shader()
        {
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

        bool Shader::InitializeAsync()
        {
            return true;
        }
        void Shader::ShutdownAsync()
        {
        }
        bool Shader::InitializeGraphics()
        {
            auto vertexSource = source->vertex();
            if (!_vert && !Util::is_empty_or_ws(vertexSource))
            {
                _vert = compileShader(GL_VERTEX_SHADER, vertexSource->c_str(), vertexSource->size());
                if (!ensureShaderCompiled("Vertex", _vert)) return false;
            }

            auto tessControlSource = source->tessControl();
            if (!_tessc && !Util::is_empty_or_ws(tessControlSource))
            {
                _tessc = compileShader(GL_TESS_CONTROL_SHADER, tessControlSource->c_str(), tessControlSource->size());
                if (!ensureShaderCompiled("TessControl", _tessc)) _tessc = 0;
            }

            auto tessEvaluationSource = source->tessEvaluation();
            if (!_tesse && !Util::is_empty_or_ws(tessEvaluationSource))
            {
                _tesse = compileShader(GL_TESS_EVALUATION_SHADER, tessEvaluationSource->c_str(), tessEvaluationSource->size());
                if (!ensureShaderCompiled("TessEvaluation", _tesse)) _tesse = 0;
            }

            auto geometrySource = source->geometry();
            if (!_geom && !Util::is_empty_or_ws(geometrySource))
            {
                _geom = compileShader(GL_GEOMETRY_SHADER, geometrySource->c_str(), geometrySource->size());
                if (!ensureShaderCompiled("Geometry", _geom)) _geom = 0;
            }

            auto fragmentSource = source->fragment();
            if (!_frag && !Util::is_empty_or_ws(fragmentSource))
            {
                _frag = compileShader(GL_FRAGMENT_SHADER, fragmentSource->c_str(), fragmentSource->size());
                if (!ensureShaderCompiled("Fragment", _frag)) return false;
            }

            if (!_vert || !_frag) return false;

            if (!_prog)
            {
                _prog = compileProgram();
                if (!ensureProgramCompiled()) return false;
            }

            reflectShader();

            return true;
        }
        void Shader::ShutdownGraphics()
        {
            if (_prog)
            {
                glDeleteProgram(_prog);
                checkForGlError();
            }
            _prog = 0;

            if (_vert)
            {
                glDeleteShader(_vert);
                checkForGlError();
            }
            _vert = 0;

            if (_frag)
            {
                glDeleteShader(_frag);
                checkForGlError();
            }
            _frag = 0;

            if (_tessc)
            {
                glDeleteShader(_tessc);
                checkForGlError();
            }
            _tessc = 0;

            if (_tesse)
            {
                glDeleteShader(_tesse);
                checkForGlError();
            }
            _tesse = 0;

            if (_geom)
            {
                glDeleteShader(_geom);
                checkForGlError();
            }
            _geom = 0;
        }

        bool Shader::isReady()
        {
            return !!_prog && !!_vert && !!_frag;
        }

        std::string Shader::name()
        {
            return "Shader";
        }

        void Shader::Push()
        {
            assert(this->isReady());
            glUseProgram(_prog);
            checkForGlError();
        }
        void Shader::Pop()
        {
            glUseProgram(0);
            checkForGlError();
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

        unsigned Shader::glslProgramIndex()
        {
            return _prog;
        }

        unsigned Shader::compileShader(unsigned type, const char *text, int text_length)
        {
            auto shader = glCreateShader(type);
            checkForGlError();
            glShaderSource(shader, 1, (const GLchar**)&text, &text_length);
            checkForGlError();
            glCompileShader(shader);
            checkForGlError();

            return shader;
        }
        bool Shader::ensureShaderCompiled(std::string name, unsigned shader)
        {
            if (shader == 0) return false;

            GLint result;
            glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
            checkForGlError();

            auto logger = Engine::GetInstance().GetServiceProvider().GetService<ILogger>();
            if (result != GL_TRUE) logger->Log(LogType::WarningC, "%s shader failed to compile", name.c_str());

            GLint logLength;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
            checkForGlError();
            if (logLength != 0)
            {
                static const int STATIC_BUFFER_SIZE = 256;
                static thread_local char infoLog[STATIC_BUFFER_SIZE];
                char *buff = infoLog;
                if (logLength + 1 > STATIC_BUFFER_SIZE) buff = new char[logLength + 1];
                GLsizei length;
                glGetShaderInfoLog(shader, max(STATIC_BUFFER_SIZE, logLength + 1), &length, buff);
                checkForGlError();
                if (!Util::is_empty_or_ws(buff)) logger->Log(LogType::Info, "%s shader info log:\n%s", name.c_str(), buff);
                if (logLength + 1 > STATIC_BUFFER_SIZE) delete[] buff;
            }

            return result == GL_TRUE;
        }

        unsigned Shader::compileProgram()
        {
            auto program = glCreateProgram();
            checkForGlError();
            glAttachShader(program, _vert);
            checkForGlError();
            glAttachShader(program, _frag);
            checkForGlError();
            if (_tessc != 0)
            {
                glAttachShader(program, _tessc);
                checkForGlError();
            }
            if (_tesse != 0)
            {
                glAttachShader(program, _tesse);
                checkForGlError();
            }
            if (_geom != 0)
            {
                glAttachShader(program, _geom);
                checkForGlError();
            }
            glLinkProgram(program);
            checkForGlError();
            return program;
        }
        bool Shader::ensureProgramCompiled()
        {
            GLint result;
            glGetProgramiv(_prog, GL_LINK_STATUS, &result);
            checkForGlError();

            auto logger = Engine::GetInstance().GetServiceProvider().GetService<ILogger>();
            if (result != GL_TRUE) logger->Log(LogType::WarningC, "Shader program failed to link");

            GLint logLength;
            glGetProgramiv(_prog, GL_INFO_LOG_LENGTH, &logLength);
            checkForGlError();
            if (logLength != 0)
            {
                static const int STATIC_BUFFER_SIZE = 256;
                static char infoLog[STATIC_BUFFER_SIZE];
                char *buff = infoLog;
                if (logLength + 1 > STATIC_BUFFER_SIZE) buff = new char[logLength + 1];
                GLsizei length;
                glGetProgramInfoLog(_prog, max(STATIC_BUFFER_SIZE, logLength + 1), &length, buff);
                checkForGlError();
                if (!Util::is_empty_or_ws(buff)) logger->Log(LogType::Info, "Shader program info log:\n%s", buff);
                if (logLength + 1 > STATIC_BUFFER_SIZE) delete[] buff;
            }

            return (result == GL_TRUE);
        }

        void Shader::reflectShader()
        {
            Util::Log("Shader program index: %d", _prog);
            Util::Log("Compiled using ShaderFactory.");

            reflectActiveAttributes();
            reflectActiveUniforms();
        }
#pragma warning(push)
#pragma warning(disable: 4201)
        void Shader::reflectActiveAttributes()
        {
            int numAttributes;
            glGetProgramInterfaceiv(_prog, GL_PROGRAM_INPUT, GL_ACTIVE_RESOURCES, &numAttributes);
            checkForGlError();
            const unsigned properties[] = { GL_LOCATION, GL_NAME_LENGTH, GL_TYPE };

            for (int attributeIdx = 0; attributeIdx < numAttributes; attributeIdx++)
            {
                union {
                    int asArray[3];
                    struct {
                        int location, name_length, type;
                    };
                } values;
                glGetProgramResourceiv(_prog, GL_PROGRAM_INPUT, attributeIdx, 3, properties, 3, NULL, values.asArray);
                checkForGlError();

                char *nameBuff = new char[values.name_length + 1];
                glGetProgramResourceName(_prog, GL_PROGRAM_INPUT, attributeIdx, values.name_length + 1, NULL, nameBuff);
                checkForGlError();
                Util::Log(LogType::Info, "layout(location = %i) in %s %s;", values.location, typeString(values.type).c_str(), nameBuff);
            }
        }
        void Shader::reflectActiveUniforms(bool showUniformBlocks)
        {
            int numUniforms = 0;
            glGetProgramInterfaceiv(_prog, GL_UNIFORM, GL_ACTIVE_RESOURCES, &numUniforms);
            checkForGlError();
            const unsigned properties[4] = { GL_LOCATION, GL_NAME_LENGTH, GL_TYPE, GL_BLOCK_INDEX };
            
            for (int uniformIdx = 0; uniformIdx < numUniforms; uniformIdx++)
            {
                union {
                    int asArray[4];
                    struct {
                        int location, name_length, type, block_index;
                    };
                } values;
                glGetProgramResourceiv(_prog, GL_UNIFORM, uniformIdx, 4, properties, 4, NULL, values.asArray);
                checkForGlError();

                if (values.block_index != -1)
                {
                    //This uniform is in a block
                    if (!showUniformBlocks) continue;
                    Util::Log("Not implemented! Cannot output block uniform information.");
                }
                else
                {
                    char *nameBuff = new char[values.name_length + 1];
                    glGetProgramResourceName(_prog, GL_UNIFORM, uniformIdx, values.name_length + 1, NULL, nameBuff);
                    checkForGlError();
                    Util::Log(LogType::Info, "layout(location = %i) uniform %s %s;", values.location, typeString(values.type).c_str(), nameBuff);
                }
            }
        }
#pragma warning(pop)
        std::string Shader::typeString(int type) {
            switch (type)
            {
            case GL_BOOL: return PropertyType_attribs<bool>::glsl_name();
            case GL_INT: return PropertyType_attribs<int>::glsl_name();
            case GL_UNSIGNED_INT: return PropertyType_attribs<unsigned>::glsl_name();
            case GL_FLOAT: return PropertyType_attribs<float>::glsl_name();
            case GL_DOUBLE: return PropertyType_attribs<double>::glsl_name();

            case GL_BOOL_VEC2: return PropertyType_attribs<Vector<2, bool>>::glsl_name();
            case GL_BOOL_VEC3: return PropertyType_attribs<Vector<3, bool>>::glsl_name();
            case GL_BOOL_VEC4: return PropertyType_attribs<Vector<4, bool>>::glsl_name();

            case GL_INT_VEC2: return PropertyType_attribs<Vector<2, int>>::glsl_name();
            case GL_INT_VEC3: return PropertyType_attribs<Vector<3, int>>::glsl_name();
            case GL_INT_VEC4: return PropertyType_attribs<Vector<4, int>>::glsl_name();

            case GL_UNSIGNED_INT_VEC2: return PropertyType_attribs<Vector<2, unsigned>>::glsl_name();
            case GL_UNSIGNED_INT_VEC3: return PropertyType_attribs<Vector<3, unsigned>>::glsl_name();
            case GL_UNSIGNED_INT_VEC4: return PropertyType_attribs<Vector<4, unsigned>>::glsl_name();

            case GL_FLOAT_VEC2: return PropertyType_attribs<Vector<2>>::glsl_name();
            case GL_FLOAT_VEC3: return PropertyType_attribs<Vector<3>>::glsl_name();
            case GL_FLOAT_VEC4: return PropertyType_attribs<Vector<4>>::glsl_name();

            case GL_DOUBLE_VEC2: return PropertyType_attribs<Vector<2, double>>::glsl_name();
            case GL_DOUBLE_VEC3: return PropertyType_attribs<Vector<3, double>>::glsl_name();
            case GL_DOUBLE_VEC4: return PropertyType_attribs<Vector<4, double>>::glsl_name();

            case GL_FLOAT_MAT2: return PropertyType_attribs<Matrix<2, 2>>::glsl_name();
            case GL_FLOAT_MAT2x3: return PropertyType_attribs<Matrix<2, 3>>::glsl_name();
            case GL_FLOAT_MAT2x4: return PropertyType_attribs<Matrix<2, 4>>::glsl_name();

            case GL_FLOAT_MAT3x2: return PropertyType_attribs<Matrix<3, 2>>::glsl_name();
            case GL_FLOAT_MAT3: return PropertyType_attribs<Matrix<3, 3>>::glsl_name();
            case GL_FLOAT_MAT3x4: return PropertyType_attribs<Matrix<3, 4>>::glsl_name();

            case GL_FLOAT_MAT4x2: return PropertyType_attribs<Matrix<4, 2>>::glsl_name();
            case GL_FLOAT_MAT4x3: return PropertyType_attribs<Matrix<4, 3>>::glsl_name();
            case GL_FLOAT_MAT4: return PropertyType_attribs<Matrix<4, 4>>::glsl_name();

            default:
                return "Unknown type"s;
            }
        }
    }
}
