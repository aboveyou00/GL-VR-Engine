#pragma once
#include "Struct.h"

namespace GlEngine::ShaderFactory
{
    ///vec3 position; vec3 color; bool attenuation;
    typedef Struct<Vector<3>, Vector<3>, bool> PointLightInfo;
}
