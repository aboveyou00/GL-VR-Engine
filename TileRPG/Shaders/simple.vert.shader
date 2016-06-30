

#version 120
#extension GL_ARB_separate_shader_objects : enable
#extension GL_ARB_explicit_attrib_location : enable

layout(location = 0) in vec3 vt_position;
layout(location = 1) in vec3 vt_color;

layout(location = 0) varying vec4 fg_color;

void main(void)
{
    gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * vec4(vt_position, 1);
    gl_Position.y *= 2;

    fg_color = vec4(vt_color, 1);
}
