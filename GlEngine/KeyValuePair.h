#pragma once

namespace GlEngine
{
    namespace Util
    {
        class ENGINE_SHARED KeyValuePair
        {
        public:
            KeyValuePair();
            KeyValuePair(const char *const key, const char *const value);
            ~KeyValuePair();

            inline const char *const GetKey() const
            {
                return _key;
            }
            inline const char *const GetValue() const
            {
                return _value;
            }

            static const size_t MAX_KEY_SIZE = 32;
            static const size_t MAX_VALUE_SIZE = 64;

        private:
            char _key[MAX_KEY_SIZE],
                 _value[MAX_VALUE_SIZE];
        };
    }
}
