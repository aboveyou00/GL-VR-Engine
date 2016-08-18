#pragma once

#include "IGraphicsComponent.h"
#include "TesselationType.h"

namespace GlEngine
{
    class Texture;
    class Shader;

    class ENGINE_SHARED Material : public IGraphicsComponent
    {
    public:
        Material();
        ~Material();

        bool Initialize() override;
        void Shutdown() override;
        bool InitializeGraphics() override;
        void ShutdownGraphics() override;

        virtual void Push(bool instanced = false) = 0;
        virtual void Pop(bool instanced = false) = 0;

        virtual bool IsOpaque() = 0;
        virtual TesselationType GetTesselationType() = 0;
    };
}
