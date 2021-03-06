#include "stdafx.h"
#include "StringUtils.h"
#include "KeyValuePair.h"
#include <sstream>

namespace GlEngine
{
    namespace Util
    {
        inline bool isWhitespace(char c) noexcept
        {
            return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\r');
        }

        inline bool isNumeric(char c) noexcept
        {
            return ('0' <= c && c <= '9');
        }

        inline bool isLetter(char c) noexcept
        {
            return ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z');
        }

        inline bool isAlphanumeric(char c) noexcept
        {
            return isNumeric(c) || isLetter(c);
        }

        void eatWhitespace(std::istream& in) noexcept
        {
            while (isWhitespace((char)in.peek()))
            {
                in.get();
            }
            char c = (char)in.peek(); c;
        }

        const char * const eatWhitespace(const char * const str) noexcept
        {
            int i = 0;
            while (str[i++] != 0)
            {
                if (!isWhitespace(str[i]))
                    return str + i;
            }
            return str;
        }

        bool stoi(const char *const str, int &value) noexcept
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

            if (negative && tmpVal > (unsigned long long) - (long long)std::numeric_limits<int>::min()) return false;
            else if (!negative && tmpVal > std::numeric_limits<int>::max()) return false;
            value = (negative ? -1 : 1) * (int)tmpVal;
            return true;
        }
        bool geti(std::istream& in, int &value) noexcept
        {
            auto start = in.tellg();

            eatWhitespace(in);

            unsigned long long tmpVal = 0;

            bool negative = false;
            auto chr = in.peek();
            if (chr == '-') { negative = true; in.get(); }
            else if (chr == '+') { in.get(); } //Collect the sign, if there is one

            chr = in.peek();
            if (chr < '0' || chr > '9') //There must be at least one digit
            {
                in.seekg(start);
                return false; 
            }

            while ((chr = in.peek()) != '\0')
            {
                if (chr == '.')
                {
                    in.seekg(start);
                    return false;
                }
                if (chr < '0' || chr > '9') { break; }
                else { tmpVal *= 10; tmpVal += (int)(chr - '0'); }
                in.get();
            }

            if (negative && tmpVal > (unsigned long long) - (long long)std::numeric_limits<int>::min())
            {
                in.seekg(start);
                return false;
            }
            else if (!negative && tmpVal > std::numeric_limits<int>::max())
            {
                in.seekg(start);
                return false;
            }
            value = (negative ? -1 : 1) * (int)tmpVal;
            return true;
        }
        bool stof(const char *const str, float &value) noexcept
        {
            std::stringstream in(str);
            return getf(in, value);
        }
        bool getf(std::istream& in, float& value) noexcept
        {
            return (bool)(in >> value);
        }
        int strcmp(const char *const lhs, const char *const rhs) noexcept
        {
            return std::strcmp(lhs, rhs);
        }

        ENGINE_SHARED std::string itos(int value)
        {
            char result[12];
            sprintf_s(result, "%i", value);
            return std::string(result);
        }

        ENGINE_SHARED std::string ftos(float value)
        {
            char result[32];
            sprintf_s(result, "%f", value);
            return std::string(result);
        }

        static int charClass(char chr)
        {
            return     isWhitespace(chr) ? 0 :
                     isAlphanumeric(chr) ? 1 :
              chr == '\n' || chr == '\r' ? 2 :
                                           3;
        }
        ENGINE_SHARED unsigned findEndOfWord(std::string text, unsigned currentPos) noexcept
        {
            auto previousClass = 0;
            while (currentPos < text.size())
            {
                auto currentClass = charClass(text.at(currentPos));
                if (previousClass != currentClass && previousClass != 0) break;
                previousClass = currentClass;
                currentPos++;
            }
            return currentPos;
        }
        ENGINE_SHARED unsigned findBeginningOfWord(std::string text, unsigned currentPos) noexcept
        {
            auto previousClass = 0;
            while (currentPos > 0)
            {
                auto currentClass = charClass(text.at(currentPos - 1));
                if (previousClass != currentClass && previousClass != 0) break;
                previousClass = currentClass;
                currentPos--;
            }
            return currentPos;
        }

        bool is_empty(const char *const str) noexcept
        {
            return str == nullptr || *str == '\0';
        }
        bool is_empty_or_ws(const char *const str) noexcept
        {
            if (str == nullptr) return true;
            auto ptr = str;
            char chr;
            while ((chr = *ptr) != '\0')
                if (!isWhitespace(chr))
                    return false;
            return true;
        }
        bool is_empty_or_ws(const std::string *const str) noexcept
        {
            if (str == nullptr) return true;
            return is_empty_or_ws(*str);
        }
        bool is_empty_or_ws(const std::string &str) noexcept
        {
            for (auto it = str.begin(); it != str.end(); it++)
                if (!isWhitespace(*it)) return false;
            return true;
        }

        inline char interpretEscapeCharacter(char chr) noexcept
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
        inline bool collectCharacter(int &tokenLen, int buffSize, const char *&ptr, char *tokenBuff) noexcept
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
        bool extractToken(char *buff, int buffSize, const char *&ptr) noexcept
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

        std::string regex_replace_callback(std::string source, std::string regex, std::function<std::string(std::smatch)> func)
        {
            std::regex r(regex);

            std::string::const_iterator lastEnd(source.cbegin());

            std::stringstream stream;
            while (true) {
                std::smatch results;
                if (!std::regex_search(lastEnd, source.cend(), results, r)) break;

                stream << std::string(&*lastEnd, &*lastEnd + results.position());
                stream << func(results);

                lastEnd += results.position() + results.length();
            }

            if (lastEnd != source.cend())
                stream << &*lastEnd;
            return stream.str();
        }
    }
}
