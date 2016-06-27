#include "stdafx.h"
#include "KeyValuePair.h"

namespace GlEngine
{
    namespace Util
    {
        KeyValuePair::KeyValuePair()
            : KeyValuePair(nullptr, nullptr)
        {
        }
        KeyValuePair::KeyValuePair(const char *const key, const char *const value)
        {
            if (key != nullptr) strcpy_s(_key, MAX_KEY_SIZE, key);
            else _key[0] = '\0';
            if (value != nullptr) strcpy_s(_value, MAX_VALUE_SIZE, value);
            else _value[0] = '\0';
        }
        KeyValuePair::~KeyValuePair()
        {
        }
    }
}
