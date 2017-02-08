#include "stdafx.h"
#include "GateGuard.h"

#include "BoxBody.h"

#include "FbxGraphicsObject.h"

namespace TileRPG
{
    GateGuard::GateGuard(Vector<3> position, Matrix<4, 4> orientation)
        : Entity(new GlEngine::BoxBody(-0.2f, 0.2f, -0.2f, 0.2f, -0.2f, 0.2f), position, orientation)
    {
    }
    GateGuard::~GateGuard()
    {
    }

    std::string GateGuard::name()
    {
        return "GateGuard";
    }

    GlEngine::GraphicsObject *GateGuard::CreateGraphicsObject(GlEngine::GraphicsContext&)
    {
        return GlEngine::FbxGraphicsObject::Create("Resources/cylinder.fbx");
    }
}
