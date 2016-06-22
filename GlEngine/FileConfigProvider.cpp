#include "stdafx.h"
#include "FileConfigProvider.h"
#include "FileConfigProviderImpl.h"

namespace GlEngine
{
    FileConfigProvider::FileConfigProvider(const char *const path, const char *const filename)
        : pimpl(new Impl::FileConfigProviderImpl(path, filename))
    {
    }
    FileConfigProvider::~FileConfigProvider()
    {
        Shutdown();
        if (pimpl != nullptr)
        {
            delete pimpl;
            pimpl = nullptr;
        }
    }

    bool FileConfigProvider::Initialize()
    {
        return pimpl->Initialize();
    }
    void FileConfigProvider::Shutdown()
    {
        pimpl->Shutdown();
    }

    bool FileConfigProvider::IsFull() const
    {
        return pimpl->IsFull();
    }
    const char *const FileConfigProvider::operator[](const char *const key) const
    {
        return (*pimpl)[key];
    }

    bool FileConfigProvider::AddUnique(const char *const key, const char *const value)
    {
        return pimpl->AddUnique(key, value);
    }
}
