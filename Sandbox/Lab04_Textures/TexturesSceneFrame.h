#pragma once
#include "Frame.h"

namespace GlEngine
{
    class GraphicsContext;
}

class TexturesSceneFrame : public GlEngine::Frame
{
public:
    TexturesSceneFrame();
    ~TexturesSceneFrame();

    virtual bool Initialize() override;
};
