

#version 430

layout(location = 0) in vec3 in_light_color;
layout(location = 1) in vec3 in_color;

layout(location = 0) out vec4 out_color;

void main(void)
{
    vec4 direct_color = vec4(in_color * in_light_color, 1);

    const vec4 fog_color = vec4(0.0, 0.0, 0.0, 1.0);

    float dist = gl_FragCoord.z / gl_FragCoord.w;
    float fog_amt = clamp(sqrt(dist) / 6, 0.0, 1.0);
    out_color = mix(direct_color, fog_color, fog_amt);
}
