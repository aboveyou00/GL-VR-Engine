#include "stdafx.h"
#include "OpenGlGraphicsAdapter.h"

namespace GlEngine::Adapters
{
    OpenGlGraphicsAdapter::OpenGlGraphicsAdapter()
        : capabilityStack(new CapStack())
    {
        capabilityStack->push({});
    }
    OpenGlGraphicsAdapter::~OpenGlGraphicsAdapter()
    {
    }

    OpenGlGraphicsAdapter *OpenGlGraphicsAdapter::_inst = nullptr;
    OpenGlGraphicsAdapter *OpenGlGraphicsAdapter::Instance()
    {
        if (_inst == nullptr) _inst = new OpenGlGraphicsAdapter();
        return _inst;
    }
}
