

#version 430

layout(location = 0) in vec3 in_position;
layout(location = 1) in vec2 in_uv_coords;

layout(location = 0) uniform mat4 projection_matrix;
layout(location = 1) uniform mat4 model_view_matrix;
//layout(location = 2) uniform sampler2D texture_sampler;

layout(location = 0) out vec2 out_uv_coords;

void main(void)
{
    gl_Position = projection_matrix * model_view_matrix * vec4(in_position, 1);
    out_uv_coords = in_uv_coords;
}
