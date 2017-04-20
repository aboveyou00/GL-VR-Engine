#pragma once

#include "Frame.h"

class WorldEditorFrame : public GlEngine::Frame
{
public:
    WorldEditorFrame();
    ~WorldEditorFrame();

    virtual bool Initialize() override;
};
