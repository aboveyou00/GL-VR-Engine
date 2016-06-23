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
            if (key == nullptr || value == nullptr) return;
            strcpy_s(_key, MAX_KEY_SIZE, key);
            strcpy_s(_value, MAX_VALUE_SIZE, value);
        }
        KeyValuePair::~KeyValuePair()
        {
        }
    }
}
