

#version 430

layout(location = 0) in vec3 in_position;
layout(location = 1) in vec3 in_color;

layout(location = 0) varying vec4 out_color;

void main(void)
{
    gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * vec4(in_position, 1);

    out_color = vec4(in_color, 1);
}
