#pragma once

#include "VboGraphicsObject.h"
#include "PhongMaterial.h"

namespace GlEngine
{
    enum class PlaneDirection: uint32_t
    {
        Xp = 0,
        Yp,
        Zp,
        Xm,
        Ym,
        Zm
    };

    class ENGINE_SHARED PlaneGraphicsObject : public VboGraphicsObject
    {
    public:
        PlaneGraphicsObject(std::string name, Material *mat, Vector<2> size = { 1, 1 }, Vector<2> subdivisions = { 1, 1 }, Vector<2> uvScale = { 1, 1 }, PlaneDirection dir = PlaneDirection::Yp);
        ~PlaneGraphicsObject();

        virtual bool InitializeAsync() override;

    private:
        Material *_mat;
        Vector<2> _size, _subdivisions, _uvScale;
        PlaneDirection _dir;
    };
}
