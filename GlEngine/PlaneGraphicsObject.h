#pragma once

#include "VboGraphicsObject.h"
#include "PhongMaterial.h"

namespace GlEngine
{
    class ENGINE_SHARED PlaneGraphicsObject : public VboGraphicsObject
    {
    public:
        PlaneGraphicsObject(Material *mat, Vector<2> size = { 1, 1 }, Vector<2> subdivisions = { 1, 1 });
        template <typename... TArgs>
        PlaneGraphicsObject(Vector<2> size, TArgs... args)
            : PlaneGraphicsObject(new PhongMaterial(args...), size)
        {
        }
        template <typename... TArgs>
        PlaneGraphicsObject(Vector<2> size, Vector<2> subdivisions, TArgs... args)
            : PlaneGraphicsObject(new PhongMaterial(args...), size, subdivisions)
        {
        }
        ~PlaneGraphicsObject();

        virtual bool InitializeAsync() override;

        virtual std::string name() override;

    private:
        Material *_mat;
        Vector<2> _size, _subdivisions;
    };
}
