#pragma once

#include "ILogger.h"

namespace GlEngine
{
    class IService;

    //WARNING: Registering a service means giving up ownership.
    //After you do it, you commit to making the lifetime of that service the lifetime of the ServiceProvider (which should be the lifetime of the program).
    //Even if you deregister the service, there is no guarantee that no other thread has a reference to that service
    //Or is no longer using it. Don't repeatedly register different of the same type of service,
    //Or you will be creating a memory leak.
    class ENGINE_SHARED ServiceProvider
    {
    public:
        ServiceProvider();
        ~ServiceProvider();

        bool RegisterService(IService *svc);
        template <typename TService>
        bool RegisterService(TService *svc)
        {
            ScopedLock _lock(_mutex);
            auto logger = GetService<ILogger>();
            if (logger != nullptr) logger->Log(LogType::Info, "Registering service for %s", typeid(TService).name());
            auto previous = GetService<TService>();
            if (previous != nullptr)
            {
                if (logger != nullptr) logger->Log(LogType::Error, "Attempted to register a duplicate service");
                return false;
            }

            return RegisterService((IService*)svc);
        }
        template <typename TService>
        TService *GetService()
        {
            ScopedLock _lock(_mutex);
            for (size_t q = 0; q < MAX_SVCS; q++)
            {
                auto cast = dynamic_cast<TService*>(_svcs[q]);
                if (cast != nullptr) return cast;
            }
            return nullptr;
        }

    private:
        rt_mutex _mutex;

        static const int MAX_SVCS = 12;
        IService *_svcs[MAX_SVCS] = { nullptr };
    };
}
