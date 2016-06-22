#pragma once

namespace GlEngine
{
    namespace Util
    {
        bool stoi(const char *const str, int &value);
        bool stof(const char *const str, float &value);
        int strcmp(const char *const lhs, const char *const rhs);
    }
}
