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

//Fixes because... why in the world is a word as common as this used as a macro?

#ifdef near
#undef near
#endif

#ifdef far
#undef far
#endif

//Fixes becaues they break YSE:

#ifdef RELATIVE
const auto COORDINATE_MODE_RELATIVE = RELATIVE;
#undef RELATIVE
const auto RELATIVE = COORDINATE_MODE_RELATIVE;
#endif

template<char c>
constexpr inline unsigned VK_ALPHANUMERIC()
{
    static_assert(('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z') || ('0' <= c && c <= '9'), "Only numbers and letters are allowed");
    return (c >= 'a' && c <= 'z') ? 65 + (c - 'a') : c;
}

const double PI_d = 3.1415926535897932;
const float PI_f = 3.1415926f;

static const unsigned VK_PAGE_UP = VK_PRIOR;
static const unsigned VK_PAGE_DOWN = VK_NEXT;

static const unsigned VK_SQUARE_BRACKET_LEFT = VK_OEM_4;
static const unsigned VK_SQUARE_BRACKET_RIGHT = VK_OEM_6;
static const unsigned VK_BACKSLASH = VK_OEM_5;
static const unsigned VK_FORWARD_SLASH = VK_OEM_2;

static const unsigned VK_ALT = VK_MENU;
static const unsigned VK_LALT = VK_LMENU;
static const unsigned VK_RALT = VK_RMENU;
