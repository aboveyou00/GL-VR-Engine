#include "stdafx.h"
#include "ServiceProvider.h"
#include "IService.h"
#include <limits>

namespace GlEngine
{
    ServiceProvider::ServiceProvider()
    {
        static_assert(MAX_SVCS != std::numeric_limits<unsigned>::max(), "MAX_SVCS must be less than the maximum value for unsigned ints");
    }
    ServiceProvider::~ServiceProvider()
    {
        for (unsigned q = MAX_SVCS - 1; q >= 0 && q < MAX_SVCS; q--)
        {
            if (_svcs[q] != nullptr)
            {
                delete _svcs[q];
                _svcs[q] = nullptr;
            }
        }
    }

    bool ServiceProvider::RegisterService(IService *svc)
    {
        ScopedLock _lock(_mutex);
        for (unsigned q = 0; q < MAX_SVCS; q++)
        {
            if (_svcs[q] == nullptr)
            {
                _svcs[q] = svc;
                return true;
            }
        }

        auto logger = GetService<ILogger>();
        if (logger != nullptr) logger->Log(LogType::Error, "Tried to register more services than the ServiceProvider can contain.");
        return false;
    }
}
