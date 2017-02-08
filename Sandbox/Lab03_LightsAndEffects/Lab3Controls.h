#pragma once

#include "../LabControls.h"

class Lab3Controls : public LabControls
{
public:
    Lab3Controls();
    ~Lab3Controls();

    static unsigned celShadingSteps;
    static float spotlightCutoffAngle;
    static float spotlightAttenuation;

    virtual void HandleEvent(Event &evt);

    virtual std::string name() override;

private:
    static const unsigned ATTENTUATION_VALUE_COUNT = 4;
    static float attenuationValues[ATTENTUATION_VALUE_COUNT];
    unsigned attenuationIdx;
};
