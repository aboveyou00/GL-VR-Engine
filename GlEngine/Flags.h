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
