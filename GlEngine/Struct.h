#pragma once

#include <tuple>

namespace GlEngine::ShaderFactory
{
    template <typename... TArgs>
    class Struct
    {
    public:
        Struct(TArgs... args)
            : _tup(args...)
        {
        }
        ~Struct()
        {
        }

        std::tuple<TArgs...> _tup;
    };

    template <>
    class Struct<>;
}
