#include "stdafx.h"
#include "FileConfigProviderImpl.h"

namespace GlEngine
{
    namespace Impl
    {
        FileConfigProviderImpl::FileConfigProviderImpl(const char *const path, const char *const filename)
            : _path(path), _filename(filename)
        {
        }
        FileConfigProviderImpl::~FileConfigProviderImpl()
        {
        }

        bool FileConfigProviderImpl::Initialize()
        {
            //TODO: open and parse the config file
            return false;
        }
        void FileConfigProviderImpl::Shutdown()
        {
        }

        bool FileConfigProviderImpl::IsFull() const
        {
            for (size_t q = 0; q < MAX_KVPS; q++)
            {
                if (_pairs[q].GetKey() == nullptr || _pairs[q].GetKey()[0] == '\0') return false;
            }
            return true;
        }
        const char *const FileConfigProviderImpl::operator[](const char *const key) const
        {
            for (size_t q = 0; q < MAX_KVPS; q++)
            {
                if (strcmp(key, _pairs[q].GetKey()) == 0) return _pairs[q].GetValue();
            }
            return nullptr;
        }
        bool FileConfigProviderImpl::AddUnique(const char *const key, const char *const value)
        {
            int firstAvailableIndex = -1;
            for (size_t q = 0; q < MAX_KVPS; q++)
            {
                auto pk = _pairs[q].GetKey();
                if (pk == nullptr || pk[0] == '\0')
                {
                    if (firstAvailableIndex == -1) firstAvailableIndex = q;
                    continue;
                }
                if (strcmp(key, _pairs[q].GetKey()) == 0)
                {
                    //TODO: Log attempt at duplicate key.
                    return false;
                }
            }
            if (firstAvailableIndex == -1)
            {
                //TODO: Log failed attempt because there was no space
                return false;
            }
            _pairs[firstAvailableIndex] = Util::KeyValuePair(key, value);
            return true;
        }
    }
}
