#pragma once

#include "IGraphicsComponent.h"
#include "VbObject.h"

namespace GlEngine
{
    class VbObjectAttribList;

    class ENGINE_SHARED VaObject : public IGraphicsComponent
    {
    public:
        VaObject();
        VaObject(unsigned vao);
        VaObject(unsigned vao, std::vector<VbObjectAttribList*> *vbo_attribs);
        ~VaObject();

        bool Initialize();
        void Shutdown();
        bool InitializeGraphics();
        void ShutdownGraphics();

        void MakeCurrent();

        operator bool();
        const char *name() override;

        inline std::vector<VbObjectAttribList*> *GetVboAttributes()
        {
            return _vbos;
        }

    private:
        unsigned _vao;
        std::vector<VbObjectAttribList*> *_vbos;
        BufferMode _mode;
    };
}
