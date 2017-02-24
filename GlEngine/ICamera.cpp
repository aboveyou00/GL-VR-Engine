#include "stdafx.h"
#include "ICamera.h"

namespace GlEngine
{
    Vector<3> ICamera::clearColor()
    {
        return { 0, 0, 0 };
    }

    bool ICamera::isReady()
    {
        return true;
    }
}
