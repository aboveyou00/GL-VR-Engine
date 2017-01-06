

#version 430

layout(vertices = 3) out;

layout(location = 0) in vec3 in_vertex_pos[];
layout(location = 1) in vec3 in_normal[];
layout(location = 2) in vec2 in_uv_coords[];

layout(location = 0) out vec3 out_vertex_pos[];
layout(location = 1) out vec3 out_normal[];
layout(location = 2) out vec2 out_uv_coords[];

//layout(location = 0) uniform mat4 projection_matrix;
layout(location = 1) uniform mat4 model_view_matrix;
//layout(location = 2) uniform vec3 direct_light_direction;
//layout(location = 3) uniform vec3 direct_light_color;
//layout(location = 4) uniform vec3 ambient_light_color;
//layout(location = 5) uniform sampler2D texture_sampler;
//layout(location = 6) uniform float in_game_time;

#define ID gl_InvocationID

void main(void)
{
    out_vertex_pos[ID] = in_vertex_pos[ID];
    out_normal[ID] = in_normal[ID];
    out_uv_coords[ID] = in_uv_coords[ID];

    if (ID == 0)
    {
        vec4 vertex_pos = model_view_matrix * vec4(in_vertex_pos[ID], 1);
        int tessLevel = int(clamp(3 + (vertex_pos.z * .5 + 3), 1, 6));
        gl_TessLevelInner[0] = tessLevel;
        gl_TessLevelOuter[0] = gl_TessLevelOuter[1] = gl_TessLevelOuter[2] = tessLevel;
    }
}
