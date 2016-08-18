#pragma once

namespace GlEngine
{
    namespace Impl
    {
        class VboGraphicsObjectImpl;

        class ENGINE_SHARED FbxGraphicsObjectImpl
        {
        private:
            FbxGraphicsObjectImpl() { }
            ~FbxGraphicsObjectImpl() { }

        public:
            static bool SharedInitialize(VboGraphicsObjectImpl *self, const char *const filename);
        };
    }
}
