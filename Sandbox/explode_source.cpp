#include "stdafx.h"

std::string explodeVertex = R"raw(
#version 430 core

layout(location = 0) in vec3 xyz_position;
layout(location = 1) in vec2 uv_coords;
layout(location = 2) in vec3 in_normal;

layout(location = 0) out vec3 color;
layout(location = 1) out vec4 out_normal;

layout(location = 0) uniform mat4 model_matrix;
layout(location = 1) uniform mat4 view_matrix;
layout(location = 2) uniform mat4 projection_matrix;

void main(void) {
    color = xyz_position;
    gl_Position = view_matrix * model_matrix * vec4(xyz_position, 1.f);
    out_normal = view_matrix * model_matrix * vec4(in_normal, 0.f);
}
)raw";

std::string explodeGeometry = R"raw(
#version 430 core
layout(triangles) in;
layout(triangle_strip, max_vertices = 48) out;

layout(location = 2) uniform mat4 projection_matrix;
layout(location = 7) uniform float gameTime;

layout(location = 0) in vec3 in_color[];
layout(location = 1) in vec4 in_normal[];

layout(location = 0) out vec3 out_color;

void main() {
    vec4 mid = (gl_in[0].gl_Position + gl_in[1].gl_Position) / 2.f;
    vec4 centroid_pos = gl_in[2].gl_Position + (mid - gl_in[2].gl_Position) * 2.f / 3.f;

    vec3 normal = normalize(cross(gl_in[2].gl_Position.xyz - gl_in[0].gl_Position.xyz, gl_in[1].gl_Position.xyz - gl_in[0].gl_Position.xyz));
    vec3 modify = -normal * (sin(gameTime) + 1) * 3;

    gl_Position = projection_matrix * (gl_in[0].gl_Position + vec4(modify, 0));
    out_color = in_color[0];
    EmitVertex();

    gl_Position = projection_matrix * (gl_in[1].gl_Position + vec4(modify, 0));
    out_color = in_color[1];
    EmitVertex();

    gl_Position = projection_matrix * (gl_in[2].gl_Position + vec4(modify, 0));
    out_color = in_color[2];
    EmitVertex();

    EndPrimitive();
}
)raw";

std::string explodeFragment = R"raw(
#version 430 core

layout(location = 0) in vec3 in_color;

layout(location = 0) out vec4 out_color;

void main(void) {
    out_color = vec4(in_color, 1.f);
}
)raw";