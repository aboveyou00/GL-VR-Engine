#include "stdafx.h"
#include "ServiceProvider.h"
#include "IService.h"

namespace GlEngine
{
    ServiceProvider::ServiceProvider()
    {
    }
    ServiceProvider::~ServiceProvider()
    {
        for (size_t q = MAX_SVCS - 1; q >= 0; q--)
        {
            if (_svcs[q] != nullptr)
            {
                delete _svcs[q];
                _svcs[q] = nullptr;
            }
        }
    }

    void ServiceProvider::RegisterService(IService *svc)
    {
        ScopedLock _lock(_mutex);
        for (size_t q = 0; q < MAX_SVCS; q++)
        {
            if (_svcs[q] == nullptr)
            {
                _svcs[q] = svc;
                return;
            }
        }
    }
}
