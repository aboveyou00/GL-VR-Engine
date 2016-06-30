

#version 120
#extension GL_ARB_separate_shader_objects : enable
#extension GL_ARB_explicit_attrib_location : enable

layout(location = 0) varying vec4 fg_color;

void main(void)
{
    gl_FragColor = fg_color;
}
