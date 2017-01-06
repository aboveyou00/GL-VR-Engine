#pragma once

namespace GlEngine
{
    namespace Util
    {
        ENGINE_SHARED bool isWhitespace(char c) noexcept;
        ENGINE_SHARED bool isNumeric(char c) noexcept;
        ENGINE_SHARED void eatWhitespace(std::istream& in) noexcept;
        ENGINE_SHARED const char * const eatWhitespace(const char * const str) noexcept;

        ENGINE_SHARED bool stoi(const char *const str, int &value) noexcept;
        ENGINE_SHARED bool geti(std::istream& in, int &value) noexcept;
        ENGINE_SHARED bool stof(const char *const str, float &value) noexcept;
        ENGINE_SHARED bool getf(std::istream& in, float &value) noexcept;
        ENGINE_SHARED int strcmp(const char *const lhs, const char *const rhs) noexcept;

        ENGINE_SHARED bool is_empty(const char *const str) noexcept;
        ENGINE_SHARED bool is_empty_or_ws(const char *const str) noexcept;

        //IMPORTANT: The return value of this method is invalidated when you call it again, unless it doesn't find another token
        //This method makes the assumption that pos is a valid index in this string; str + pos should never be after the terminating \0 on str
        template <size_t buffSize = 32>
        const char *const extractToken(const char *&ptr)
        {
            static thread_local char tokenBuff[buffSize];
            if (!extractToken(tokenBuff, sizeof(tokenBuff), ptr)) return nullptr;
            return tokenBuff;
        }
        //This method makes the assumption that pos is a valid index in this string; str + pos should never be after the terminating \0 on str
        ENGINE_SHARED bool extractToken(char* buff, int buffSize, const char *&ptr) noexcept;
    }
}
