#include "stdafx.h"

std::string hairVertex = R"raw(
#version 430 core

layout(location = 0) in vec3 xyz_position;
layout(location = 1) in vec2 uv_coords;
layout(location = 2) in vec3 in_normal;

layout(location = 0) out vec3 color;
layout(location = 1) out vec4 out_normal;

layout(location = 0) uniform mat4 model_matrix;
layout(location = 1) uniform mat4 view_matrix;

void main(void) {
    color = xyz_position;
    gl_Position = view_matrix * model_matrix * vec4(xyz_position, 1.f);
    out_normal = view_matrix * model_matrix * vec4(in_normal, 0.f);
}
)raw";

std::string hairGeometry = R"raw(
#version 430 core
layout(triangles) in;
layout(triangle_strip, max_vertices = 48) out;

layout(location = 2) uniform mat4 projection_matrix;

layout(location = 0) in vec3 in_color[];
layout(location = 1) in vec4 in_normal[];

layout(location = 0) out vec3 out_color;

void DrawNormal(vec4 position, vec3 normal, vec3 color) 
{
    vec3 i = normalize(vec3(normal.z, 0.0, normal.x));
    vec3 j = normalize(cross(i, normal));

    float size = 0.01;
    float length = 0.3;

    vec3 topleft = -size * i - size * j;
    vec3 topright = size * i - size * j;
    vec3 bottomleft = -size * i + size * j;
    vec3 bottomright = size * i + size * j;

    gl_Position = projection_matrix * (position + vec4(topleft, 0));
    out_color = color;
    EmitVertex();

    gl_Position = projection_matrix * (position + vec4(normal * length, 0.0));
    out_color = color / 2;
    EmitVertex();

    gl_Position = projection_matrix * (position + vec4(topright, 0));
    out_color = color;
    EmitVertex();

    EndPrimitive();

    gl_Position = projection_matrix * (position + vec4(topright, 0));
    out_color = color;
    EmitVertex();

    gl_Position = projection_matrix * (position + vec4(normal * length, 0.0));
    out_color = color / 2;
    EmitVertex();

    gl_Position = projection_matrix * (position + vec4(bottomright, 0));
    out_color = color;
    EmitVertex();

    EndPrimitive();

    gl_Position = projection_matrix * (position + vec4(bottomright, 0));
    out_color = color;
    EmitVertex();

    gl_Position = projection_matrix * (position + vec4(normal * length, 0.0));
    out_color = color / 2;
    EmitVertex();

    gl_Position = projection_matrix * (position + vec4(bottomleft, 0));
    out_color = color;
    EmitVertex();

    EndPrimitive();

    gl_Position = projection_matrix * (position + vec4(bottomleft, 0));
    out_color = color;
    EmitVertex();

    gl_Position = projection_matrix * (position + vec4(normal * length, 0.0));
    out_color = color / 2;
    EmitVertex();

    gl_Position = projection_matrix * (position + vec4(topleft, 0));
    out_color = color;
    EmitVertex();

    EndPrimitive();
}

void main() {
    vec4 mid = (gl_in[0].gl_Position + gl_in[1].gl_Position) / 2.f;
    vec4 centroid_pos = gl_in[2].gl_Position + (mid - gl_in[2].gl_Position) * 2.f / 3.f;

    gl_Position = projection_matrix * gl_in[0].gl_Position;
    out_color = in_color[0];
    EmitVertex();

    gl_Position = projection_matrix * gl_in[1].gl_Position;
    out_color = in_color[1];
    EmitVertex();

    gl_Position = projection_matrix * gl_in[2].gl_Position;
    out_color = in_color[2];
    EmitVertex();

    EndPrimitive();

    vec3 normal = -normalize(cross(gl_in[2].gl_Position.xyz - gl_in[0].gl_Position.xyz, gl_in[1].gl_Position.xyz - gl_in[0].gl_Position.xyz));
    DrawNormal(centroid_pos, normal, vec3(1.0, 0.0, 0.0));

    EndPrimitive();

    for (int n = 0; n < 3; n++)
    {
        DrawNormal(gl_in[n].gl_Position, in_normal[n].xyz, vec3(0.0, 0.0, 1.0));
    }
}
)raw";

std::string hairFragment = R"raw(
#version 430 core

layout(location = 0) in vec3 in_color;

layout(location = 0) out vec4 out_color;

void main(void) {
    out_color = vec4(in_color, 1.f);
}
)raw";