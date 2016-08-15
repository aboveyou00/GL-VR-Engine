#pragma once

#include "VboGraphicsObject.h"

namespace TileRPG
{
    class WorldEditorTargetGraphicsObject : public GlEngine::VboGraphicsObject<>
    {
    public:
        WorldEditorTargetGraphicsObject();
        ~WorldEditorTargetGraphicsObject();

        bool Initialize() override;

        virtual const char *name() override;
    };
}
