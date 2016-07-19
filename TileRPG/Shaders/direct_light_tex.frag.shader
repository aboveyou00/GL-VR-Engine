

#version 430

layout(location = 0) in vec3 in_light_color;
layout(location = 1) in vec2 in_uv_coords;

//layout(location = 0) uniform mat4 projection_matrix;
//layout(location = 1) uniform mat4 model_view_matrix;
//layout(location = 2) uniform vec3 direct_light_direction;
//layout(location = 3) uniform vec3 direct_light_color;
//layout(location = 4) uniform vec3 ambient_light_color;
layout(location = 5) uniform sampler2D texture_sampler;

layout(location = 0) out vec4 out_color;

void main(void)
{
    vec4 tex_color = texture(texture_sampler, in_uv_coords);
    out_color = tex_color * vec4(in_light_color, 1);
}
