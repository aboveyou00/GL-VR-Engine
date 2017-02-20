#pragma once

namespace GlEngine
{
    class ENGINE_SHARED IInitializable
    {
    public:
        virtual bool Initialize() = 0;
        virtual void Shutdown() = 0;

        virtual std::string name() = 0;
    };
}
