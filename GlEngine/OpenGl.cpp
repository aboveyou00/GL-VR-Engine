#include "stdafx.h"
#include "LogUtils.h"
#include <sstream>

#include "../OpenGlGraphicsAdapter/OpenGl.h"

static void reflectShader();
static void reflectActiveAttributes(unsigned currentProgram);
static void reflectActiveUniforms(unsigned currentProgram, bool showUniformBlocks = false);
static std::string typeString(int type);

void checkForGlError()
{
    while (true)
    {
        auto err = glGetError();
        if (!err) return;
        std::stringstream stream;
        switch (err)
        {
        case GL_INVALID_ENUM:                  stream << "INVALID_ENUM"; break;
        case GL_INVALID_VALUE:                 stream << "INVALID_VALUE"; break;
        case GL_INVALID_OPERATION:             stream << "INVALID_OPERATION"; break;
        case GL_STACK_OVERFLOW:                stream << "STACK_OVERFLOW"; break;
        case GL_STACK_UNDERFLOW:               stream << "STACK_UNDERFLOW"; break;
        case GL_OUT_OF_MEMORY:                 stream << "OUT_OF_MEMORY"; break;
        case GL_INVALID_FRAMEBUFFER_OPERATION: stream << "INVALID_FRAMEBUFFER_OPERATION"; break;
        }
        stream << ": " << glewGetErrorString(err);
        GlEngine::Util::Log(GlEngine::LogType::ErrorC, "An OpenGL error was produced: %s", stream.str().c_str());
        reflectShader();
        assert(false);
    }
}

#include "PropertyType_attribs.h"
using namespace GlEngine;
using namespace GlEngine::ShaderFactory;

static void reflectShader()
{
    int currentProgram;
    glGetIntegerv(GL_CURRENT_PROGRAM, &currentProgram);
    if (!currentProgram)
    {
        Util::Log(LogType::InfoC, "No current shader!");
        return;
    }

    Util::Log(LogType::InfoC, "Shader program index: %d", currentProgram);
    Util::Log(LogType::InfoC, "Compiled using ShaderFactory.");

    reflectActiveAttributes(currentProgram);
    reflectActiveUniforms(currentProgram);
}
#pragma warning(push)
#pragma warning(disable: 4201)
static void reflectActiveAttributes(unsigned prog)
{
    int numAttributes;
    glGetProgramInterfaceiv(prog, GL_PROGRAM_INPUT, GL_ACTIVE_RESOURCES, &numAttributes);
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
        glGetProgramResourceiv(prog, GL_PROGRAM_INPUT, attributeIdx, 3, properties, 3, NULL, values.asArray);
        checkForGlError();

        char *nameBuff = new char[values.name_length + 1];
        glGetProgramResourceName(prog, GL_PROGRAM_INPUT, attributeIdx, values.name_length + 1, NULL, nameBuff);
        checkForGlError();
        Util::Log(LogType::InfoC, "layout(location = %i) in %s %s;", values.location, typeString(values.type).c_str(), nameBuff);
    }
}
static void reflectActiveUniforms(unsigned prog, bool showUniformBlocks)
{
    int numUniforms = 0;
    glGetProgramInterfaceiv(prog, GL_UNIFORM, GL_ACTIVE_RESOURCES, &numUniforms);
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
        glGetProgramResourceiv(prog, GL_UNIFORM, uniformIdx, 4, properties, 4, NULL, values.asArray);
        checkForGlError();

        if (values.block_index != -1)
        {
            //This uniform is in a block
            if (!showUniformBlocks) continue;
            Util::Log(LogType::InfoC, "Not implemented! Cannot output block uniform information.");
        }
        else
        {
            char *nameBuff = new char[values.name_length + 1];
            glGetProgramResourceName(prog, GL_UNIFORM, uniformIdx, values.name_length + 1, NULL, nameBuff);
            checkForGlError();
            Util::Log(LogType::InfoC, "layout(location = %i) uniform %s %s;", values.location, typeString(values.type).c_str(), nameBuff);
        }
    }
}
#pragma warning(pop)
static std::string typeString(int type) {
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

    case GL_SAMPLER_2D: return PropertyType_attribs<Texture*>::glsl_name();

    default:
        return "Unknown type"s;
    }
}
