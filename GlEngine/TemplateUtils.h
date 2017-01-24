#pragma once

namespace GlEngine::Util
{
    //Adapted from http://stackoverflow.com/a/10766422/768597

    namespace Impl
    {
        template <typename F, typename Tuple, bool Done, int Total, int... N>
        struct call_impl
        {
            template <typename... TArgs>
            static void call(F f, Tuple &&t, TArgs... args)
            {
                call_impl<F, Tuple, Total == 1 + sizeof...(N), Total, N..., sizeof...(N)>::call(f, std::forward<Tuple>(t), args...);
            }
        };

        template <typename F, typename Tuple, int Total, int... N>
        struct call_impl<F, Tuple, true, Total, N...>
        {
            template <typename... TArgs>
            static void call(F f, Tuple &&t, TArgs... args)
            {
                f(args..., std::get<N>(std::forward<Tuple>(t))...);
            }
        };
    }

    template <typename F, typename Tuple, typename... TArgs>
    void call(F f, Tuple &&t, TArgs... args)
    {
        typedef typename std::decay<Tuple>::type ttype;
        Impl::call_impl<F, Tuple, 0 == std::tuple_size<ttype>::value, std::tuple_size<ttype>::value>::call(f, std::forward<Tuple>(t), args...);
    }
}
