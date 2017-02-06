#pragma once
#include "Frame.h"

namespace GlEngine
{
    class GraphicsContext;
}

class G2DOverlaySceneFrame : public GlEngine::Frame
{
public:
    G2DOverlaySceneFrame();
    ~G2DOverlaySceneFrame();

    virtual bool Initialize() override;
};
