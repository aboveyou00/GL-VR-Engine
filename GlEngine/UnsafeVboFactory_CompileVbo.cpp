#include "stdafx.h"
#include "UnsafeVboFactory.h"

#include "OpenGl.h"

namespace GlEngine
{
    namespace Impl
    {
        VbObject CompileVbo(BufferMode mode, unsigned bufferSizeInBytes, unsigned vertexSizeInBytes, void *front, attribute_descriptor *attrs, unsigned attributeCount, VboType type)
        {
            //mode should be BufferMode::Array
            //bufferSizeInBytes should be 72
            //vertexSizeInBytes should be 24
            //front should point to the beginning of the data
            //attrs should be { 0, 3, 0 } and { 1, 3, 12 }
            //attributeCount should be 2
            //type should be VboType::Float

            unsigned currentVbo;
            glGenBuffers(1, &currentVbo);
            glBindBuffer(static_cast<GLenum>(mode), currentVbo);
            glBufferData(static_cast<GLuint>(mode), bufferSizeInBytes, front, GL_STATIC_DRAW);

            unsigned vao = 0;
            if (mode == BufferMode::Array)
            {
                glGenVertexArrays(1, &vao);
                glBindVertexArray(vao);

                for (unsigned i = 0; i < attributeCount; i++)
                {
                    auto attr = attrs[i];
                    switch (type)
                    {
                    case VboType::Float:
                        glVertexAttribPointer(attr.name, attr.size, static_cast<GLenum>(type), GL_FALSE, vertexSizeInBytes, (void*)attr.start);
                        break;
                    case VboType::Double:
                        glVertexAttribLPointer(attr.name, attr.size, static_cast<GLenum>(type), vertexSizeInBytes, (void*)attr.start);
                        break;
                    case VboType::Int:
                    case VboType::UnsignedInt:
                    case VboType::Short:
                    case VboType::UnsignedShort:
                    case VboType::Byte:
                    case VboType::UnsignedByte:
                        glVertexAttribIPointer(attr.name, attr.size, static_cast<GLenum>(type), vertexSizeInBytes, (void*)attr.start);
                        break;
                    }
                    glEnableVertexAttribArray(attr.name);
                }
            }

            return VbObject(vao, currentVbo, mode);
        }
    }
}
