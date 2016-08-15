#pragma once

#include "IGraphicsComponent.h"
#include "VbObject.h"

namespace GlEngine
{
    class VaObject : public IGraphicsComponent
    {
    public:
        VaObject();
        VaObject(unsigned vao);
        VaObject(unsigned vao, std::vector<VbObject> *vbos);
        ~VaObject();

        bool Initialize();
        void Shutdown();
        bool InitializeGraphics();
        void ShutdownGraphics();

        void MakeCurrent();

        operator bool();
        const char *name() override;

    private:
        unsigned _vao;
        std::vector<VbObject> *_vbos;
        BufferMode _mode;
    };
}
