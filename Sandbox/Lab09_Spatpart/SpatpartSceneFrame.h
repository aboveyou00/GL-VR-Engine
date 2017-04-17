#pragma once

#include "Frame.h"
#include "FontRenderer.h"

class SpatpartSceneFrame : public GlEngine::Frame
{
public:
    SpatpartSceneFrame();
    ~SpatpartSceneFrame();

    virtual bool Initialize() override;
    virtual void Tick(float dt) override;

    virtual void UpdateGraphics() override;
    virtual void Render(GlEngine::RenderStage *stage);

    GlEngine::GameObject *flagGobj;
    GlEngine::CameraComponent* cameraComponent;

private:
    static const unsigned TEST_POINT_COUNT = 1;
    Vector<3> testPoints[TEST_POINT_COUNT] = {
        { 1.637f, 1.742f, 0.076f },
        //{ 0.100f, 1.900f, 0.000f },
        //{ 0.891f, 2.298f, 0.076f },
        //{ 0.100f, 2.900f, 0.000f },
        //{ 1.700f, 2.614f, 0.076f }
    };
    //GlEngine::GameObject* raytraceDebugObjects[TEST_POINT_COUNT] = { nullptr, nullptr, nullptr, nullptr, nullptr };
    GlEngine::GameObject* raytraceDebugObjects[TEST_POINT_COUNT] = { nullptr };

    FIG::FontRenderer* renderer;
    std::string renderText;
};
