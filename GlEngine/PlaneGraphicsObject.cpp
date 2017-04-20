#include "stdafx.h"
#include "PlaneGraphicsObject.h"

namespace GlEngine
{
    PlaneGraphicsObject::PlaneGraphicsObject(std::string name, Material *mat, Vector<2> size, Vector<2> subdivisions, Vector<2> uvScale, PlaneDirection dir)
        : VboGraphicsObject(name), _mat(mat), _size(size), _subdivisions(subdivisions), _uvScale(uvScale), _dir(dir)
    {
    }
    PlaneGraphicsObject::~PlaneGraphicsObject()
    {
    }

    bool PlaneGraphicsObject::InitializeAsync()
    {
        if (!VboGraphicsObject::InitializeAsync()) return false;

        SetMaterial(_mat);

        const float x = -_size[0] / 2, y = 0, z = -_size[1] / 2;
        const float w = _size[0], h = 0, d = _size[1];
        int idx0 = 0, idx1 = 0, idx2 = 0, idx3 = 0;

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
                
                if (_dir == PlaneDirection::Xp || _dir == PlaneDirection::Xm)
                {
                    auto normal = _dir == PlaneDirection::Xp ? -1 : 1;
                    idx0 = AddVertex({ y + h, tx,      tz      }, { uvx,       uvz       }, { normal, 0, 0 });
                    idx1 = AddVertex({ y + h, tx + ww, tz      }, { uvx + uvw, uvz       }, { normal, 0, 0 });
                    idx2 = AddVertex({ y + h, tx + ww, tz + dd }, { uvx + uvw, uvz + uvd }, { normal, 0, 0 });
                    idx3 = AddVertex({ y + h, tx,      tz + dd }, { uvx,       uvz + uvd }, { normal, 0, 0 });
                }
                else if (_dir == PlaneDirection::Yp || _dir == PlaneDirection::Ym)
                {
                    auto normal = _dir == PlaneDirection::Yp ? -1 : 1;
                    idx0 = AddVertex({ tx,      y + h, tz      }, { uvx,       uvz       }, { 0, normal, 0 });
                    idx1 = AddVertex({ tx + ww, y + h, tz      }, { uvx + uvw, uvz       }, { 0, normal, 0 });
                    idx2 = AddVertex({ tx + ww, y + h, tz + dd }, { uvx + uvw, uvz + uvd }, { 0, normal, 0 });
                    idx3 = AddVertex({ tx,      y + h, tz + dd }, { uvx,       uvz + uvd }, { 0, normal, 0 });
                }
                else if (_dir == PlaneDirection::Zp || _dir == PlaneDirection::Zm)
                {
                    auto normal = _dir == PlaneDirection::Zp ? -1 : 1;
                    idx0 = AddVertex({ tx,      tz,      y + h }, { uvx,       uvz       }, { 0, 0, normal });
                    idx1 = AddVertex({ tx + ww, tz,      y + h }, { uvx + uvw, uvz       }, { 0, 0, normal });
                    idx2 = AddVertex({ tx + ww, tz + dd, y + h }, { uvx + uvw, uvz + uvd }, { 0, 0, normal });
                    idx3 = AddVertex({ tx,      tz + dd, y + h }, { uvx,       uvz + uvd }, { 0, 0, normal });
                }
                else assert(false);

                AddTriangle({ idx0, idx1, idx2 });
                AddTriangle({ idx0, idx2, idx3 });
            }
        }

        return true;
    }
}
