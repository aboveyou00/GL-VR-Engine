#include "stdafx.h"
#include "TestGameObject.h"

namespace TileRPG
{
    TestGameObject::TestGameObject()
    {
        RequireTick(true);
        timePassed = 0;
    }
    TestGameObject::~TestGameObject()
    {
    }

    bool TestGameObject::Initialize()
    {
        if (!GameObject::Initialize()) return false;

        return true;
    }
    void TestGameObject::Tick(float delta)
    {
        timePassed += delta;
        auto theta = timePassed;
        position = Vector<3> { sin(theta) / 2, cos(theta) / 2, 1 };
    }
}
