

#version 430

layout(triangles, equal_spacing, ccw) in;

layout(location = 0) in vec3 in_vertex_pos[];
layout(location = 1) in vec3 in_normal[];
layout(location = 2) in vec2 in_uv_coords[];

//layout(location = 0) out vec3 out_vertex_pos;
layout(location = 0) out vec3 out_light_color;
layout(location = 1) out vec2 out_uv_coords;

layout(location = 0) uniform mat4 projection_matrix;
layout(location = 1) uniform mat4 model_view_matrix;
layout(location = 2) uniform vec3 direct_light_direction;
layout(location = 3) uniform vec3 direct_light_color;
layout(location = 4) uniform vec3 ambient_light_color;
layout(location = 5) uniform sampler2D texture_sampler;
layout(location = 6) uniform float in_game_time;

//float rand(vec2 co)
//{
//    return fract(sin(dot(co.xy, vec2(12.9898, 78.233))) * 43758.5453);
//}

float water_wave(vec2 xz)
{
    float xcomp = (xz.x - in_game_time) * 2;
    float ycomp = (xz.y - in_game_time) * 2;
    return .1 * sin(xcomp + ycomp);
}
vec2 derivative_water_wave(vec2 xz)
{
    return vec2(
        water_wave(vec2(xz.x - .1, xz.y)) - water_wave(vec2(xz.x + .1, xz.y)),
        water_wave(vec2(xz.x, xz.y - .1)) - water_wave(vec2(xz.x, xz.y + .1))
    ) * 8;
}

void main(void)
{
    //in vec3 gl_TessCoord
    //in int gl_PatchVerticesIn
    //in int gl_PrimitiveID

    //gl_Position = vec4(gl_TessCoord.x, gl_TessCoord.y + rand(gl_TessCoord.xz) / 2, gl_TessCoord.z);
	
	vec3 p0 = gl_TessCoord.x * in_vertex_pos[0];
	vec3 p1 = gl_TessCoord.y * in_vertex_pos[1];
	vec3 p2 = gl_TessCoord.z * in_vertex_pos[2];
	vec3 local_vertex_pos = p0 + p1 + p2;
    local_vertex_pos.y += water_wave(local_vertex_pos.xz);

    vec3 n0 = gl_TessCoord.x * in_normal[0];
    vec3 n1 = gl_TessCoord.y * in_normal[1];
    vec3 n2 = gl_TessCoord.z * in_normal[2];
    vec3 normal = n0 + n1 + n2;
    normal.xz += derivative_water_wave(local_vertex_pos.xz);

    float direct_light_amt = clamp(dot(direct_light_direction, normal), 0.0, 1.0);
    vec3 direct_light = direct_light_amt * direct_light_color;
    out_light_color = ambient_light_color + direct_light;

    vec2 uv0 = gl_TessCoord.x * in_uv_coords[0];
    vec2 uv1 = gl_TessCoord.y * in_uv_coords[1];
    vec2 uv2 = gl_TessCoord.z * in_uv_coords[2];
    out_uv_coords = uv0 + uv1 + uv2;

	gl_Position = projection_matrix * model_view_matrix * vec4(local_vertex_pos, 1);
}
