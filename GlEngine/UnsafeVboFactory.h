#pragma once

#include "BufferMode.h"
#include "VbObject.h"
#include "VboType.h"

namespace GlEngine
{
    class VaoFactory;
    namespace Impl
    {
        typedef struct { unsigned name, start, size; } attribute_descriptor;
        VbObject ENGINE_SHARED CompileVbo(VaoFactory *vao, bool instanced, BufferMode mode, unsigned bufferSizeInBytes, unsigned vertexSizeInBytes, void *front, attribute_descriptor *attrs, unsigned attributeCount, VboType type);
    }

    template <VboType type = VboType::Float, unsigned attribCount = 1>
    class UnsafeVboFactory
    {
    protected:
        typedef typename vbo_type_attribs<type>::type el_type;

    public:
        UnsafeVboFactory(unsigned vertexSizeInElements, BufferMode mode)
            : vertexSizeInElements(vertexSizeInElements),
              currentMode(mode),
              elemIdx(0),
              attribIdx(0)
        {
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

        int AddVertex(el_type *elements, unsigned count, bool checkCache = false)
        {
            assert(!checkCache);
            //if (checkCache)
            //    for (size_t q = 0; q < elemIdx; q++)
            //    {
            //        for (size_t w = 0; w < min(count, vertexSize); w++)
            //        {
            //            if (data[(q * vertexSizeInElements) + w] != elements[w]) goto continue_cache;
            //        }
            //        for (size_t w = count; w < vertexSize; w++)
            //        {
            //            if (data[(q * vertexSizeInElements) + w] != 0) goto continue_cache;
            //        }
            //        return q;
            //    continue_cache:
            //    }

            for (size_t q = 0; q < min(count, vertexSize); q++)
            {
                data.push_back(elements[q]);
            }
            for (size_t q = count; q < vertexSize; q++)
            {
                data.push_back(0.f);
            }
            return elemIdx++;
        }
        int AddVertex(el_type *elements, bool checkCache = false)
        {
            return AddVertex(elements, vertexSizeInElements, checkCache);
        }
        void RemoveVertex(unsigned idx)
        {
            assert(idx < elemIdx);
            auto begin = data.begin() + (idx * vertexSizeInElements);
            auto end = data.begin() + ((idx + 1) * vertexSizeInElements) - 1;
            data.erase(begin, end);
            elemIdx--;
        }

        VbObject Compile(VaoFactory *vao, bool instanced = false)
        {
            assert(attribIdx == attribCount);
            void *start;
            if (data.size() == 0) start = nullptr;
            else start = &data[0];
            return Impl::CompileVbo(vao, instanced, currentMode, data.size() * sizeof(el_type), vertexSizeInElements * sizeof(el_type), start, attribs, attribCount, type);
        }

    protected:
        std::vector<el_type> data;
        unsigned vertexSizeInElements = 0;
        BufferMode currentMode;
        unsigned elemIdx = 0;

    private:
        unsigned attribIdx = 0;
        Impl::attribute_descriptor attribs[attribCount];
    };

    template <>
    class UnsafeVboFactory<VboType::Float, 0>
    {
    protected:
        typedef typename vbo_type_attribs<VboType::Float>::type el_type;

    public:
        UnsafeVboFactory(unsigned vertexSizeInElements, BufferMode mode)
            : vertexSizeInElements(vertexSizeInElements), currentMode(mode)
        {
            assert(vertexSizeInElements == 0);
        }
        ~UnsafeVboFactory()
        {
        }

        void AddAttrib(unsigned, unsigned, unsigned)
        {
            assert(false);
        }

        void Allocate(unsigned vertexCount)
        {
            assert(vertexCount == 0);
        }

        int AddVertex(el_type*, unsigned, bool = false)
        {
            assert(false);
            return 0;
        }
        int AddVertex(el_type *elements, bool checkCache = false)
        {
            return AddVertex(elements, vertexSizeInElements, checkCache);
        }

        VbObject Compile(VaoFactory*, bool = false)
        {
            return VbObject();
        }

    protected:
        std::vector<el_type> data;
        unsigned vertexSizeInElements = 0;
        BufferMode currentMode;
    };
}
