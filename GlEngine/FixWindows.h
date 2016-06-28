#pragma once

//The entire purpose of this file is to get rid of ridiculus preprocessing directives that only serve to make life hard for everyone.
//There are better alternatives to creating macros for every little thing. Use those instead!

//Fixes because they break std::numeric_limits<T>::min and ::max

#ifdef min
#undef min
#endif

#ifdef max
#undef max
#endif

template <typename T>
inline T max(T one, T two)
{
    return (one > two ? one : two);
}
template <typename T>
inline T min(T one, T two)
{
    return (one < two ? one : two);
}

//Fixes becaues they break YSE:

#ifdef RELATIVE
const auto COORDINATE_MODE_RELATIVE = RELATIVE;
#undef RELATIVE
const auto RELATIVE = COORDINATE_MODE_RELATIVE;
#endif
