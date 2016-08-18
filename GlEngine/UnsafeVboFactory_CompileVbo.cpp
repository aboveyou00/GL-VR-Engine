#include "stdafx.h"
#include "UnsafeVboFactory.h"

#include "OpenGl.h"
#include "VaoFactory.h"

namespace GlEngine
{
    namespace Impl
    {
        VbObject CompileVbo(VaoFactory *vao, bool instanced, BufferMode mode, unsigned bufferSizeInBytes, unsigned vertexSizeInBytes, void *front, attribute_descriptor *attrs, unsigned attributeCount, VboType type)
        {
            unsigned currentVbo;
            glGenBuffers(1, &currentVbo);
            glBindBuffer(static_cast<GLenum>(mode), currentVbo);
            glBufferData(static_cast<GLuint>(mode), bufferSizeInBytes, front, GL_STATIC_DRAW);
            
            if (mode == BufferMode::Array)
            {
                for (unsigned i = 0; i < attributeCount; i++)
                {
                    auto attr = attrs[i];
                    switch (type)
                    {
                    case VboType::Float:
                        vao->AddAttrib(attr.size, type, false, vertexSizeInBytes, (void*)attr.start, instanced);
                        break;
                    case VboType::Double:
                        vao->AddAttribL(attr.size, type, vertexSizeInBytes, (void*)attr.start, instanced);
                        break;
                    case VboType::Int:
                    case VboType::UnsignedInt:
                    case VboType::Short:
                    case VboType::UnsignedShort:
                    case VboType::Byte:
                    case VboType::UnsignedByte:
                        vao->AddAttribI(attr.size, type, vertexSizeInBytes, (void*)attr.start, instanced);
                        break;
                    }
                }
            }

            return VbObject(currentVbo, mode);
        }
    }
}
