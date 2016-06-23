#include "stdafx.h"
#include "IConfigProvider.h"

namespace GlEngine
{
    IConfigProvider::IConfigProvider()
    {
    }
    IConfigProvider::~IConfigProvider()
    {
    }

    bool IConfigProvider::ContainsKey(const char *const key) const
    {
        return (*this)[key] != nullptr;
    }
}
