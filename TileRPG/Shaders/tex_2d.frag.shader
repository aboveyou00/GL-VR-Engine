

#version 430

layout(location = 0) in vec2 in_uv_coords;

//layout(location = 0) uniform mat4 projection_matrix;
//layout(location = 1) uniform mat4 model_view_matrix;
layout(location = 2) uniform sampler2D texture_sampler;

layout(location = 0) out vec4 out_color;

void main(void)
{
    out_color = texture(texture_sampler, in_uv_coords);
}
