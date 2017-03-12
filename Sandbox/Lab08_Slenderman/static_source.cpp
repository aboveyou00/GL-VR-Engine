#include "stdafx.h"
#include <map>
#include "ComponentArray.h"
#include "Property.h"

GlEngine::ShaderFactory::Property<float> prop_StaticAmount("static_amount");

std::string staticVertex = R"raw(
#version 430 core

layout(location = 0) in vec3 xyz_position;
layout(location = 1) in vec2 in_uv_coords;

layout(location = 0) out vec2 out_uv_coords;

void main(void)
{
    gl_Position = vec4(xyz_position.xyx, 1);
    out_uv_coords = in_uv_coords;
}
)raw";

std::string staticFragment = R"raw(
#version 430 core

layout(location = 0) in vec2 in_uv_coords;

layout(location = 0) uniform float game_time;
layout(location = 1) uniform vec2 screen_dimensions;
layout(location = 2) uniform sampler2D scene_texture;
layout(location = 3) uniform float static_amount;

layout(location = 0) out vec4 out_color;

void main(void)
{
    out_color = texture2D(scene_texture, in_uv_coords);
}
)raw";

std::map<unsigned, GlEngine::ShaderFactory::ShaderProp*> staticProps = {
    { 0, &GlEngine::ShaderFactory::prop_GameTime },
    { 1, &GlEngine::ShaderFactory::prop_ScreenDimensions },
    { 2, &GlEngine::ShaderFactory::prop_Texture },
    { 3, &prop_StaticAmount }
};

GlEngine::ShaderFactory::ShaderSource staticSource = {
    &staticVertex,
    &staticFragment
};
