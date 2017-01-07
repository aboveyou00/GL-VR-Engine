#pragma once

namespace GlEngine
{
    FLAGS_H_PREDECL(LogType)

    FLAGS_H_DECL(LogType)
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

    FLAGS_H(LogType)

    ENGINE_SHARED const char *const MakeReadableLogType(LogType type);
}
