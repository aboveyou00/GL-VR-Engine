#include "stdafx.h"
#include "OpenGlGraphicsAdapter.h"
#include "OpenGl.h"

namespace GlEngine::Adapters
{
    static unsigned getGlCap(GraphicsCap cap);
    static void setGl(unsigned glCap, bool val);
    static bool getGl(unsigned glCap);

    void OpenGlGraphicsAdapter::ForkCapabilities()
    {
        capabilityStack->push({});
    }
    void OpenGlGraphicsAdapter::PopCapabilities()
    {
        assert(capabilityStack->size() > 0);
        auto &oldCaps = capabilityStack->top();
        for (auto it = oldCaps.begin(); it != oldCaps.end(); it++)
        {
            GraphicsCap cap;
            bool val;
            std::tie(cap, val) = *it;
            setGl(getGlCap(cap), val);
        }
        capabilityStack->pop();
    }
    void OpenGlGraphicsAdapter::SetCapability(GraphicsCap cap, bool enabled)
    {
        assert(capabilityStack->size() != 0);
        auto glCap = getGlCap(cap);

        auto &oldCaps = capabilityStack->top();
        auto found = oldCaps.find(cap);
        if (found == oldCaps.end()) oldCaps[cap] = getGl(glCap);
        setGl(glCap, enabled);
    }
    bool OpenGlGraphicsAdapter::GetCapability(GraphicsCap cap)
    {
        return getGl(getGlCap(cap));
    }

    static unsigned getGlCap(GraphicsCap cap)
    {
        switch (cap)
        {
        case GraphicsCap::DepthTest: return GL_DEPTH_TEST;
        case GraphicsCap::CullFace: return GL_CULL_FACE;
        case GraphicsCap::Blend: return GL_BLEND;
        default: assert(false); return 0;
        }
    }
    static void setGl(unsigned glCap, bool enable)
    {
        if (enable) glEnable(glCap);
        else glDisable(glCap);
        checkForGlError();
    }
    static bool getGl(unsigned glCap)
    {
        auto enabled = glIsEnabled(glCap);
        checkForGlError();
        return enabled;
    }
}
