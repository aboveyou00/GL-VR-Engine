#include "stdafx.h"
#include <map>
#include "ComponentArray.h"
#include "Property.h"
using namespace GlEngine::ShaderFactory;

std::string fountainVertex = R"raw(
#version 430 core

layout(location = 0) in float start_time;
layout(location = 1) in float live_time;
layout(location = 2) in vec3 in_color;
layout(location = 3) in vec3 start_velocity;
layout(location = 4) in vec3 acceleration;

layout(location = 0) uniform mat4 model_matrix;
layout(location = 1) uniform mat4 view_matrix;
layout(location = 2) uniform mat4 projection_matrix;
layout(location = 3) uniform vec3 start_position;
layout(location = 4) uniform float game_time;

layout(location = 0) out vec3 out_color;
layout(location = 1) out float out_life;

void main(void) {
    float local_game_time = game_time - start_time;
    vec3 position = start_position + (start_velocity * local_game_time) + (.5 * local_game_time * local_game_time * acceleration);
    gl_Position = projection_matrix * view_matrix * model_matrix * vec4(position, 1);

    out_color = in_color;
    out_life = local_game_time / live_time;
}
)raw";

std::string fountainGeometry = R"raw(
#version 430 core

layout(points) in;
layout(triangle_strip, max_vertices = 4) out;

layout(location = 0) in vec3 in_color[];
layout(location = 1) in float in_life[];

layout(location = 5) uniform vec2 screen_size;
layout(location = 6) uniform vec2 billboard_size;

layout(location = 0) out vec2 uv_coords;
layout(location = 1) out vec4 out_color;

void main() {
    if (in_life[0] >= 0 && in_life[0] < 1)
    {
        vec4 pos = gl_in[0].gl_Position;
        float wh = (billboard_size[0] / screen_size[0]) * 5;
        float hh = (billboard_size[1] / screen_size[1]) * 5;

        float life_alpha = clamp(5 - in_life[0] * 5, 0, 1);

        gl_Position = pos + vec4(-wh, -hh, 0, 0);
        uv_coords = vec2(0, 0);
        out_color = vec4(in_color[0], life_alpha);
        EmitVertex();

        gl_Position = pos + vec4(-wh, +hh, 0, 0);
        uv_coords = vec2(0, 1);
        out_color = vec4(in_color[0], life_alpha);
        EmitVertex();

        gl_Position = pos + vec4(+wh, -hh, 0, 0);
        uv_coords = vec2(1, 0);
        out_color = vec4(in_color[0], life_alpha);
        EmitVertex();

        gl_Position = pos + vec4(+wh, +hh, 0, 0);
        uv_coords = vec2(1, 1);
        out_color = vec4(in_color[0], life_alpha);
        EmitVertex();

        EndPrimitive();
    }
}
)raw";

std::string fountainFragment = R"raw(
#version 430 core

layout(location = 0) in vec2 uv_coords;
layout(location = 1) in vec4 in_color;

layout(location = 7) uniform sampler2D billboard_texture;

layout(location = 0) out vec4 out_color;

void main(void) {
    out_color = texture2D(billboard_texture, uv_coords) * in_color;
    if (out_color.a == 0) discard;
}
)raw";

Property<float> prop_StartTime = Property<float>("start_time");
Property<float> prop_LiveTime = Property<float>("live_time");
Property<Vector<3>> prop_StartPosition = Property<Vector<3>>("start_position");
Property<Vector<3>> prop_StartVelocity = Property<Vector<3>>("start_velocity");
Property<Vector<3>> prop_Acceleration = Property<Vector<3>>("acceleration");

std::map<unsigned, GlEngine::ShaderFactory::ShaderProp*> fountainProps = {
    { 0, &prop_ModelMatrix },
    { 1, &prop_ViewMatrix },
    { 2, &prop_ProjectionMatrix },
    { 3, &prop_StartPosition },
    { 4, &prop_GameTime },
    { 5, &prop_ScreenDimensions },
    { 6, &prop_BillboardSize },
    { 7, &prop_Texture }
};

ShaderSource fountainSource = {
    &fountainVertex,
    nullptr,
    nullptr,
    &fountainGeometry,
    &fountainFragment
};
