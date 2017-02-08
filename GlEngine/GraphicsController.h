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

        virtual bool Initialize();
        virtual void Shutdown();

        void AddGraphicsContext(GraphicsContext *graphicsContext);

        virtual std::string name() override;

        inline Impl::GraphicsControllerImpl *GetImpl()
        {
            return pimpl;
        }

    private:
        Impl::GraphicsControllerImpl *pimpl;
    };
}
