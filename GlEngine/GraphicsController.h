#pragma once

#include "IInitializable.h"

namespace GlEngine
{
    namespace Impl
    {
        class GraphicsControllerImpl;
    }

    class RenderTarget;

    class ENGINE_SHARED GraphicsController : public IInitializable
    {
    private:
        GraphicsController();
        ~GraphicsController();

        friend class RenderTarget;

        static GraphicsController _instance;

    public:
        inline static GraphicsController &GetInstance()
        {
            return _instance;
        }

        virtual bool Initialize() override;
        virtual void Shutdown() override;

        virtual std::string name() override;

        inline Impl::GraphicsControllerImpl *GetImpl()
        {
            return pimpl;
        }

    private:
        Impl::GraphicsControllerImpl *pimpl;

        void addRenderTarget(RenderTarget *target);
    };
}
