#pragma once

#include "IComponent.h"

namespace GlEngine
{
    namespace Impl
    {
        class GraphicsControllerImpl;
    }

    class GraphicsContext;

    class ENGINE_SHARED GraphicsController : public IComponent
    {
    private:
        GraphicsController();
        ~GraphicsController();

        static GraphicsController _instance;

    public:
        inline static GraphicsController &GetInstance()
        {
            return _instance;
        }

        bool Initialize();
        void Shutdown();

        void AddGraphicsContext(GraphicsContext *graphicsContext);

        const char *name() override;

        inline Impl::GraphicsControllerImpl *GetImpl()
        {
            return pimpl;
        }

    private:
        Impl::GraphicsControllerImpl *pimpl;
    };
}
