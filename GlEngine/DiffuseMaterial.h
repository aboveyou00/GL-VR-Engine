#pragma once

#include "Material.h"

namespace GlEngine
{
    class ENGINE_SHARED DiffuseMaterial : public Material
    {
    public:
        static DiffuseMaterial *Create(Vector<3> color);

    private:
        DiffuseMaterial(Vector<3> color);
        ~DiffuseMaterial();

    public:
        void Push(bool instanced = false) override;
        void Pop(bool instanced = false) override;

        bool IsOpaque() override;
        TesselationType GetTesselationType() override;

        const char *name() override;
        operator bool() override;

    private:
        Vector<3> color;
        //Shader *instancedShader, *singleShader;
    };
}
