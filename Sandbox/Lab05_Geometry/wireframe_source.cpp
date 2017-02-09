#include "stdafx.h"

std::string wireframeVertex = R"raw(
#version 430 core

layout(location = 0) in vec3 xyz_position;
layout(location = 1) in vec2 uv_coords;
layout(location = 2) in vec3 normal;

layout(location = 0) out vec3 color;

layout(location = 0) uniform mat4 model_matrix;
layout(location = 1) uniform mat4 view_matrix;
layout(location = 2) uniform mat4 projection_matrix;

void main(void) {
    color = xyz_position;
    gl_Position = projection_matrix * view_matrix * model_matrix * vec4(xyz_position, 1.f);
}
)raw";

std::string wireframeGeometry = R"raw(
#version 430 core
layout(triangles) in;
layout(triangle_strip,  max_vertices = 3) out;

layout(location = 0) in vec3 in_color[];

layout(location = 3) uniform vec2 screen_dimensions;

layout(location = 0) out vec3 out_color;
layout(location = 1) noperspective out vec3 orthocentric;

float distance_squared(vec4 a, vec4 b) {
    vec4 diff = a - b;
    return dot(diff, diff);
}

void main() {
    float sx = screen_dimensions.x;
    float sy = screen_dimensions.y;
    mat4 viewPort = mat4(
        sx / 2, 0, 0, sx / 2,
        0, sy / 2, 0, sy / 2,
        0, 0,      0,  0,
        0, 0,      0,  1
    );

    vec4 p0 = viewPort * (gl_in[0].gl_Position / gl_in[0].gl_Position.w);
    vec4 p1 = viewPort * (gl_in[1].gl_Position / gl_in[1].gl_Position.w);
    vec4 p2 = viewPort * (gl_in[2].gl_Position / gl_in[2].gl_Position.w);

    //vec4 p0 = (gl_in[0].gl_Position / gl_in[0].gl_Position.w);
    //vec4 p1 = (gl_in[1].gl_Position / gl_in[1].gl_Position.w);
    //vec4 p2 = (gl_in[2].gl_Position / gl_in[2].gl_Position.w);

    float a_sqr = distance_squared(p1, p2);
    float b_sqr = distance_squared(p0, p2);
    float c_sqr = distance_squared(p0, p1);

    vec3 crs = cross(p1.xyz - p0.xyz, p2.xyz - p0.xyz);
    float area_sqr = dot(crs, crs);

    float ha = sqrt(area_sqr / a_sqr);
    float hb = sqrt(area_sqr / b_sqr);
    float hc = sqrt(area_sqr / c_sqr);

    gl_Position = gl_in[0].gl_Position;
    out_color = in_color[0];
    orthocentric = vec3(ha, 0, 0);
    EmitVertex();

    gl_Position = gl_in[1].gl_Position;
    out_color = in_color[1];
    orthocentric = vec3(0, hb, 0);
    EmitVertex();

    gl_Position = gl_in[2].gl_Position;
    out_color = in_color[2];
    orthocentric = vec3(0, 0, hc);
    EmitVertex();

    EndPrimitive();
}

)raw";

std::string wireframeFragment = R"raw(
#version 430 core

layout(location = 0) in vec3 in_color;
layout(location = 1) noperspective in vec3 orthocentric;

layout(location = 4) uniform float wireframe_thickness;

layout(location = 0) out vec4 out_color;

void main(void) {
    float d = min(min(orthocentric.x, orthocentric.y), orthocentric.z);
    float proportion;
    if (wireframe_thickness > 0) proportion = smoothstep(wireframe_thickness - 0.5, wireframe_thickness + 0.5, d);
    else proportion = 1;
    out_color = mix(vec4(1.0, 0.0, 0.0, 1.0), vec4(in_color, 1.0), proportion);
}
)raw";
