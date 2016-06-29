#pragma once

#include "BufferMode.h"
#include "VbObject.h"
#include "VboType.h"

namespace GlEngine
{
    namespace Impl
    {
        typedef struct { unsigned name, start, size; } attribute_descriptor;
        VbObject CompileVbo(BufferMode mode, unsigned bufferSizeInBytes, unsigned vertexSizeInBytes, char *front, attribute_descriptor *attrs, unsigned attributeCount, VboType type);
    }

    template <VboType type = VboType::Float, unsigned attribCount = 1>
    class UnsafeVboFactory
    {
    private:
        typedef typename vbo_type_attribs<type>::type el_type;

    public:
        UnsafeVboFactory(unsigned vertexSizeInElements, BufferMode mode)
            : vertexSizeInElements(vertexSizeInElements), currentMode(mode)
        {
            attribIdx = 0;
        }
        ~UnsafeVboFactory()
        {
        }

        void AddAttrib(unsigned attrib, unsigned start, unsigned size)
        {
            assert(attribIdx <= attribCount);

            attribs[attribIdx].name = attrib;
            attribs[attribIdx].start = start;
            attribs[attribIdx].size = size;
            attribIdx++;
        }

        void Allocate(unsigned vertexCount)
        {
            data.reserve(vertexCount * attribCount);
        }

        void AddVertex(el_type *elements, unsigned count)
        {
            for (size_t q = 0; q < min(count, vertexSize); q++)
            {
                data.push_back(elements[q]);
            }
            for (size_t q = min(count, vertexSize); q < vertexSize; q++)
            {
                data.push_back(0.f);
            }
        }
        void AddVertex(el_type *elements)
        {
            AddVertex(elements, vertexSizeInElements);
        }

        VbObject Compile()
        {
            assert(attribIdx == attribCount);
            return Impl::CompileVbo(currentMode, data.size() * sizeof(el_type), vertexSizeInElements * sizeof(el_type), (char*)&data[0], attribs, attribCount, type);
        }

    protected:
        std::vector<el_type> data;

    private:
        unsigned vertexSizeInElements = 0;
        BufferMode currentMode;

        unsigned attribIdx = 0;
        Impl::attribute_descriptor attribs[attribCount];
    };
}
