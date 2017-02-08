#pragma once

#include "VboGraphicsObject.h"

namespace TileRPG
{
    class WorldEditorTargetGraphicsObject : public GlEngine::VboGraphicsObject
    {
    public:
        WorldEditorTargetGraphicsObject();
        ~WorldEditorTargetGraphicsObject();

        virtual bool Initialize() override;

        virtual std::string name() override;
    };
}
