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

subroutine(DistortionFunction) vec4 MedianConvolution3(vec2 xy)
{
    vec4 pixels[9];
    float mags[9];

    for (int x = 0; x < 3; x++)
    {
        for (int y = 0; y < 3; y++)
        {
            vec2 step = vec2(x - 1, y - 1) / screen_dimensions;
            vec2 coord = uv_coords + step;
            vec4 pixel_color = texture2D(scene_texture, coord);
            pixels[(x * 3) + y] = pixel_color;
            mags[(x * 3) + y] = dot(pixel_color, pixel_color);
        }
    }

    for (int w = 0; w < 8; w++)
    {
        for (int q = 0; q < 8 - w; q++)
        {
            if (mags[q] < mags[q + 1])
            {
                float tempf = mags[q];
                vec4 tempv = pixels[q];
                mags[q] = mags[q + 1];
                pixels[q] = pixels[q + 1];
                mags[q + 1] = tempf;
                pixels[q + 1] = tempv;
            }
        }
    }

    return pixels[4];
}

subroutine(DistortionFunction) vec4 MedianConvolution5(vec2 xy)
{
    vec4 pixels[25];
    float mags[25];

    for (int x = 0; x < 5; x++)
    {
        for (int y = 0; y < 5; y++)
        {
            vec2 step = vec2(x - 2, y - 2) / screen_dimensions;
            vec2 coord = uv_coords + step;
            vec4 pixel_color = texture2D(scene_texture, coord);
            pixels[(x * 5) + y] = pixel_color;
            mags[(x * 5) + y] = dot(pixel_color, pixel_color);
        }
    }

    for (int w = 0; w < 24; w++)
    {
        for (int q = 0; q < 24 - w; q++)
        {
            if (mags[q] < mags[q + 1])
            {
                float tempf = mags[q];
                vec4 tempv = pixels[q];
                mags[q] = mags[q + 1];
                pixels[q] = pixels[q + 1];
                mags[q + 1] = tempf;
                pixels[q + 1] = tempv;
            }
        }
    }

    return pixels[12];
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
