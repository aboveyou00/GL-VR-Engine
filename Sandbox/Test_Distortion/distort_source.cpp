#include "stdafx.h"

std::string distortVertex = R"raw(
#version 430 core

layout(location = 0) in vec3 xyz_position;
layout(location = 1) in vec2 in_uv_coords;

layout(location = 0) out vec2 out_uv_coords;

void main(void)
{
    gl_Position = vec4(xyz_position.xyx, 1);
    out_uv_coords = in_uv_coords;
}
)raw";

std::string distortFragment = R"raw(
#version 430 core

#define KERNEL_SIZE 5
subroutine vec4 DistortionFunction(vec2 xy);

layout(location = 0) in vec2 uv_coords;

layout(location = 0) uniform float game_time;
layout(location = 1) uniform vec2 screen_dimensions;
layout(location = 2) uniform sampler2D scene_texture;
layout(location = 3) uniform float convolution_kernel[KERNEL_SIZE * KERNEL_SIZE];

layout(location = 0) subroutine uniform DistortionFunction distortion_fn;

layout(location = 0) out vec4 out_color;

subroutine(DistortionFunction) vec4 PassThrough(vec2 xy)
{
    return texture2D(scene_texture, uv_coords);
}

subroutine(DistortionFunction) vec4 SinWave(vec2 xy)
{
    vec2 offset = vec2(sin((xy.y / 100) + game_time) / 25, cos((xy.x / 140) + game_time) / 20);
    return texture2D(scene_texture, uv_coords + offset);
}

subroutine(DistortionFunction) vec4 Convolution(vec2 xy)
{
    vec4 result = vec4(0, 0, 0, 0);
    for (int x = 0; x < KERNEL_SIZE; x++)
    {
        for (int y = 0; y < KERNEL_SIZE; y++)
        {
            vec2 step = (vec2(x, y) - uvec2(KERNEL_SIZE / 2, KERNEL_SIZE / 2)) / screen_dimensions;
            vec2 coord = uv_coords + step;
            result += convolution_kernel[y * KERNEL_SIZE + x] * texture2D(scene_texture, coord);
        }
    }
    return result;
}

subroutine(DistortionFunction) vec4 MedianConvolution(vec2 xy)
{
    vec4 pixels[KERNEL_SIZE * KERNEL_SIZE];
    float mags[KERNEL_SIZE * KERNEL_SIZE];

    for (int i = 0; i < KERNEL_SIZE * KERNEL_SIZE; i++)
        mags[i] = 0;

    for (int x = 0; x < KERNEL_SIZE; x++)
    {
        for (int y = 0; y < KERNEL_SIZE; y++)
        {
            vec2 step = (vec2(x, y) - uvec2(KERNEL_SIZE / 2, KERNEL_SIZE / 2)) / screen_dimensions;
            vec2 coord = uv_coords + step;
            vec4 pixel_color = convolution_kernel[y * KERNEL_SIZE + x] * texture2D(scene_texture, coord);
            float mag = dot(pixel_color, pixel_color);

            uint i = 0;
            while(mag < mags[i] && i < y * KERNEL_SIZE + x)
                i++;
            for (int j = KERNEL_SIZE * KERNEL_SIZE - 1; j > i; j--)
            {
                mags[j] = mags[j - 1];
                pixels[j] = pixels[j - 1];
            }
            mags[i] = mag;
            pixels[i] = pixel_color;
        }
    }
    
    //return pixels[0];
    return pixels[KERNEL_SIZE * KERNEL_SIZE / 2];
}

subroutine(DistortionFunction) vec4 EdgeConvolution(vec2 xy)
{
    vec4 color = abs(Convolution(xy));
    float mag = max(color.r, max(color.g, color.b));
    return vec4(mag, mag, mag, 1.0);
}

subroutine(DistortionFunction) vec4 Outline(vec2 xy)
{
    vec4 edge = EdgeConvolution(xy);
    vec4 color = PassThrough(xy);
    if (edge.r > 0.1)
        return vec4(1.0, 1.0, 1.0, 1.0);
    else
        return color;
}

void main(void)
{
    out_color = distortion_fn(gl_FragCoord.xy);
}
)raw";
