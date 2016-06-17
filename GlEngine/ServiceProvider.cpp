#include "stdafx.h"
#include "ServiceProvider.h"

namespace GlEngine
{
    ServiceProvider::ServiceProvider()
    {
    }
    ServiceProvider::~ServiceProvider()
    {
    }

    void ServiceProvider::RegisterService(IService *svc)
    {
        for (size_t q = 0; q < MAX_SVCS; q++)
        {
            if (_svcs[q] == nullptr)
            {
                _svcs[q] = svc;
                return;
            }
        }
    }
    void ServiceProvider::DeregisterService(IService *svc)
    {
        for (size_t q = 0; q < MAX_SVCS; q++)
        {
            if (_svcs[q] == svc)
            {
                _svcs[q] = nullptr;
                return;
            }
        }
    }
}
