#pragma once

#include "IConfigProvider.h"
#include "IComponent.h"

namespace GlEngine
{
    namespace Impl
    {
        class FileConfigProviderImpl;
    }

    class FileConfigProvider : public IConfigProvider, public IComponent
    {
    public:
        FileConfigProvider(const char *const path, const char *const filename);
        ~FileConfigProvider();

        bool Initialize();
        void Shutdown();

        bool IsFull() const override;
        const char *const operator[](const char *const key) const override;

        bool AddUnique(const char *const key, const char *const value) override;

    private:
        Impl::FileConfigProviderImpl *pimpl;
    };
}
