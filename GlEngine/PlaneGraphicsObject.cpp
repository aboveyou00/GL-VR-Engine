#include "stdafx.h"
#include "PlaneGraphicsObject.h"

namespace GlEngine
{
    PlaneGraphicsObject::PlaneGraphicsObject(std::string name, Material *mat, Vector<2> size, Vector<2> subdivisions, Vector<2> uvScale)
        : VboGraphicsObject(name), _mat(mat), _size(size), _subdivisions(subdivisions), _uvScale(uvScale)
    {
    }
    PlaneGraphicsObject::~PlaneGraphicsObject()
    {
    }

    bool PlaneGraphicsObject::InitializeAsync()
    {
        if (!VboGraphicsObject::InitializeAsync()) return false;

        SetMaterial(_mat);

        static const float x = -_size[0] / 2, y = 0, z = -_size[1] / 2;
        static const float w = _size[0], h = 0, d = _size[1];
        int idx0, idx1, idx2, idx3;

        //Render face Yp
        auto ww = w / _subdivisions[0];
        auto dd = d / _subdivisions[1];
        auto uvw = _uvScale[0] / _subdivisions[0];
        auto uvd = _uvScale[1] / _subdivisions[1];
        for (size_t q = 0; q < _subdivisions[0]; q++)
        {
            auto tx = x + q * ww;
            auto uvx = q * uvw;

            for (size_t e = 0; e < _subdivisions[1]; e++)
            {
                auto tz = z + e * dd;
                auto uvz = e * uvd;

                idx0 = AddVertex({ tx,      y + h, tz      }, { uvx,       uvz       }, { 0, 1, 0 });
                idx1 = AddVertex({ tx + ww, y + h, tz      }, { uvx + uvw, uvz       }, { 0, 1, 0 });
                idx2 = AddVertex({ tx + ww, y + h, tz + dd }, { uvx + uvw, uvz + uvd }, { 0, 1, 0 });
                idx3 = AddVertex({ tx,      y + h, tz + dd }, { uvx,       uvz + uvd }, { 0, 1, 0 });

                AddTriangle({ idx0, idx1, idx2 });
                AddTriangle({ idx0, idx2, idx3 });
            }
        }

        return true;
    }
}
