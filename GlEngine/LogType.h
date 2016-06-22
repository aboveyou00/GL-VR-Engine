#pragma once

namespace GlEngine
{
    enum class LogType;

    inline constexpr ENGINE_SHARED LogType operator|(LogType one, LogType two);
    inline constexpr ENGINE_SHARED LogType operator&(LogType one, LogType two);
    inline constexpr ENGINE_SHARED LogType operator^(LogType one, LogType two);

    inline constexpr ENGINE_SHARED LogType operator~(LogType type);

    inline ENGINE_SHARED LogType operator|=(LogType &one, LogType two);
    inline ENGINE_SHARED LogType operator&=(LogType &one, LogType two);
    inline ENGINE_SHARED LogType operator^=(LogType &one, LogType two);

    enum class LogType
    {
        Ignore      = 0,
        Console     = 0b000001,

        Info        = 0b000010,
        InfoC       = LogType::Info | LogType::Console,
        Warning     = 0b000100,
        WarningC    = LogType::Warning | LogType::Console,
        Error       = 0b001000,
        ErrorC      = LogType::Error | LogType::Console,
        FatalError  = 0b010000,
        FatalErrorC = LogType::FatalError | LogType::Console,
    };

    inline constexpr ENGINE_SHARED LogType operator|(LogType one, LogType two)
    {
        return static_cast<LogType>(static_cast<unsigned>(one) | static_cast<unsigned>(two));
    }
    inline constexpr ENGINE_SHARED LogType operator&(LogType one, LogType two)
    {
        return static_cast<LogType>(static_cast<unsigned>(one) & static_cast<unsigned>(two));
    }
    inline constexpr ENGINE_SHARED LogType operator^(LogType one, LogType two)
    {
        return static_cast<LogType>(static_cast<unsigned>(one) ^ static_cast<unsigned>(two));
    }

    inline constexpr ENGINE_SHARED LogType operator~(LogType type)
    {
        return static_cast<LogType>(~static_cast<unsigned>(type));
    }

    inline ENGINE_SHARED LogType operator|=(LogType &one, LogType two)
    {
        return one = static_cast<LogType>(static_cast<unsigned>(one) ^ static_cast<unsigned>(two));
    }
    inline ENGINE_SHARED LogType operator&=(LogType &one, LogType two)
    {
        return one = static_cast<LogType>(static_cast<unsigned>(one) ^ static_cast<unsigned>(two));
    }
    inline ENGINE_SHARED LogType operator^=(LogType &one, LogType two)
    {
        return one = static_cast<LogType>(static_cast<unsigned>(one) ^ static_cast<unsigned>(two));
    }

    const char *const MakeReadableLogType(LogType type);
}
