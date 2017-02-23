#pragma once

#include "../LabControlsComponent.h"

class Lab3ControlsComponent : public LabControlsComponent
{
public:
    Lab3ControlsComponent();
    ~Lab3ControlsComponent();

    static int celShadingSteps;
    static float spotlightCutoffAngle;
    static float spotlightAttenuation;

    virtual void HandleEvent(Event &evt);

private:
    static const unsigned ATTENTUATION_VALUE_COUNT = 4;
    static float attenuationValues[ATTENTUATION_VALUE_COUNT];
    unsigned attenuationIdx;
};
