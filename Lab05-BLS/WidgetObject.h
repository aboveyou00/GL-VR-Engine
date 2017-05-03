#pragma once

#include "VboGraphicsObject.h"

class WidgetObject : public GlEngine::VboGraphicsObject
{
public:
    WidgetObject(std::string name);
    ~WidgetObject();

    bool InitializeAsync() override;
};
