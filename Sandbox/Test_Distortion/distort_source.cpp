#include "stdafx.h"

std::string distortVertex = R"raw(
#version 430 core

layout(location = 0) in vec3 xyz_position;
layout(location = 1) in vec2 in_uv_coords;

layout(location = 0) out vec2 out_uv_coords;

void main(void) {
    gl_Position = vec4(xyz_position.xyx, 1);
    out_uv_coords = in_uv_coords;
}
)raw";

std::string distortFragment = R"raw(
#version 430 core

layout(location = 0) in vec2 uv_coords;

layout(location = 0) uniform float game_time;
layout(location = 1) uniform sampler2D scene_texture;

layout(location = 0) out vec4 out_color;

void main(void) {
    out_color = texture2D(scene_texture, vec2(1, 1) - uv_coords);
}
)raw";
