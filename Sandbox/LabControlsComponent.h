#pragma once

#include "GameComponent.h"
#include "Event.h"
#include "PointLightSource.h"
#include <map>

typedef GlEngine::Events::Event Event;
typedef GlEngine::Events::Event Event;

namespace GlEngine
{
    class GraphicsObject;
    class GraphicsContext;
}

class LabControlsComponent : public GlEngine::GameComponent
{
public:
    LabControlsComponent();
    ~LabControlsComponent();

    static bool isPaused;
    static bool rotateX;
    static bool rotateY;
    static bool rotateZ;

    virtual void Tick(float delta);

    virtual void HandleEvent(Event &evt);

    void SetControllingLight(GlEngine::PointLightSource *light);

private:
    std::map<unsigned, bool> keysDown;
    GlEngine::PointLightSource *controllingLight;
    float movementSpeed;
};
