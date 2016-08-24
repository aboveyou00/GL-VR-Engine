#include "stdafx.h"
#include "GateTileEntity.h"

#include "FbxGraphicsObject.h"

namespace TileRPG
{
    GateTileEntity::GateTileEntity(Vector<3> position, Matrix<4, 4> orientation)
        : TileEntity({ 2, 2, 1 }, position, orientation)
    {
    }
    GateTileEntity::~GateTileEntity()
    {
    }

    const char *GateTileEntity::name()
    {
        return "GateTileEntity";
    }

    GlEngine::GraphicsObject *GateTileEntity::CreateGraphicsObject(GlEngine::GraphicsContext&)
    {
        return GlEngine::FbxGraphicsObject::Create("Resources/castle/ac_gate.fbx");
    }
}
