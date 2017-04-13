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
    static const unsigned TEST_POINT_COUNT = 5;
    Vector<3> testPoints[TEST_POINT_COUNT] = {
        { 1.737f, 1.642, 0.076f },
        { 0, 1.8f, 0 },
        { .891f, 2.298f, 0.076f },
        { 0, 3, 0 },
        { 1.8f, 2.714f, 0.076f }
    };

    FIG::FontRenderer* renderer;
    std::string renderText;
};
