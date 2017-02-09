#include "stdafx.h"

std::string billboardVertex = R"raw(
#version 430 core

layout(location = 0) in vec3 xyz_position;
layout(location = 1) in float billboard_time_offset;
layout(location = 2) in float billboard_speed;

layout(location = 0) uniform mat4 model_matrix;
layout(location = 1) uniform mat4 view_matrix;
layout(location = 2) uniform mat4 projection_matrix;
layout(location = 7) uniform float game_time;

void main(void) {
    float relative_game_time = (game_time * billboard_speed) + billboard_time_offset;
    vec4 pos = vec4(
        xyz_position.x * 30 + sin(relative_game_time * 4),
        xyz_position.y * 30 - (relative_game_time * 8),
        xyz_position.z * 30 + (game_time * 1.5),
        1
    );
    pos = view_matrix * model_matrix * pos;
    pos = vec4(mod(pos.x, 60)-30, mod(pos.y, 60)-30, mod(pos.z, 60)-30, 1);
    gl_Position = projection_matrix * pos;
}
)raw";

std::string billboardGeometry = R"raw(
#version 430 core

layout(points) in;
layout(triangle_strip, max_vertices = 4) out;

layout(location = 3) uniform vec2 screen_size;
layout(location = 6) uniform vec2 billboard_size;

layout(location = 0) out vec2 uv_coords;

void main() {
    vec4 pos = gl_in[0].gl_Position;
    float wh = (billboard_size[0] / screen_size[0]) * 5;
    float hh = (billboard_size[1] / screen_size[1]) * 5;

    gl_Position = pos + vec4(-wh, -hh, 0, 0);
    uv_coords = vec2(0, 0);
    EmitVertex();

    gl_Position = pos + vec4(-wh, +hh, 0, 0);
    uv_coords = vec2(0, 1);
    EmitVertex();

    gl_Position = pos + vec4(+wh, -hh, 0, 0);
    uv_coords = vec2(1, 0);
    EmitVertex();

    gl_Position = pos + vec4(+wh, +hh, 0, 0);
    uv_coords = vec2(1, 1);
    EmitVertex();

    EndPrimitive();
}
)raw";

std::string billboardFragment = R"raw(
#version 430 core

layout(location = 0) in vec2 uv_coords;

layout(location = 5) uniform sampler2D billboard_texture;

layout(location = 0) out vec4 out_color;

void main(void) {
    out_color = texture2D(billboard_texture, uv_coords);
    if (out_color.a == 0) discard;
}
)raw";
