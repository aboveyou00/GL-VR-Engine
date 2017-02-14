#include "stdafx.h"

std::string distortVertex = R"raw(
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

std::string distortFragment = R"raw(
#version 430 core

subroutine vec4 DistortionFunction(vec2 xy);

layout(location = 0) in vec2 uv_coords;

layout(location = 0) uniform float game_time;
layout(location = 1) uniform sampler2D scene_texture;
subroutine uniform DistortionFunction in_distortion_fn;

layout(location = 0) out vec4 out_color;

subroutine(DistortionFunction) vec4 SinWave(vec2 xy)
{
    vec2 offset = vec2(sin((xy.y / 100) + game_time) / 25, cos((xy.x / 140) + game_time) / 20);
    return texture2D(scene_texture, uv_coords + offset);
}

void main(void)
{
    out_color = in_distortion_fn(gl_FragCoord.xy);
}
)raw";
