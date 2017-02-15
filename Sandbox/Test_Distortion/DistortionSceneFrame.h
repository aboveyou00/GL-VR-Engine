#pragma once

#include "Subroutine.h"
#include "Frame.h"
#include "ComponentArray.h"
#include <map>

namespace GlEngine
{
    class TextureRenderTarget;
    class GraphicsContext;
}
namespace GlEngine::Events
{
    class Event;
}
namespace GlEngine::ShaderFactory
{
    class ShaderProp;
}

class DistortionSceneFrame : public GlEngine::Frame
{
public:
    DistortionSceneFrame();
    ~DistortionSceneFrame();

    virtual bool Initialize() override;
    virtual void Tick(float delta) override;
    virtual void Shutdown() override;

    virtual void HandleEvent(GlEngine::Events::Event &evt);

private:
    std::map<size_t, GlEngine::ShaderFactory::ShaderProp*> props;
    GlEngine::ShaderFactory::ShaderSource distortSource;
    
    static const unsigned SR_COUNT = 6;
    GlEngine::ShaderFactory::Subroutine *subroutines[SR_COUNT] = {
        new GlEngine::ShaderFactory::Subroutine("PassThrough"),
        new GlEngine::ShaderFactory::Subroutine("SinWave"),
        new GlEngine::ShaderFactory::Subroutine("Convolution"),
        new GlEngine::ShaderFactory::Subroutine("EdgeConvolution"),
        new GlEngine::ShaderFactory::Subroutine("Outline"),
        new GlEngine::ShaderFactory::Subroutine("MedianConvolution")
    };
    GlEngine::ShaderFactory::Subroutine *currentSubroutine;

    float a = 1.0f;

    static const size_t KERNEL_SIZE = 5;
    static const size_t KERNEL_COUNT = 5;

    float convolutionKernels[KERNEL_COUNT][KERNEL_SIZE * KERNEL_SIZE] = {
        { 0.003765f, 0.015019f, 0.023792f, 0.015019f, 0.003765f,
          0.015019f, 0.059912f, 0.094907f, 0.059912f, 0.015019f,
          0.023792f, 0.094907f, 0.150342f, 0.094907f, 0.023792f,
          0.015019f, 0.059912f, 0.094907f, 0.059912f, 0.015019f,
          0.003765f, 0.015019f, 0.023792f, 0.015019f, 0.003765f },
        
        { 1.f / 25, 1.f / 25, 1.f / 25, 1.f / 25, 1.f / 25,
          1.f / 25, 1.f / 25, 1.f / 25, 1.f / 25, 1.f / 25,
          1.f / 25, 1.f / 25, 1.f / 25, 1.f / 25, 1.f / 25,
          1.f / 25, 1.f / 25, 1.f / 25, 1.f / 25, 1.f / 25,
          1.f / 25, 1.f / 25, 1.f / 25, 1.f / 25, 1.f / 25 },

        { 0, 0,      0,           0,      0,
          0, -a/9.f, -a/9.f,      -a/9.f, 0,
          0, -a/9.f, 1+(8*a/9.f), -a/9.f, 0,
          0, -a/9.f, -a/9.f,      -a/9.f, 0,
          0, 0,      0,           0,      0 },

        { 0, 0,     0,     0,     0,
          0, 0,     -.25f, 0,     0,
          0, -.25f, 1,     -.25f, 0,
          0, 0,     -.25f, 0,     0,
          0, 0,     0,     0,     0 },

        { 1, 1, 1, 1, 1,
          1, 1, 1, 1, 1,
          1, 1, 1, 1, 1,
          1, 1, 1, 1, 1,
          1, 1, 1, 1, 1 }
    };
    float * currentConvolutionKernel;

    int pair_index;
    static const unsigned PAIR_COUNT = 8;
    size_t subroutineKernelPairs[PAIR_COUNT * 2]{
        0, 0,
        1, 0,
        2, 0,
        2, 1,
        2, 2,
        3, 3,
        4, 3,
        4, 5
    };

    GlEngine::GraphicsContext *myCtx;
    GlEngine::Frame *renderedFrame;
    GlEngine::TextureRenderTarget *sceneTex;

    void RefreshPair();
};
