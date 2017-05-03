#pragma once

#include "Frame.h"

class Lab05Frame : public GlEngine::Frame
{
public:
    Lab05Frame();
    ~Lab05Frame();

    virtual bool Initialize() override;
};
