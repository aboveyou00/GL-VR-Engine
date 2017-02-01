#include "stdafx.h"
#include "FrameBufferCubeGameObject.h"
#include "TextureRenderTarget.h"
#include "GraphicsContext.h"

#include "Engine.h"
#include "GraphicsController.h"

FrameBufferCubeGameObject::FrameBufferCubeGameObject(Vector<3> size)
    : CubeGameObject(static_cast<GlEngine::CubeGraphicsObject*>(nullptr))
{
    RequireUniqueGraphics(true);
    texRenderTarget = new GlEngine::TextureRenderTarget(512, 512);
    _gfxObj = new GlEngine::CubeGraphicsObject(size, texRenderTarget);
    RequireTick(true);
}
FrameBufferCubeGameObject::~FrameBufferCubeGameObject()
{
}

bool FrameBufferCubeGameObject::Initialize()
{
    myCtx = new GlEngine::GraphicsContext(this->frame());
    myCtx->AddRenderTarget(texRenderTarget);
    GlEngine::Engine::GetInstance().GetGlController().AddGraphicsContext(myCtx);

    return CubeGameObject::Initialize();
}

static float totalDelta;
void FrameBufferCubeGameObject::Tick(float delta)
{
    totalDelta += delta;
    texRenderTarget->SetViewMatrix(Matrix<4, 4>::ScaleMatrix(sin(totalDelta) + 2) * Matrix<4, 4>::YawMatrix(totalDelta));
}

GlEngine::GraphicsObject *FrameBufferCubeGameObject::CreateGraphicsObject(GlEngine::GraphicsContext *ctx)
{
    if (ctx == myCtx) return nullptr;
    return GlEngine::CubeGameObject::CreateGraphicsObject(ctx);
}
