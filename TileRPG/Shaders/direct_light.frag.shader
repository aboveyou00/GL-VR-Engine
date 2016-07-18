

#version 430

layout(location = 0) varying vec3 in_light_color;
layout(location = 1) varying vec3 in_color;

layout(location = 0) out vec4 out_color;

void main(void)
{
    out_color = vec4(in_color * in_light_color, 1);
}
