#pragma once

#include "Engine.h"
#include "LogType.h"
#include <string>

namespace Util
{
    template <typename... TArgs>
    bool Log(std::string format, TArgs... args)
    {
        return Log(GlEngine::LogType::InfoC, format.c_str(), args...);
    }
    template <typename... TArgs>
    bool Log(GlEngine::LogType type, std::string format, TArgs... args)
    {
        return Log(type, format.c_str(), args...);
    }
    template <typename... TArgs>
    bool Log(const char * const format, TArgs... args)
    {
        return Log(GlEngine::LogType::InfoC, format, args...);
    }
    template <typename... TArgs>
    bool Log(GlEngine::LogType type, const char * const format, TArgs... args)
    {
        auto logger = GlEngine::Engine::GetInstance().GetServiceProvider().GetService<GlEngine::ILogger>();
        return logger->Log(type, format, args...);
    }
}