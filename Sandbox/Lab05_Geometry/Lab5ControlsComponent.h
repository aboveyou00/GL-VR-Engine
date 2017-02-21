#pragma once

#include "../LabControlsComponent.h"

class Lab5ControlsComponent : public LabControlsComponent
{
public:
    Lab5ControlsComponent();
    ~Lab5ControlsComponent();

    static float wireframeThickness;

    virtual void HandleEvent(Event &evt);
};
