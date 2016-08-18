#include "stdafx.h"
#include "FbxLoader.h"
#include "FbxGraphicsObjectImpl.h"

namespace GlEngine
{
    namespace Impl
    {
        bool FbxGraphicsObjectImpl::SharedInitialize(VboGraphicsObjectImpl *self, const char *const filename)
        {
            return GlEngine::FbxLoader::Load(filename, self);
        }
    }
}
