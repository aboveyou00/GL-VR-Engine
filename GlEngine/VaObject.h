#pragma once

#include "IAsyncInitializable.h"
#include "VbObject.h"

namespace GlEngine
{
    class VbObjectAttribList;

    class ENGINE_SHARED VaObject : public IAsyncInitializable
    {
    public:
        VaObject();
        VaObject(unsigned vao);
        VaObject(unsigned vao, std::vector<VbObjectAttribList*> *vbo_attribs);
        ~VaObject();

        virtual bool InitializeAsync() override;
        virtual void ShutdownAsync() override;
        virtual bool InitializeGraphics() override;
        virtual void ShutdownGraphics() override;

        void MakeCurrent();

        virtual std::string name() override;

        virtual bool isReady() override;

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
