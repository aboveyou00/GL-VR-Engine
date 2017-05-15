#pragma once

#include "IService.h"
#include "StringUtils.h"

namespace GlEngine
{
    class ENGINE_SHARED IConfigProvider : public IService
    {
    public:
        IConfigProvider();
        ~IConfigProvider();

        virtual bool IsFull() const = 0;
        virtual const char *const operator[](const char *const key) const = 0;

        virtual bool AddUnique(const char *const key, const char *const value) = 0;

        bool ContainsKey(const char *const key) const;

        template <typename T = const char*>
        bool GetValue(const char *const key, T &value) const
        {
            static_assert(false, "You can't use the template method (GetValue) with that type argument!");
        }
        template <>
        bool GetValue<const char*>(const char *const key, const char *&value) const
        {
            value = (*this)[key];
            return value != nullptr;
        }
        template <>
        bool GetValue<int>(const char *const key, int &value) const
        {
            const char *strVal;
            if (!GetValue(key, strVal)) return false;
            if (strVal == nullptr) return false;
            return Util::stoi(strVal, value);
        }
        template <>
        bool GetValue<float>(const char *const key, float &value) const
        {
            const char *strVal;
            if (!GetValue(key, strVal)) return false;
            if (strVal == nullptr) return false;
            return Util::stof(strVal, value);
        }
        template <>
        bool GetValue<bool>(const char *const key, bool &value) const
        {
            const char *strVal;
            if (!GetValue(key, strVal)) return false;
            if (strVal == nullptr) return false;
            if (Util::strcmp(strVal, "true") == 0 || Util::strcmp(strVal, "yes") == 0 || Util::strcmp(strVal, "enabled") == 0)
            {
                value = true;
                return true;
            }
            else if (Util::strcmp(strVal, "false") == 0 || Util::strcmp(strVal, "no") == 0 || Util::strcmp(strVal, "disabled") == 0)
            {
                value = false;
                return true;
            }
            return false;
        }

        template <typename T = const char*>
        T GetValue(const char *const key)
        {
            T value;
            auto worked = GetValue(key, value);
            if (!worked) throw std::invalid_argument("The requested key does not exist: "s + key);
            return value;
        }

        template <typename T = const char*>
        T GetValueWithDefault(const char *const key, T defaultValue = default(T))
        {
            T value;
            if (!GetValue(key, value)) return defaultValue;
            return value;
        }
    };
}
