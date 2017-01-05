#pragma once

namespace GlEngine
{
    namespace ShaderFactory
    {
        class ENGINE_SHARED Environment
        {
        public:
            Environment();
            ~Environment();

            float GetGameTime();
        };
    }
}
