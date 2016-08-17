

#version 430

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
