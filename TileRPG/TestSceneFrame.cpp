#include "stdafx.h"
#include "TestSceneFrame.h"

#include "TestMusicObject.h"
#include "TestEventObject.h"
#include "GraphicsObject.h"

namespace TileRPG
{
    TestSceneFrame::TestSceneFrame()
    {
    }
    TestSceneFrame::~TestSceneFrame()
    {
    }

    bool TestSceneFrame::Initialize()
    {
        if (!Frame::Initialize()) return false;

        this->CreateGameObject<TestEventObject>()->position = Vector<3>(0, 0, 20.f);

        this->CreateGameObject<TestMusicObject>("Audio\\overworld-start.ogg", "Audio\\overworld-main.ogg")->position = Vector<3>(20.f, 5.f, 2.f);
        this->CreateGameObject<TestMusicObject>("Audio\\happy-start.ogg", "Audio\\happy-main.ogg")->position = Vector<3>(-15.f, 10.f, 2.f);
        this->CreateGameObject<TestMusicObject>("Audio\\friendly-start.ogg", "Audio\\friendly-main.ogg")->position = Vector<3>(-15.f, -10.f, 2.f);

        return true;
    }
}
