

#version 120
#extension GL_ARB_separate_shader_objects : enable
#extension GL_ARB_explicit_attrib_location : enable

layout(location = 0) varying vec3 in_light_color;
layout(location = 1) varying vec3 in_color;

void main(void)
{
    gl_FragColor = vec4(in_color * in_light_color, 1);
}
