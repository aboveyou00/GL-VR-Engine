#include "stdafx.h"
#include "TimeUtils.h"
#include <chrono>

namespace GlEngine
{
    namespace Util
    {
        long long high_resolution_offset = 0;
        
        //IMPORTANT: Each time you call this method, the strings returned by previous calls are invalidated.
        const char *const getTimestamp() noexcept
        {
            static thread_local char buff[32];
            if (!getTimestamp(buff, sizeof(buff))) return nullptr;
            return buff;
        }
        bool getTimestamp(char *buff, int buffSize) noexcept
        {
            if (high_resolution_offset == 0) {
                auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
                auto millis_high_res = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now().time_since_epoch());
                high_resolution_offset = (millis - millis_high_res).count();
            }
            
            auto timeNow = std::chrono::high_resolution_clock::now();
            auto nowFractional = timeNow - std::chrono::time_point_cast<std::chrono::seconds>(timeNow);
            auto nanos = std::chrono::duration_cast<std::chrono::nanoseconds>(nowFractional).count();
            time_t now = (std::chrono::duration_cast<std::chrono::milliseconds>(timeNow.time_since_epoch()).count() + high_resolution_offset) / 1000;

            struct tm tstruct;
            localtime_s(&tstruct, &now); //Convert time_t to local time
            static thread_local char timeBuff[24];
            strftime(timeBuff, sizeof(timeBuff), "%Y-%m-%d.%H-%M-%S", &tstruct); //Format the local time and store it in a temporary buffer

            sprintf_s(buff, buffSize, "%s.%09d", timeBuff, (int)nanos); //Write the temporary buffer and the nanoseconds to the buffer

            //TODO: return false if strftime or sptringf_s failed because the buffers were not large enough
            return true;
        }
    }
}
