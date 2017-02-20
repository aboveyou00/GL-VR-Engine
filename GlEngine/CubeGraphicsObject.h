#pragma once

#include "VboGraphicsObject.h"
#include "PhongMaterial.h"

namespace GlEngine
{
    class ENGINE_SHARED CubeGraphicsObject : public VboGraphicsObject
    {
    public:
        CubeGraphicsObject(Material *mat, Vector<3> size = { 1, 1, 1 });
        template <typename... TArgs>
        CubeGraphicsObject(Vector<3> size, TArgs... args)
            : CubeGraphicsObject(new PhongMaterial(args...), size)
        {
        }
        ~CubeGraphicsObject();

        virtual bool InitializeAsync() override;

        virtual std::string name() override;

    private:
        Material *_mat;
        Vector<3> _size;
    };
}
