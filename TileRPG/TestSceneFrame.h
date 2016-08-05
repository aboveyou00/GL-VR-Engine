#pragma once

#include "Frame.h"
#include "Space.h"
#include "TileCollisionGroup.h"

namespace TileRPG
{
	class TileCollisionProvider;

    class TestSceneFrame : public GlEngine::Frame
    {
    public:
        TestSceneFrame();
        ~TestSceneFrame();

        bool Initialize() override;
		void Shutdown() override;
		void Tick(float delta) override;

		GlEngine::Space * space;

		TileCollisionProvider * tileCollisionProvider;
		GlEngine::TileCollisionGroup<TileCollisionProvider> * tileCollisionGroup;
    };
}
