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

        virtual bool Initialize() override;
        virtual void Shutdown() override;
        virtual bool InitializeGraphics() override;
        virtual void ShutdownGraphics() override;

        void MakeCurrent();

        virtual std::string name() override;

        virtual operator bool() override;

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
