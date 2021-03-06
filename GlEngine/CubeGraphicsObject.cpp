#include "stdafx.h"
#include "CubeGraphicsObject.h"

namespace GlEngine
{
    CubeGraphicsObject::CubeGraphicsObject(std::string name, Material *mat, Vector<3> size)
        : VboGraphicsObject(name), _mat(mat), _size(size)
    {
    }
    CubeGraphicsObject::~CubeGraphicsObject()
    {
    }

    bool CubeGraphicsObject::InitializeAsync()
    {
        if (!GraphicsObject::InitializeAsync()) return false;

        SetMaterial(_mat);

        static const float x = -_size[0] / 2, y = -_size[1] / 2, z = -_size[2] / 2;
        static const float w = _size[0], h = _size[1], d = _size[2];
        int idx0, idx1, idx2, idx3;

        //Render face Xm
        idx0 = AddVertex({ x, y,     z     }, { 0, 0 }, { -1, 0, 0 });
        idx1 = AddVertex({ x, y + h, z     }, { 1, 0 }, { -1, 0, 0 });
        idx2 = AddVertex({ x, y + h, z + d }, { 1, 1 }, { -1, 0, 0 });
        idx3 = AddVertex({ x, y,     z + d }, { 0, 1 }, { -1, 0, 0 });

        AddTriangle({ idx0, idx1, idx2 });
        AddTriangle({ idx0, idx2, idx3 });

        //Render face Xp
        idx0 = AddVertex({ x + w, y,     z     }, { 0, 0 }, { 1, 0, 0 });
        idx1 = AddVertex({ x + w, y + h, z     }, { 1, 0 }, { 1, 0, 0 });
        idx2 = AddVertex({ x + w, y + h, z + d }, { 1, 1 }, { 1, 0, 0 });
        idx3 = AddVertex({ x + w, y,     z + d }, { 0, 1 }, { 1, 0, 0 });

        AddTriangle({ idx0, idx2, idx1 });
        AddTriangle({ idx0, idx3, idx2 });

        //Render face Ym
        idx0 = AddVertex({ x,     y, z     }, { 0, 0 }, { 0, -1, 0 });
        idx1 = AddVertex({ x + w, y, z     }, { 1, 0 }, { 0, -1, 0 });
        idx2 = AddVertex({ x + w, y, z + d }, { 1, 1 }, { 0, -1, 0 });
        idx3 = AddVertex({ x,     y, z + d }, { 0, 1 }, { 0, -1, 0 });

        AddTriangle({ idx0, idx2, idx1 });
        AddTriangle({ idx0, idx3, idx2 });

        //Render face Yp
        idx0 = AddVertex({ x,     y + h, z     }, { 0, 0 }, { 0, 1, 0 });
        idx1 = AddVertex({ x + w, y + h, z     }, { 1, 0 }, { 0, 1, 0 });
        idx2 = AddVertex({ x + w, y + h, z + d }, { 1, 1 }, { 0, 1, 0 });
        idx3 = AddVertex({ x,     y + h, z + d }, { 0, 1 }, { 0, 1, 0 });

        AddTriangle({ idx0, idx1, idx2 });
        AddTriangle({ idx0, idx2, idx3 });

        //Render face Zm
        idx0 = AddVertex({ x,     y,     z }, { 0, 0 }, { 0, 0, -1 });
        idx1 = AddVertex({ x + w, y,     z }, { 1, 0 }, { 0, 0, -1 });
        idx2 = AddVertex({ x + w, y + h, z }, { 1, 1 }, { 0, 0, -1 });
        idx3 = AddVertex({ x,     y + h, z }, { 0, 1 }, { 0, 0, -1 });

        AddTriangle({ idx0, idx1, idx2 });
        AddTriangle({ idx0, idx2, idx3 });

        //Render face Zp
        idx0 = AddVertex({ x,     y,     z + d }, { 0, 0 }, { 0, 0, 1 });
        idx1 = AddVertex({ x + w, y,     z + d }, { 1, 0 }, { 0, 0, 1 });
        idx2 = AddVertex({ x + w, y + h, z + d }, { 1, 1 }, { 0, 0, 1 });
        idx3 = AddVertex({ x,     y + h, z + d }, { 0, 1 }, { 0, 0, 1 });

        AddTriangle({ idx0, idx2, idx1 });
        AddTriangle({ idx0, idx3, idx2 });

        return true;
    }
}
