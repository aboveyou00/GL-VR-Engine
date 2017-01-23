#pragma once

#include "GameObject.h"
#include "Event.h"

typedef GlEngine::Events::Event Event;
typedef GlEngine::Events::Event Event;

namespace GlEngine
{
    class GraphicsObject;
    class GraphicsContext;
}

class LabControls : public GlEngine::GameObject
{
public:
    LabControls();
    ~LabControls();

    static bool isPaused;
    static bool rotateX;
    static bool rotateY;
    static bool rotateZ;

    virtual void HandleEvent(Event &evt);

    virtual const char *name() override;
    virtual GlEngine::GraphicsObject *CreateGraphicsObject(GlEngine::GraphicsContext &ctx) override;
};
