#include "stdafx.h"

std::string wavesVertex = R"raw(
#version 430 core

layout(location = 0) in vec3 in_vertex_pos;
layout(location = 1) in vec2 in_uv_coords;
layout(location = 2) in vec3 in_normal;

layout(location = 0) out vec3 out_vertex_pos;
layout(location = 1) out vec3 out_normal;
layout(location = 2) out vec2 out_uv_coords;

//layout(location = 0) uniform mat4 projection_matrix;
//layout(location = 1) uniform mat4 model_view_matrix;
//layout(location = 2) uniform vec3 direct_light_direction;
//layout(location = 3) uniform vec3 direct_light_color;
//layout(location = 4) uniform vec3 ambient_light_color;
//layout(location = 5) uniform sampler2D texture_sampler;
layout(location = 6) uniform float in_game_time;

void main(void)
{
    out_vertex_pos = in_vertex_pos;
    out_normal = in_normal;

    float igt = in_game_time / 3.14159 / 4 / 4;
    out_uv_coords = vec2(in_uv_coords.x - igt, in_uv_coords.y - igt);
}
)raw";

std::string wavesTessc = R"raw(
#version 430 core

layout(vertices = 3) out;

layout(location = 0) in vec3 in_vertex_pos[];
layout(location = 1) in vec3 in_normal[];
layout(location = 2) in vec2 in_uv_coords[];

layout(location = 0) out vec3 out_vertex_pos[];
layout(location = 1) out vec3 out_normal[];
layout(location = 2) out vec2 out_uv_coords[];

//layout(location = 0) uniform mat4 projection_matrix;
layout(location = 1) uniform mat4 model_view_matrix;
//layout(location = 2) uniform vec3 direct_light_direction;
//layout(location = 3) uniform vec3 direct_light_color;
//layout(location = 4) uniform vec3 ambient_light_color;
//layout(location = 5) uniform sampler2D texture_sampler;
//layout(location = 6) uniform float in_game_time;

#define ID gl_InvocationID

void main(void)
{
    out_vertex_pos[ID] = in_vertex_pos[ID];
    out_normal[ID] = in_normal[ID];
    out_uv_coords[ID] = in_uv_coords[ID];

    if (ID == 0)
    {
        vec4 vertex_pos = model_view_matrix * vec4(in_vertex_pos[ID], 1);
        int tessLevel = int(clamp(3 + (vertex_pos.z * .5 + 3), 1, 6));
        gl_TessLevelInner[0] = tessLevel;
        gl_TessLevelOuter[0] = gl_TessLevelOuter[1] = gl_TessLevelOuter[2] = tessLevel;
    }
}
)raw";

std::string wavesTesse = R"raw(
#version 430 core

layout(triangles, equal_spacing, ccw) in;

layout(location = 0) in vec3 in_vertex_pos[];
layout(location = 1) in vec3 in_normal[];
layout(location = 2) in vec2 in_uv_coords[];

layout(location = 0) out vec3 out_light_color;
layout(location = 1) out vec2 out_uv_coords;

layout(location = 0) uniform mat4 projection_matrix;
layout(location = 1) uniform mat4 model_view_matrix;
layout(location = 2) uniform vec3 direct_light_direction;
layout(location = 3) uniform vec3 direct_light_color;
layout(location = 4) uniform vec3 ambient_light_color;
//layout(location = 5) uniform sampler2D texture_sampler;
layout(location = 6) uniform float in_game_time;

float water_wave(vec2 xz)
{
    float xcomp = (xz.x - in_game_time) * 2;
    float ycomp = (xz.y - in_game_time) * 2;
    return .1 * sin(xcomp + ycomp);
}
vec2 derivative_water_wave(vec2 xz)
{
    return vec2(
        water_wave(vec2(xz.x - .1, xz.y)) - water_wave(vec2(xz.x + .1, xz.y)),
        water_wave(vec2(xz.x, xz.y - .1)) - water_wave(vec2(xz.x, xz.y + .1))
    ) * 8;
}

void main(void)
{
    vec3 p0 = gl_TessCoord.x * in_vertex_pos[0];
    vec3 p1 = gl_TessCoord.y * in_vertex_pos[1];
    vec3 p2 = gl_TessCoord.z * in_vertex_pos[2];
    vec3 local_vertex_pos = p0 + p1 + p2;
    local_vertex_pos.y += water_wave(local_vertex_pos.xz);

    vec3 n0 = gl_TessCoord.x * in_normal[0];
    vec3 n1 = gl_TessCoord.y * in_normal[1];
    vec3 n2 = gl_TessCoord.z * in_normal[2];
    vec3 normal = n0 + n1 + n2;
    normal.xz += derivative_water_wave(local_vertex_pos.xz);
    normal = normalize(normal);

    float direct_light_amt = clamp(dot(direct_light_direction, normal), 0.0, 1.0);
    vec3 direct_light = direct_light_amt * direct_light_color;
    out_light_color = ambient_light_color + direct_light;

    vec2 uv0 = gl_TessCoord.x * in_uv_coords[0];
    vec2 uv1 = gl_TessCoord.y * in_uv_coords[1];
    vec2 uv2 = gl_TessCoord.z * in_uv_coords[2];
    out_uv_coords = uv0 + uv1 + uv2;

    gl_Position = projection_matrix * model_view_matrix * vec4(local_vertex_pos, 1);
}
)raw";

std::string wavesFragment = R"raw(
#version 430 core

layout(location = 0) in vec3 in_light_color;
layout(location = 1) in vec2 in_uv_coords;

layout(location = 0) out vec4 out_color;

//layout(location = 0) uniform mat4 projection_matrix;
//layout(location = 1) uniform mat4 model_view_matrix;
//layout(location = 2) uniform vec3 direct_light_direction;
//layout(location = 3) uniform vec3 direct_light_color;
//layout(location = 4) uniform vec3 ambient_light_color;
layout(location = 5) uniform sampler2D texture_sampler;
//layout(location = 6) uniform float in_game_time;

void main(void)
{
    vec4 tex_color = texture(texture_sampler, in_uv_coords);
    vec4 direct_color = tex_color * vec4(in_light_color, 1);

    const vec4 fog_color = vec4(0.0, 0.0, 0.0, 1.0);

    float dist = gl_FragCoord.z / gl_FragCoord.w;
    float fog_amt = clamp(sqrt(dist) / 6, 0.0, 1.0);
    out_color = mix(direct_color, fog_color, fog_amt);
}
)raw";
