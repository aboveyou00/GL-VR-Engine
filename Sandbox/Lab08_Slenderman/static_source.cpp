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

float rand(float n) {
    return fract(sin(n) * 43758.5453123);
}
float rand(vec2 n) { 
    return fract(sin(dot(n, vec2(12.9898, 4.1414))) * 43758.5453);
}
float noise(vec2 n) {
    const vec2 d = vec2(0.0, 1.0);
    vec2 b = floor(n), f = smoothstep(vec2(0.0), vec2(1.0), fract(n));
    return mix(mix(rand(b), rand(b + d.yx), f.x), mix(rand(b + d.xy), rand(b + d.yy), f.x), f.y);
}

void main(void)
{
    vec4 base_color = texture2D(scene_texture, in_uv_coords);
    vec2 local_coords = vec2(gl_FragCoord.x + (rand(game_time) * 1000000) / 3, gl_FragCoord.y / 3);
    float noise_value = noise(local_coords);
    out_color = mix(base_color, vec4(noise_value, noise_value, noise_value, 1), static_amount);
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
