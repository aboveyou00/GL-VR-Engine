#pragma once

#include "VboGraphicsObject.h"
#include "PhongMaterial.h"

namespace GlEngine
{
    class ENGINE_SHARED PlaneGraphicsObject : public VboGraphicsObject
    {
    public:
        PlaneGraphicsObject(std::string name, Material *mat, Vector<2> size = { 1, 1 }, Vector<2> subdivisions = { 1, 1 }, Vector<2> uvScale = { 1, 1 });
        template <typename... TArgs>
        PlaneGraphicsObject(std::string name, Vector<2> size, TArgs... args)
            : PlaneGraphicsObject(name, new PhongMaterial(args...), size)
        {
        }
        template <typename... TArgs>
        PlaneGraphicsObject(std::string name, Vector<2> size, Vector<2> subdivisions, TArgs... args)
            : PlaneGraphicsObject(name, new PhongMaterial(args...), size, subdivisions)
        {
        }
        template <typename... TArgs>
        PlaneGraphicsObject(std::string name, Vector<2> size, Vector<2> subdivisions, Vector<2> uvScale, TArgs... args)
            : PlaneGraphicsObject(name, new PhongMaterial(args...), size, subdivisions, uvScale)
        {
        }
        ~PlaneGraphicsObject();

        virtual bool InitializeAsync() override;

    private:
        Material *_mat;
        Vector<2> _size, _subdivisions, _uvScale;
    };
}
