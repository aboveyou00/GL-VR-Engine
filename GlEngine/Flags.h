#pragma once

#define FLAGS_H_PREDECL(flags_name) \
    enum class flags_name : unsigned; \
     \
    inline constexpr ENGINE_SHARED flags_name operator|(flags_name one, flags_name two); \
    inline constexpr ENGINE_SHARED flags_name operator&(flags_name one, flags_name two); \
    inline constexpr ENGINE_SHARED flags_name operator^(flags_name one, flags_name two); \
     \
    inline constexpr ENGINE_SHARED flags_name operator~(flags_name type); \
     \
    inline ENGINE_SHARED flags_name operator|=(flags_name &one, flags_name two); \
    inline ENGINE_SHARED flags_name operator&=(flags_name &one, flags_name two); \
    inline ENGINE_SHARED flags_name operator^=(flags_name &one, flags_name two);

#define FLAGS_H_DECL(flags_name) \
    FLAGS_H_PREDECL(flags_name) \
    enum class ENGINE_SHARED flags_name : unsigned

#define FLAGS_H(flags_name) \
    inline constexpr ENGINE_SHARED flags_name operator|(flags_name one, flags_name two) \
    { \
        return static_cast<flags_name>(static_cast<unsigned>(one) | static_cast<unsigned>(two)); \
    } \
    inline constexpr ENGINE_SHARED flags_name operator&(flags_name one, flags_name two) \
    { \
        return static_cast<flags_name>(static_cast<unsigned>(one) & static_cast<unsigned>(two)); \
    } \
    inline constexpr ENGINE_SHARED flags_name operator^(flags_name one, flags_name two) \
    { \
        return static_cast<flags_name>(static_cast<unsigned>(one) ^ static_cast<unsigned>(two)); \
    } \
     \
    inline constexpr ENGINE_SHARED flags_name operator~(flags_name type) \
    { \
        return static_cast<flags_name>(~static_cast<unsigned>(type)); \
    } \
     \
    inline ENGINE_SHARED flags_name operator|=(flags_name &one, flags_name two) \
    { \
        return one = static_cast<flags_name>(static_cast<unsigned>(one) | static_cast<unsigned>(two)); \
    } \
    inline ENGINE_SHARED flags_name operator&=(flags_name &one, flags_name two) \
    { \
        return one = static_cast<flags_name>(static_cast<unsigned>(one) & static_cast<unsigned>(two)); \
    } \
    inline ENGINE_SHARED flags_name operator^=(flags_name &one, flags_name two) \
    { \
        return one = static_cast<flags_name>(static_cast<unsigned>(one) ^ static_cast<unsigned>(two)); \
    }

#define CONTIGUOUS_ENUM_H(enum_name, min_val, max_val) \
    template<> \
    constexpr enum_name std::numeric_limits<enum_name>::min() noexcept \
    { \
        return enum_name::min_val; \
    } \
    template<> \
    constexpr enum_name std::numeric_limits<enum_name>::max() noexcept \
    { \
        return enum_name::max_val; \
    } \
     \
    enum_name ENGINE_SHARED operator++(enum_name &ref, int) noexcept; \
    enum_name ENGINE_SHARED operator--(enum_name &ref, int) noexcept; \
    enum_name ENGINE_SHARED operator++(enum_name &ref) noexcept; \
    enum_name ENGINE_SHARED operator--(enum_name &ref) noexcept;

#define CONTIGUOUS_ENUM_CPP(enum_name) \
    enum_name operator++(enum_name &ref, int) noexcept \
    { \
        auto oldval = ref; \
        ref = static_cast<enum_name>(static_cast<unsigned>(ref) + 1); \
        return oldval; \
    } \
    enum_name operator--(enum_name &ref, int) noexcept \
    { \
        auto oldval = ref; \
        ref = static_cast<enum_name>(static_cast<unsigned>(ref) - 1); \
        return oldval; \
    } \
    enum_name operator++(enum_name &ref) noexcept \
    { \
        ref = static_cast<enum_name>(static_cast<unsigned>(ref) + 1); \
        return ref; \
    } \
    enum_name operator--(enum_name &ref) noexcept \
    { \
        ref = static_cast<enum_name>(static_cast<unsigned>(ref) - 1); \
        return ref; \
    }
