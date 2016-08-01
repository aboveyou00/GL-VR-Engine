#include "stdafx.h"
#include "TestSceneFrame.h"

#include "TestMusicObject.h"
#include "PlayerObject.h"
#include "GraphicsObject.h"
#include "CameraGameObject.h"

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

        auto testObject = this->CreateGameObject<PlayerObject>();
		testObject->position = Vector<3>(0, 0, 0);

		auto cameraObject = this->CreateGameObject<GlEngine::CameraGameObject>();
		cameraObject->SetTargetObject(testObject);
		cameraObject->SetLock(GlEngine::CameraLock::RELATIVE_POSITION | GlEngine::CameraLock::RELATIVE_ORIENTATION);
		cameraObject->SetPosition({ 0, 0, -10 });

        this->CreateGameObject<TestMusicObject>("Audio/overworld-start.ogg", "Audio/overworld-main.ogg")->position = Vector<3>(5.f, -2.f, 5.f);
        this->CreateGameObject<TestMusicObject>("Audio/happy-start.ogg", "Audio/happy-main.ogg")->position = Vector<3>(-5.f, 3.f, 2.f);
        this->CreateGameObject<TestMusicObject>("Audio/friendly-start.ogg", "Audio/friendly-main.ogg")->position = Vector<3>(-2.f, -5.f, -4.f);

        return true;
    }
}
