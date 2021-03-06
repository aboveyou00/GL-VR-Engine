#pragma once

#include "Frame.h"
#include "ComponentArray.h"
#include <map>

namespace GlEngine
{
    class Texture;
}
namespace GlEngine::ShaderFactory
{
    class ShaderProp;
}

class GeometrySceneFrame : public GlEngine::Frame
{
public:
    GeometrySceneFrame();
    ~GeometrySceneFrame();

    virtual bool Initialize() override;

private:
    std::map<size_t, GlEngine::ShaderFactory::ShaderProp*> billboardProps, wireframeProps, hairProps, explodeProps;
    GlEngine::ShaderFactory::ShaderSource billboardSource, wireframeSource, hairSource, explodeSource;
    GlEngine::Texture *snowTex;
    Vector<2> snowflakeSize;
};
