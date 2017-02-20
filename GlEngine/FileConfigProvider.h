#pragma once

#include "IConfigProvider.h"
#include "IInitializable.h"
#include "KeyValuePair.h"

namespace GlEngine
{
    class ENGINE_SHARED FileConfigProvider : public IConfigProvider, public IInitializable
    {
    public:
        FileConfigProvider(const char *const path, const char *const filename);
        ~FileConfigProvider();

        virtual bool Initialize() override;
        virtual void Shutdown() override;

        virtual std::string name() override;

        bool IsFull() const override;
        const char *const operator[](const char *const key) const override;

        bool AddUnique(const char *const key, const char *const value) override;

    private:
        const char *const _path,
                   *const _filename;

        static const size_t MAX_KVPS = 32;
        GlEngine::Util::KeyValuePair _pairs[MAX_KVPS];
    };
}
