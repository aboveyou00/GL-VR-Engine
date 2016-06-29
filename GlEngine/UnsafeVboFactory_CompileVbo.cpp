#include "stdafx.h"
#include "UnsafeVboFactory.h"

#include "OpenGl.h"

namespace GlEngine
{
    namespace Impl
    {
        VbObject CompileVbo(BufferMode mode, unsigned bufferSizeInBytes, unsigned vertexSizeInBytes, char *front, attribute_descriptor *attrs, unsigned attributeCount, VboType type)
        {
            GLuint currentVbo;
            glGenBuffers(1, &currentVbo);
            glBindBuffer(static_cast<GLuint>(mode), currentVbo);
            glBufferData(static_cast<GLuint>(mode), bufferSizeInBytes, &front, GL_STATIC_DRAW);

            for (unsigned i = 0; i < attributeCount; i++)
            {
                auto attr = attrs[i];
                switch (type)
                {
                case VboType::Float:
                    glVertexAttribPointer(attr.name, attr.size, static_cast<GLenum>(type), GL_FALSE, vertexSizeInBytes, front + attr.start);
                    break;
                case VboType::Double:
                    glVertexAttribLPointer(attr.name, attr.size, static_cast<GLenum>(type), vertexSizeInBytes, front + attr.start);
                    break;
                case VboType::Int:
                case VboType::UnsignedInt:
                case VboType::Short:
                case VboType::UnsignedShort:
                case VboType::Byte:
                case VboType::UnsignedByte:
                    glVertexAttribIPointer(attr.name, attr.size, static_cast<GLenum>(type), vertexSizeInBytes, front + attr.start);
                    break;
                }
            }

            return VbObject(static_cast<unsigned>(currentVbo), mode);
        }
    }
}
