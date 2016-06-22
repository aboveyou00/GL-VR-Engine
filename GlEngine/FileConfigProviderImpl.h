#pragma once

#include "IComponent.h"
#include "KeyValuePair.h"

namespace GlEngine
{
    namespace Impl
    {
        class FileConfigProviderImpl : public IComponent
        {
        public:
            FileConfigProviderImpl(const char *const path, const char *const filename);
            ~FileConfigProviderImpl();

            bool Initialize() override;
            void Shutdown() override;

            bool IsFull() const;
            const char *const operator[](const char *const key) const;

            bool AddUnique(const char *const key, const char *const value);

        private:
            const char *const _path,
                       *const _filename;

            static const size_t MAX_KVPS = 32;
            GlEngine::Util::KeyValuePair _pairs[MAX_KVPS];
        };
    }
}
