#include "stdafx.h"
#include "TimeUtils.h"
#include <chrono>

namespace GlEngine
{
    namespace Util
    {
        //IMPORTANT: Each time you call this method, the strings returned by previous calls are invalidated.
        const char *const getTimestamp()
        {
            static thread_local char buff[32];
            if (!getTimestamp(buff, sizeof(buff))) return nullptr;
            return buff;
        }
        bool getTimestamp(char *buff, int buffSize)
        {
            auto chrono_now = std::chrono::system_clock::now();

            time_t now = std::chrono::system_clock::to_time_t(chrono_now); //Convert chrono time to time_t
            struct tm tstruct;
            localtime_s(&tstruct, &now); //Convert time_t to local time
            static thread_local char timeBuff[24];
            strftime(timeBuff, sizeof(timeBuff), "%Y-%m-%d.%H-%M-%S", &tstruct); //Format the local time and store it in a temporary buffer

            auto millisPart = chrono_now - std::chrono::time_point_cast<std::chrono::seconds>(chrono_now);
            auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(millisPart).count();
            sprintf_s(buff, buffSize, "%s.%03d", timeBuff, (int)millis); //Write the temporary buffer and the milliseconds  to the buffer

            //TODO: return false if strftime or sptringf_s failed because the buffers were not large enough
            return true;
        }
    }
}
