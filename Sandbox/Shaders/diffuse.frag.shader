

#version 430

layout(location = 0) in vec3 in_light_color;
layout(location = 1) in vec2 in_uv_coords;

//layout(location = 0) uniform mat4 projection_matrix;
//layout(location = 1) uniform mat4 model_view_matrix;
//layout(location = 2) uniform vec3 direct_light_direction;
//layout(location = 3) uniform vec3 direct_light_color;
//layout(location = 4) uniform vec3 ambient_light_color;
layout(location = 5) uniform vec3 base_color;

layout(location = 0) out vec4 out_color;

void main(void)
{
    vec4 direct_color = vec4(base_color, 1) * vec4(in_light_color, 1);
    out_color = direct_color;

    //const vec4 fog_color = vec4(0.0, 0.0, 0.0, 1.0);

    //float dist = gl_FragCoord.z / gl_FragCoord.w;
    //float fog_amt = clamp(sqrt(dist) / 6, 0.0, 1.0);
    //out_color = mix(direct_color, fog_color, fog_amt);
}
