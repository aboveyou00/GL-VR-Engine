#include "stdafx.h"
#include "TestSceneFrame.h"
#include "World.h"

#include "TestMusicObject.h"
#include "PlayerObject.h"
#include "WorldEditorTargetObject.h"
#include "GraphicsObject.h"
#include "CameraGameObject.h"

#include "DiskChunkProvider.h"

#include "Space.h"
#include "BoxBody.h"
#include "TileCollisionGroup.h"
#include "TileCollisionProvider.h"

namespace TileRPG
{
    TestSceneFrame::TestSceneFrame()
    {
    }
    TestSceneFrame::~TestSceneFrame()
    {
		if (tileCollisionProvider == nullptr)
			delete tileCollisionProvider;
		if (tileCollisionGroup == nullptr)
			delete tileCollisionGroup;
    }

    bool TestSceneFrame::Initialize()
    {
        if (!Frame::Initialize()) return false;

		space = new GlEngine::Space();
		auto world = this->CreateGameObject<World>(new DiskChunkProvider("world"));

        auto testObject = this->CreateGameObject<PlayerObject>(world);
        //auto testObject = this->CreateGameObject<WorldEditorTargetObject>(world);
		testObject->position = Vector<3>(0, 0, 0);
		space->Add(testObject);

		auto cameraObject = this->CreateGameObject<GlEngine::CameraGameObject>();
		cameraObject->SetTargetObject(testObject);
		cameraObject->SetLock(GlEngine::CameraLock::RELATIVE_POSITION);
        cameraObject->SetPosition({ 0, -1.5, 0.5 });
        //cameraObject->SetPosition({ 0, -7, 3.5 });

		tileCollisionProvider = new TileCollisionProvider(world);
		tileCollisionGroup = new GlEngine::TileCollisionGroup<TileCollisionProvider>(tileCollisionProvider);
		space->Add(tileCollisionGroup);

        //this->CreateGameObject<TestMusicObject>("Audio/overworld-start.ogg", "Audio/overworld-main.ogg")->position = Vector<3>(3.f, -2.f, 5.f);
        //this->CreateGameObject<TestMusicObject>("Audio/happy-start.ogg", "Audio/happy-main.ogg")->position = Vector<3>(-50.f, 3.f, 2.f);
        //this->CreateGameObject<TestMusicObject>("Audio/friendly-start.ogg", "Audio/friendly-main.ogg")->position = Vector<3>(50.f, -5.f, -4.f);

        return true;
    }

	void TestSceneFrame::Shutdown()
	{
        Frame::Shutdown();
		if (space != nullptr)
			delete space;
	}

	void TestSceneFrame::Tick(float delta)
	{
		if (space != nullptr)
			space->Tick(delta);
		Frame::Tick(delta);
	}
}
