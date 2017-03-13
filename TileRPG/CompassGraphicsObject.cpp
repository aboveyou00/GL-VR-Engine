#include "stdafx.h"
#include "CompassGraphicsObject.h"
#include "Image2dGraphicsObject.h"
#include "MathUtils.h"

namespace TileRPG
{
    CompassGraphicsObject::CompassGraphicsObject()
        : GlEngine::CompoundGraphicsObject<2>({
              GlEngine::TransformedGraphicsObject { GlEngine::Image2dGraphicsObject::Create("Textures/compass_socket.png"s) },
              GlEngine::TransformedGraphicsObject { GlEngine::Image2dGraphicsObject::Create("Textures/compass.png"s) }
          })
    {
        SetRotation(0deg);
    }
    CompassGraphicsObject::~CompassGraphicsObject()
    {
    }

    void CompassGraphicsObject::SetRotation(float rot)
    {
        (*this)[1].transformation = Matrix<4, 4>::RollMatrix(rot);
    }
}
