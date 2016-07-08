#pragma once

#include "Frame.h"

namespace TileRPG
{
    class TestSceneFrame : public GlEngine::Frame
    {
    public:
        TestSceneFrame();
        ~TestSceneFrame();

        bool Initialize() override;
    };
}
