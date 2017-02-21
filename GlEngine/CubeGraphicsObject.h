#pragma once

#include "VboGraphicsObject.h"
#include "PhongMaterial.h"

namespace GlEngine
{
    class ENGINE_SHARED CubeGraphicsObject : public VboGraphicsObject
    {
    public:
        CubeGraphicsObject(std::string name, Material *mat, Vector<3> size = { 1, 1, 1 });
        //template <typename... TArgs>
        //CubeGraphicsObject(std::string name, Vector<3> size, TArgs... args)
        //    : CubeGraphicsObject(name, new PhongMaterial(name, args...), size)
        //{
        //}
        ~CubeGraphicsObject();

        virtual bool InitializeAsync() override;

    private:
        Material *_mat;
        Vector<3> _size;
    };
}
