#include "stdafx.h"
#include <map>
#include "ComponentArray.h"
#include "Property.h"
using namespace GlEngine::ShaderFactory;

std::string wavesVertex = R"raw(
#version 430 core

layout(location = 0) uniform mat4 in_view_matrix;
layout(location = 1) uniform mat4 in_model_matrix;
layout(location = 2) uniform mat4 in_projection_matrix;
layout(location = 11) uniform float in_game_time;

layout(location = 0) in vec3 in_xyz_position;
layout(location = 2) in vec3 in_normal;

layout(location = 0) out vec3 out_xyz_position;
layout(location = 1) out vec4 out_modelview_normal;

void main(void) {
    mat4 model_view_projection_matrix;
    mat4 model_matrix;
    vec3 normal;
    mat4 projection_matrix;
    vec4 modelview_normal;
    mat4 view_matrix;
    mat4 model_view_matrix;
    vec3 xyz_position;
    float game_time;
    
/* BEGIN INPUT IDENTITIES */ 
    view_matrix = in_view_matrix;
    model_matrix = in_model_matrix;
    projection_matrix = in_projection_matrix;
    xyz_position = in_xyz_position;
    normal = in_normal;
    game_time = in_game_time;
/* END INPUT IDENTITIES */

    float yy = sin(xyz_position.x - xyz_position.z + game_time * 4);
    xyz_position = vec3(xyz_position.x, yy, xyz_position.z);
    float dx = -cos(xyz_position.x - xyz_position.z + game_time * 4);
    float dz = cos(xyz_position.x - xyz_position.z + game_time * 4);
    normal = vec3(dx, 1, dz);

    model_view_matrix = view_matrix * model_matrix;
    model_view_projection_matrix = projection_matrix * model_view_matrix;
    gl_Position = model_view_projection_matrix * vec4(xyz_position, 1);
    modelview_normal = normalize(model_view_matrix * vec4(normal, 0));

/* BEGIN OUTPUT IDENTITIES */
    out_xyz_position = in_xyz_position;
    out_modelview_normal = modelview_normal;
/* END OUTPUT IDENTITIES */
}
)raw";

std::string wavesFragment = R"raw(
#version 430 core

layout(location = 0) uniform mat4 in_view_matrix;
layout(location = 1) uniform mat4 in_model_matrix;
layout(location = 3) uniform vec3 in_point_light_position;
layout(location = 4) uniform vec3 in_camera_position;
layout(location = 5) uniform vec3 in_reflection_coefficient;
layout(location = 6) uniform vec3 in_specular_light_color;
layout(location = 7) uniform float in_shininess;
layout(location = 8) uniform vec3 in_diffuse_light_color;
layout(location = 9) uniform vec3 in_ambient_light_color;
layout(location = 10) uniform vec3 in_rgb_color;

layout(location = 0) in vec3 in_xyz_position;
layout(location = 1) in vec4 in_modelview_normal;

layout(location = 0) out vec4 out_color;

void main(void) {
    vec3 diffuse_light_color;
    vec4 color;
    vec3 light_color;
    float shininess;
    vec3 specular_light_color;
    vec4 base_color;
    mat4 model_matrix;
    vec3 ambient_light_color;
    vec3 point_light_position;
    vec3 diffuse_light_component;
    vec3 surface_to_camera;
    vec4 modelview_normal;
    vec3 specular_light_component;
    float diffuse_component_intensity;
    vec3 rgb_color;
    vec3 point_light_direction;
    vec3 reflection_coefficient;
    vec3 camera_position;
    mat4 view_matrix;
    vec3 xyz_position;
    
    vec4 temp_00CA5008_0;
    vec4 temp_00CA5008_1;
    vec3 temp_00CA4DF8_0;
    
/* BEGIN INPUT IDENTITIES */ 
    xyz_position = in_xyz_position;
    model_matrix = in_model_matrix;
    view_matrix = in_view_matrix;
    point_light_position = in_point_light_position;
    modelview_normal = in_modelview_normal;
    camera_position = in_camera_position;
    reflection_coefficient = in_reflection_coefficient;
    specular_light_color = in_specular_light_color;
    shininess = in_shininess;
    diffuse_light_color = in_diffuse_light_color;
    ambient_light_color = in_ambient_light_color;
    rgb_color = in_rgb_color;
/* END INPUT IDENTITIES */ 

    temp_00CA5008_0 = view_matrix * model_matrix * vec4(xyz_position, 1);
    temp_00CA5008_1 = view_matrix * vec4(point_light_position, 1);
    point_light_direction = normalize(temp_00CA5008_1.xyz - temp_00CA5008_0.xyz);
    diffuse_component_intensity = dot(point_light_direction, modelview_normal.xyz);
    surface_to_camera = normalize(vec3(view_matrix * vec4(camera_position, 1) - view_matrix * model_matrix * vec4(xyz_position, 1))); //normalized vector from surface position to camera position
    if (gl_FrontFacing) temp_00CA4DF8_0 = normalize(reflect(point_light_direction, vec3(modelview_normal))); //light direction reflected across the normal
    else temp_00CA4DF8_0 = normalize(reflect(point_light_direction, vec3(-modelview_normal)));
    specular_light_component = reflection_coefficient * specular_light_color * pow(clamp(dot(temp_00CA4DF8_0, -surface_to_camera), 0.0, 1.0), shininess); //specular light calculation
    if (!gl_FrontFacing) diffuse_component_intensity = -diffuse_component_intensity;
    diffuse_light_component = reflection_coefficient * diffuse_light_color * clamp(diffuse_component_intensity, 0.0, 1.0);
    light_color = ambient_light_color + diffuse_light_component + specular_light_component;
    base_color = vec4(rgb_color, 1);
    color = vec4(light_color, 1) * base_color;

/* BEGIN OUTPUT IDENTITIES */
    out_color = color;
/* END OUTPUT IDENTITIES */
}
)raw";

std::map<unsigned, GlEngine::ShaderFactory::ShaderProp*> wavesProps = {
    { 0, &prop_ViewMatrix },
    { 1, &prop_ModelMatrix },
    { 2, &prop_ProjectionMatrix },
    { 3, &prop_PointLightPosition },
    { 4, &prop_CameraPosition },
    { 5, &prop_ReflectionCoefficient },
    { 6, &prop_SpecularLightColor },
    { 7, &prop_Shininess },
    { 8, &prop_DiffuseLightColor },
    { 9, &prop_AmbientLightColor },
    { 10, &prop_RgbColor },
    { 11, &prop_GameTime }
};

ShaderSource wavesSource = {
    &wavesVertex,
    nullptr,
    nullptr,
    nullptr,
    &wavesFragment
};
