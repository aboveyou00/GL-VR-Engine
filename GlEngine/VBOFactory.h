#pragma once

#include "UnsafeVboFactory.h"
#include "vbo_attribs.h"

namespace GlEngine
{
    template <VboType type, typename... TArgs>
    class VboFactory : private UnsafeVboFactory<type, compound_vbo_attribs<type, TArgs...>::attrib_count>
    {
    public:
        VboFactory(BufferMode mode)
            : UnsafeVboFactory(compound_vbo_attribs<type, TArgs...>::element_count, mode)
        {
            compound_vbo_attribs<type, TArgs...>::add_attribs(*this);
        }
        ~VboFactory()
        {
        }

        void Allocate(unsigned vertexCount)
        {
            UnsafeVboFactory::Allocate(vertexCount);
        }

        int AddVertex(TArgs... args)
        {
            //return AddVertex(args..., currentMode == BufferMode::Array ? true : false);
            return AddVertex(args..., false);
        }
        int AddVertex(TArgs... args, bool checkCache)
        {
            assert(!checkCache);
            //if (checkCache)
            //{
            //    check_cache_data.clear();
            //    compound_vbo_attribs<type, TArgs...>::push(args..., check_cache_data);

            //    auto numElements = data.size() / vertexSizeInElements;
            //    for (size_t q = 0; q < numElements; q++)
            //    {
            //        auto base_idx = q * vertexSizeInElements;
            //        for (size_t w = 0; w < vertexSizeInElements; w++)
            //            if (data[base_idx + w] != check_cache_data[w])
            //                goto continue_cache;
            //        return q;
            //    continue_cache:;
            //    }

            //    for (size_t q = 0; q < vertexSizeInElements; q++)
            //        data.push_back(check_cache_data[q]);
            //    return numElements;
            //}
            //else
            //{
                compound_vbo_attribs<type, TArgs...>::push(args..., data);
                return elemIdx++;
            //}
        }
        void RemoveVertex(unsigned idx)
        {
            UnsafeVboFactory::RemoveVertex(idx);
        }

        VbObject Compile(VaoFactory *vao, bool instanced = false)
        {
            return UnsafeVboFactory::Compile(vao, instanced);
        }

        BufferMode mode()
        {
            return currentMode;
        }

    //private:
    //    std::vector<el_type> check_cache_data;
    };

    using ElementVboFactory = VboFactory<VboType::UnsignedShort, uint16_t, uint16_t, uint16_t>;
}
