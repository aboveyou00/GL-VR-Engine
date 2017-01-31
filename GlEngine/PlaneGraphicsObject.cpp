#include "stdafx.h"
#include "PlaneGraphicsObject.h"

namespace GlEngine
{
    PlaneGraphicsObject::PlaneGraphicsObject(Material *mat, Vector<2> size, Vector<2> subdivisions)
        : _mat(mat), _size(size), _subdivisions(subdivisions)
    {
    }
    PlaneGraphicsObject::~PlaneGraphicsObject()
    {
    }

    bool PlaneGraphicsObject::Initialize()
    {
        SetMaterial(_mat);

        static const float x = -_size[0] / 2, y = 0, z = -_size[1] / 2;
        static const float w = _size[0], h = 0, d = _size[1];
        int idx0, idx1, idx2, idx3;

        ////Render face Xm
        //idx0 = AddVertex({ x, y,     z     }, { 0, 0 }, { -1, 0, 0 });
        //idx1 = AddVertex({ x, y + h, z     }, { 1, 0 }, { -1, 0, 0 });
        //idx2 = AddVertex({ x, y + h, z + d }, { 1, 1 }, { -1, 0, 0 });
        //idx3 = AddVertex({ x, y,     z + d }, { 0, 1 }, { -1, 0, 0 });

        //AddTriangle({ idx0, idx1, idx2 });
        //AddTriangle({ idx0, idx2, idx3 });

        ////Render face Xp
        //idx0 = AddVertex({ x + w, y,     z     }, { 0, 0 }, { 1, 0, 0 });
        //idx1 = AddVertex({ x + w, y + h, z     }, { 1, 0 }, { 1, 0, 0 });
        //idx2 = AddVertex({ x + w, y + h, z + d }, { 1, 1 }, { 1, 0, 0 });
        //idx3 = AddVertex({ x + w, y,     z + d }, { 0, 1 }, { 1, 0, 0 });

        //AddTriangle({ idx0, idx2, idx1 });
        //AddTriangle({ idx0, idx3, idx2 });

        ////Render face Ym
        //idx0 = AddVertex({ x,     y, z     }, { 0, 0 }, { 0, -1, 0 });
        //idx1 = AddVertex({ x + w, y, z     }, { 1, 0 }, { 0, -1, 0 });
        //idx2 = AddVertex({ x + w, y, z + d }, { 1, 1 }, { 0, -1, 0 });
        //idx3 = AddVertex({ x,     y, z + d }, { 0, 1 }, { 0, -1, 0 });

        //AddTriangle({ idx0, idx2, idx1 });
        //AddTriangle({ idx0, idx3, idx2 });

        //Render face Yp
        auto ww = w / _subdivisions[0];
        auto dd = d / _subdivisions[1];
        auto uvw = 1.f / _subdivisions[0];
        auto uvd = 1.f / _subdivisions[1];
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

        ////Render face Zm
        //idx0 = AddVertex({ x,     y,     z }, { 0, 0 }, { 0, 0, -1 });
        //idx1 = AddVertex({ x + w, y,     z }, { 1, 0 }, { 0, 0, -1 });
        //idx2 = AddVertex({ x + w, y + h, z }, { 1, 1 }, { 0, 0, -1 });
        //idx3 = AddVertex({ x,     y + h, z }, { 0, 1 }, { 0, 0, -1 });

        //AddTriangle({ idx0, idx1, idx2 });
        //AddTriangle({ idx0, idx2, idx3 });

        ////Render face Zp
        //idx0 = AddVertex({ x,     y,     z + d }, { 0, 0 }, { 0, 0, 1 });
        //idx1 = AddVertex({ x + w, y,     z + d }, { 1, 0 }, { 0, 0, 1 });
        //idx2 = AddVertex({ x + w, y + h, z + d }, { 1, 1 }, { 0, 0, 1 });
        //idx3 = AddVertex({ x,     y + h, z + d }, { 0, 1 }, { 0, 0, 1 });

        //AddTriangle({ idx0, idx2, idx1 });
        //AddTriangle({ idx0, idx3, idx2 });

        return true;
    }
}
