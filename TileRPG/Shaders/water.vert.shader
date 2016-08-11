

#version 430

layout(location = 0) in vec3 in_vertex_pos;
layout(location = 1) in vec2 in_uv_coords;
layout(location = 2) in vec3 in_normal;

layout(location = 0) out vec3 out_vertex_pos;
layout(location = 1) out vec3 out_normal;
layout(location = 2) out vec2 out_uv_coords;

layout(location = 0) uniform mat4 projection_matrix;
layout(location = 1) uniform mat4 model_view_matrix;
layout(location = 2) uniform vec3 direct_light_direction;
layout(location = 3) uniform vec3 direct_light_color;
layout(location = 4) uniform vec3 ambient_light_color;
layout(location = 5) uniform sampler2D texture_sampler;
layout(location = 6) uniform float in_game_time;

void main(void)
{
    //out_vertex_pos = projection_matrix * model_view_matrix * vec4(in_position, 1);
    out_vertex_pos = in_vertex_pos;
    out_normal = in_normal;
    out_uv_coords = in_uv_coords;

    //float direct_light_amt = clamp(dot(direct_light_direction, in_normal), 0.0, 1.0);
    //vec3 direct_light = direct_light_amt * direct_light_color;
    //out_light_color = ambient_light_color + direct_light;
}
