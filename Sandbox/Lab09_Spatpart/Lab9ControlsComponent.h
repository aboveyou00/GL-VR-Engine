#pragma once
#include "../LabControlsComponent.h"

class Lab9ControlsComponent: public LabControlsComponent
{
public:
    Lab9ControlsComponent();
    ~Lab9ControlsComponent();

    bool displayDebugString;
    bool rayTracingEnabled;

    virtual void HandleEvent(Event &evt);
};
