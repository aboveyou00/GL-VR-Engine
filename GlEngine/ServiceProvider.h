#pragma once

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

        void RegisterService(IService *svc);
        template <typename TService>
        void RegisterService(TService *svc)
        {
            ScopedLock _lock(_mutex);
            assert(GetService<TService>() == nullptr);
            RegisterService((IService*)svc);
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
