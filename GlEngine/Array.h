#pragma once

namespace GlEngine::ShaderFactory
{
    template <typename TElem, unsigned size_arr>
    class Array
    {
    public:
        template <typename... TArgs>
        Array(TArgs... args)
        {
            static_assert(size_arr != 0, "Cannot have an empty Array!");
            ctor(args...);
        }
        ~Array()
        {
        }

        constexpr static unsigned size()
        {
            return size_arr;
        }

        TElem &operator[](unsigned idx)
        {
            return _elems[idx];
        }

    private:
        template <unsigned idx = 0, typename... TArgs>
        void ctor(TElem elem, TArgs... args)
        {
            static_assert(idx < size_arr - 1, "Too many arguments for ShaderFactory::Array!");
            ctor<idx + 1, TArgs...>(args...);
        }
        template <unsigned idx = 0>
        void ctor(TElem elem)
        {
            static_assert(idx == size_arr - 1, "Too few arguments for ShaderFactory::Array!");
            _elems[idx] = elem;
        }

        TElem _elems[size_arr];
    };
}
