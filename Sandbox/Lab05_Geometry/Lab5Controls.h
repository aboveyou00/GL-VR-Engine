#pragma once

#include "../LabControls.h"

class Lab5Controls : public LabControls
{
public:
    Lab5Controls();
    ~Lab5Controls();

    static unsigned wireframeThickness;

    virtual void HandleEvent(Event &evt);

    virtual std::string name() override;
};
