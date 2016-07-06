

#version 120
#extension GL_ARB_separate_shader_objects : enable
#extension GL_ARB_explicit_attrib_location : enable

layout(location = 0) in vec3 in_position;
layout(location = 1) in vec3 in_normal;
layout(location = 2) in vec3 in_color;

uniform vec3 direct_light_direction;
uniform vec3 direct_light_color;
uniform vec3 ambient_light_color;
layout(location = 0) varying vec3 out_light_color;
layout(location = 1) varying vec3 out_color;

void main(void)
{
    gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * vec4(in_position, 1);
    out_color = in_color;

    float direct_light_amt = clamp(dot(gl_ProjectionMatrix * gl_ModelViewMatrix * vec4(direct_light_direction, 1), vec4(in_normal, 1)), 0.0, 1.0);
    vec3 direct_light = direct_light_amt * direct_light_color;

    //out_light_color = vec3(1, 1, 1);
    out_light_color = ambient_light_color + direct_light;
}
