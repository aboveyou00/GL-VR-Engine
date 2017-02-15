#include "stdafx.h"

std::string convolutionVertex = R"raw(
#version 430 core

layout(location = 0) in vec3 xyz_position;
layout(location = 1) in vec2 uv_coords;

layout(location = 0) uniform mat4 model_matrix;
layout(location = 1) uniform mat4 view_matrix;
layout(location = 2) uniform mat4 projection_matrix;

void main(void) {
    gl_Position = projection_matrix * view_matrix * model_matrix * vec4(xyz_position, 1);
}
)raw";

std::string convolutionFragment = R"raw(
#version 430 core
#define KERNEL_SIZE = 5

layout(location = 3) uniform sampler2d tex;
layout(location = 4) uniform float[KERNEL_SIZE * KERNEL_SIZE] convolution_kernel;

layout(location = 0) vec4 out_color;

void main(void) {
    out_color = vec4(0, 0, 0, 0);

    for (int x = 0; x < KERNEL_SIZE; x++)
    {
        for (int y = 0; y < KERNEL_SIZE; y++)
        {
            vec2 step = vec2(x, y) - uvec2(KERNEL_SIZE / 2, KERNEL_SIZE / 2);
            vec2 coord = gl_FragCoord + step;
            out_color += convolution_kernel[y * KERNEL_SIZE + x] * texture2d(tex, coord);
        }
    }
}
)raw";