#pragma once

namespace GlEngine
{
    class IService;

    class ServiceProvider
    {
    public:
        ServiceProvider();
        ~ServiceProvider();

        void RegisterService(IService *svc);
        template <typename TService>
        void RegisterService(TService *svc)
        {
            DeregisterService<TService>();
            RegisterService((IService*)svc);
        }
        template <typename TService>
        void DeregisterService()
        {
            for (size_t q = 0; q < MAX_SVCS; q++)
            {
                auto cast = dynamic_cast<TService*>(_svcs[q]);
                if (cast != nullptr) _svcs[q] = nullptr;
            }
        }
        template <typename TService>
        TService *GetService()
        {
            for (size_t q = 0; q < MAX_SVCS; q++)
            {
                auto cast = dynamic_cast<TService*>(_svcs[q]);
                if (cast != nullptr) return cast;
            }
            return nullptr;
        }

    private:
        static const int MAX_SVCS = 12;
        IService *_svcs[MAX_SVCS] = { nullptr };
    };
}
