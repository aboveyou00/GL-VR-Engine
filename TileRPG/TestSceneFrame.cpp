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

        this->CreateGameObject<TestEventObject>();
        this->CreateGameObject<TestMusicObject>();

        return true;
    }
}
