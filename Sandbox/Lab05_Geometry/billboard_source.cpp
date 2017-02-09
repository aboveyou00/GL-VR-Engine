#include "stdafx.h"

std::string billboardVertex = R"raw(
#version 430 core

layout(location = 0) in vec3 xyz_position;

layout(location = 0) uniform mat4 model_matrix;
layout(location = 1) uniform mat4 view_matrix;
layout(location = 2) uniform mat4 projection_matrix;

void main(void) {
    gl_Position = projection_matrix * view_matrix * model_matrix * vec4(xyz_position, 1.f);
}
)raw";

std::string billboardGeometry = R"raw(
#version 430 core

layout(points) in;
layout(triangle_strip, max_vertices = 4) out;

layout(location = 0) out vec2 uv_coords;

void main() {
    gl_Position = gl_in[0].gl_Position + vec4(-.5, -.5, 0, 0);
    uv_coords = vec2(0, 0);
    EmitVertex();

    gl_Position = gl_in[0].gl_Position + vec4(-.5, +.5, 0, 0);
    uv_coords = vec2(0, 1);
    EmitVertex();

    gl_Position = gl_in[0].gl_Position + vec4(+.5, -.5, 0, 0);
    uv_coords = vec2(1, 0);
    EmitVertex();

    gl_Position = gl_in[0].gl_Position + vec4(+.5, +.5, 0, 0);
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
