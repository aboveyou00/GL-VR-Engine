#include "stdafx.h"
#include "StringUtils.h"
#include "KeyValuePair.h"
#include <string> //Used only for stof, and strcmp
#include <stdexcept> //Used only for stof - because the C++ standard library is dumb and doesn't provide a no-exception version

namespace GlEngine
{
    namespace Util
    {
        bool stoi(const char *const str, int &value)
        {
            //This function only supports base 10, will allow leading zeros, and will allow one sign upfront.
            //Strip spaces first, it will not do so.

            auto idx = 0;
            unsigned long long tmpVal = 0;

            bool negative = false;
            auto chr = *(str + idx);
            if (chr == '-') { negative = true; idx++; }
            else if (chr == '+') { idx++; } //Collect the sign, if there is one

            chr = *(str + idx);
            if (chr < '0' || chr > '9') return false; //There must be at least one digit

            while ((chr = *(str + idx++)) != '\0')
            {
                if (chr < '0' || chr > '9') { return false; }
                else { tmpVal *= 10; tmpVal += (int)(chr - '0'); }
            }

            if (negative && tmpVal > (unsigned long long)-(long long)std::numeric_limits<int>::min()) return false;
            else if (!negative && tmpVal > std::numeric_limits<int>::max()) return false;
            value = (negative ? -1 : 1) * (int)tmpVal;
            return true;
        }
        bool stof(const char *const str, float &value)
        {
            try
            {
                value = std::stof(str);
                return true;
            }
            catch (std::invalid_argument) { return false; }
            catch (std::out_of_range) { return false; }
        }
        int strcmp(const char *const lhs, const char *const rhs)
        {
            return std::strcmp(lhs, rhs);
        }

        inline bool isWhitespace(char chr)
        {
            return (chr == ' ' || chr == '\t' || chr == '\r' || chr == '\n');
        }
        inline char interpretEscapeCharacter(char chr)
        {
            switch (chr)
            {
            case 'r':
                return '\r';
            case 'n':
                return '\n';
            case '0':
                return '\0';
            case '\\':
            case '"':
            case '\'':
            default:
                return chr;
                break;
            }
        }
        inline bool collectCharacter(int &tokenLen, int buffSize, const char *&ptr, char *tokenBuff)
        {
            if (tokenLen >= buffSize) return false; //Too long!
            if (*ptr == '\\')
            {
                tokenBuff[tokenLen++] = interpretEscapeCharacter(*(++ptr));
                ptr++;
            }
            else tokenBuff[tokenLen++] = *(ptr++);
            return true;
        }

        //This method makes the assumption that pos is a valid index in this string; str + pos should never be after the terminating \0 on str
        bool extractToken(char *buff, int buffSize, const char *&ptr)
        {
            if (ptr == nullptr) return false;
            while (isWhitespace(*ptr))
                ptr++;
            if (*ptr == '\0') return false;

            int tokenLen = 0;

            if (*ptr == '/' && *(ptr + 1) == '/') return false; //Beginning of a single-line comment
            else if (*ptr == '"')
            {
                ptr++;
                while (*ptr != '"' && *ptr != '\0')
                    if (!collectCharacter(tokenLen, buffSize, ptr, buff)) return false;
                if (*ptr++ == '\0') return nullptr;
            }
            else
            {
                while (!isWhitespace(*ptr) && *ptr != '\0' && (*ptr != '/' || *(ptr + 1) != '/'))
                    if (!collectCharacter(tokenLen, buffSize, ptr, buff)) return false;
            }

            buff[tokenLen] = '\0';
            return true;
        }
    }
}
