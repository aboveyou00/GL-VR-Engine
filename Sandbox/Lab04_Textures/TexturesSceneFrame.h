#pragma once
#include "Frame.h"

class TexturesSceneFrame : public GlEngine::Frame
{
public:
    TexturesSceneFrame();
    ~TexturesSceneFrame();

    virtual bool Initialize() override;
};
