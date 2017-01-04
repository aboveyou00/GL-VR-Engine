#include "stdafx.h"
#include "TestSceneFrame.h"
#include "World.h"

#include "TestMusicObject.h"
#include "PlayerObject.h"
#include "WorldEditorTargetObject.h"
#include "GraphicsObject.h"
#include "CameraGameObject.h"
#include "PlagueVictim.h"
#include "GateGuard.h"
#include "GateTileEntity.h"
#include "CompassObject.h"

#include "DiskChunkProvider.h"

#include "Space.h"
#include "BoxBody.h"
#include "TileCollisionGroup.h"
#include "TileCollisionProvider.h"
#include "DialogBoxObject.h"
#include "Quest.h"

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

        auto testObject = this->CreateGameObject<WorldEditorTargetObject>(world);
        //auto testObject = this->CreateGameObject<PlayerObject>(world, Vector<3> { 0, 30, -3 });
		space->Add(testObject);

		auto cameraObject = this->CreateGameObject<GlEngine::CameraGameObject>();
		cameraObject->SetTargetObject(testObject);
		cameraObject->SetLock(GlEngine::CameraLock::RELATIVE_POSITION);
        cameraObject->SetPosition({ 0, -7, 3.5 });
        //cameraObject->SetPosition({ 0, -1.5 + 30, 0.5 - 3 });

        auto gate0 = this->CreateGameObject<GateTileEntity>(Vector<3> { -2, 2, -1 });
        space->Add(gate0);

        auto plagueVictim0 = this->CreateGameObject<PlagueVictim>(Vector<3> { 8, 30, -13 });
        auto plagueVictim1 = this->CreateGameObject<PlagueVictim>(Vector<3> { 10, 30, -15 });
        auto plagueVictim2 = this->CreateGameObject<PlagueVictim>(Vector<3> { 10, 30, -11 });
        space->Add(plagueVictim0);
        space->Add(plagueVictim1);
        space->Add(plagueVictim2);

        auto gateGuard0 = this->CreateGameObject<GateGuard>(Vector<3> { 1, 30, 0 });
        auto gateGuard1 = this->CreateGameObject<GateGuard>(Vector<3> { -3, 30, 0 });
        space->Add(gateGuard0);
        space->Add(gateGuard1);

		tileCollisionProvider = new TileCollisionProvider(world);
		tileCollisionGroup = new GlEngine::TileCollisionGroup<TileCollisionProvider>(tileCollisionProvider);
		space->Add(tileCollisionGroup);

        //auto dbo = this->CreateGameObject<DialogBoxObject>();
        //testObject->GetCurrentQuest()->SetDialogBoxObject(dbo);

        //this->CreateGameObject<CompassObject>(Vector<3> { 100, -100, 0 });

        this->CreateGameObject<TestMusicObject>("Audio/overworld-start.ogg", "Audio/overworld-main.ogg")->position = Vector<3>(3.f, -2.f, 5.f);
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
