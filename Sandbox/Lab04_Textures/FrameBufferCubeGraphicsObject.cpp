#include "stdafx.h"
#include "FrameBufferCubeGraphicsObject.h"
#include "TextureRenderTarget.h"

#include "Engine.h"
#include "GraphicsController.h"

FrameBufferCubeGraphicsObject::FrameBufferCubeGraphicsObject(std::string name, GlEngine::Material *mat, Vector<3> size)
    : CubeGraphicsObject(name, mat, size)
{
    //_gfxObj = new GlEngine::CubeGraphicsObject(size, texRenderTarget);
}
FrameBufferCubeGraphicsObject::~FrameBufferCubeGraphicsObject()
{
}

bool FrameBufferCubeGraphicsObject::InitializeAsync()
{
    texRenderTarget = new GlEngine::TextureRenderTarget(512, 512);
    texRenderTarget->AddToGraphicsLoop();

    return CubeGraphicsObject::InitializeAsync();
}

static float totalDelta;
void FrameBufferCubeGraphicsObject::Tick(float delta)
{
    totalDelta += delta;
    texRenderTarget->SetViewMatrix(Matrix<4, 4>::ScaleMatrix(sin(totalDelta) + 2) * Matrix<4, 4>::YawMatrix(totalDelta));
}
