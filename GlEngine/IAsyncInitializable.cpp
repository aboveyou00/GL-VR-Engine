#include "stdafx.h"
#include "IAsyncInitializable.h"

namespace GlEngine
{
    bool IAsyncInitializable::needsGraphics()
    {
        return true;
    }
}
