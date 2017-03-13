#include "stdafx.h"
#include <map>
#include "ComponentArray.h"
#include "Property.h"
using namespace GlEngine::ShaderFactory;

std::string instancedPhongFogVertex = R"raw(
#version 430 core

layout(location = 0) uniform mat4 in_view_matrix;
layout(location = 1) uniform mat4 in_model_matrix;
layout(location = 2) uniform mat4 in_projection_matrix;
layout(location = 3) uniform vec3 in_camera_position;

layout(location = 0) in vec3 in_xyz_position;
layout(location = 1) in vec2 in_uv_coords;
layout(location = 2) in vec3 in_normal;
layout(location = 3) in mat4 in_instance_model_matrix;

layout(location = 0) out vec2 out_uv_coords;
layout(location = 1) out vec3 out_xyz_position;
layout(location = 2) out vec4 out_modelview_normal;
layout(location = 3) out mat4 out_instance_model_matrix;
layout(location = 7) out float out_fog_dist_to_camera;

void main(void) {
    float fog_dist_to_camera;
    mat4 model_view_projection_matrix;
    mat4 model_matrix;
    mat4 instance_model_matrix;
    vec3 normal;
    mat4 projection_matrix;
    vec4 modelview_normal;
    vec3 camera_position;
    mat4 view_matrix;
    mat4 model_view_matrix;
    vec3 xyz_position;
    vec2 uv_coords;
    
/* BEGIN INPUT IDENTITIES */
    view_matrix = in_view_matrix;
    model_matrix = in_model_matrix;
    instance_model_matrix = in_instance_model_matrix;
    projection_matrix = in_projection_matrix;
    xyz_position = in_xyz_position;
    uv_coords = in_uv_coords;
    normal = in_normal;
    camera_position = in_camera_position;
/* END INPUT IDENTITIES */

    model_view_matrix = view_matrix * model_matrix * instance_model_matrix;
    model_view_projection_matrix = projection_matrix * model_view_matrix;
    gl_Position = model_view_projection_matrix * vec4(xyz_position, 1);
    modelview_normal = model_view_matrix * vec4(normal, 0);
    fog_dist_to_camera = distance(vec3(model_matrix * vec4(xyz_position, 1)), camera_position);

/* BEGIN OUTPUT IDENTITIES */
    out_uv_coords = uv_coords;
    out_xyz_position = in_xyz_position;
    out_modelview_normal = modelview_normal;
    out_instance_model_matrix = instance_model_matrix;
    out_fog_dist_to_camera = fog_dist_to_camera;
/* END OUTPUT IDENTITIES */
}
)raw";

std::string instancedPhongFogFragment = R"raw(
#version 430 core

layout(location = 0) uniform mat4 in_view_matrix;
layout(location = 1) uniform mat4 in_model_matrix;
layout(location = 3) uniform vec3 in_camera_position;
layout(location = 4) uniform sampler2D texture;
layout(location = 5) uniform vec3 in_point_light_position;
layout(location = 6) uniform vec3 in_reflection_coefficient;
layout(location = 7) uniform vec3 in_specular_light_color;
layout(location = 8) uniform float in_shininess;
layout(location = 9) uniform vec3 in_diffuse_light_color;
layout(location = 10) uniform vec3 in_spotlight_direction;
layout(location = 11) uniform float in_spotlight_attenuation;
layout(location = 12) uniform float in_spotlight_cutoff_angle;
layout(location = 13) uniform vec3 in_ambient_light_color;
layout(location = 14) uniform float in_fog_min_distance;
layout(location = 15) uniform float in_fog_max_distance;
layout(location = 16) uniform vec4 in_fog_color;

layout(location = 0) in vec2 in_uv_coords;
layout(location = 1) in vec3 in_xyz_position;
layout(location = 2) in vec4 in_modelview_normal;
layout(location = 3) in mat4 in_instance_model_matrix;
layout(location = 7) in float in_fog_dist_to_camera;

layout(location = 0) out vec4 out_color;

void main(void) {
    float fog_dist_to_camera;
    float spotlight_spot_factor;
    vec3 diffuse_light_color;
    vec4 color;
    vec3 light_color;
    float shininess;
    vec3 specular_light_color;
    vec4 base_color;
    mat4 model_matrix;
    mat4 instance_model_matrix;
    float fog_min_distance;
    vec3 ambient_light_color;
    vec4 fog_color;
    float spotlight_cutoff_angle;
    vec3 point_light_position;
    vec3 diffuse_light_component;
    vec3 spotlight_direction;
    vec3 surface_to_camera;
    vec4 modelview_normal;
    vec3 specular_light_component;
    float diffuse_component_intensity;
    vec3 point_light_direction;
    vec3 reflection_coefficient;
    vec3 camera_position;
    float spotlight_attenuation;
    float fog_max_distance;
    mat4 view_matrix;
    vec3 xyz_position;
    vec2 uv_coords;
    
    vec4 temp_00795FA8_0;
    vec4 temp_00795FA8_1;
    vec3 temp_00796058_0;
    float temp_00794638_0;
    float temp_007956B8_0;
    
/* BEGIN INPUT IDENTITIES */
    uv_coords = in_uv_coords;
    xyz_position = in_xyz_position;
    model_matrix = in_model_matrix;
    instance_model_matrix = in_instance_model_matrix;
    view_matrix = in_view_matrix;
    point_light_position = in_point_light_position;
    modelview_normal = in_modelview_normal;
    camera_position = in_camera_position;
    reflection_coefficient = in_reflection_coefficient;
    specular_light_color = in_specular_light_color;
    shininess = in_shininess;
    diffuse_light_color = in_diffuse_light_color;
    spotlight_direction = in_spotlight_direction;
    spotlight_attenuation = in_spotlight_attenuation;
    spotlight_cutoff_angle = in_spotlight_cutoff_angle;
    ambient_light_color = in_ambient_light_color;
    fog_dist_to_camera = in_fog_dist_to_camera;
    fog_min_distance = in_fog_min_distance;
    fog_max_distance = in_fog_max_distance;
    fog_color = in_fog_color;
/* END INPUT IDENTITIES */

    base_color = texture2D(texture, uv_coords);
    temp_00795FA8_0 = view_matrix * model_matrix * instance_model_matrix * vec4(xyz_position, 1);
    temp_00795FA8_1 = view_matrix * vec4(point_light_position, 1);
    point_light_direction = normalize(temp_00795FA8_1.xyz - temp_00795FA8_0.xyz);
    diffuse_component_intensity = dot(point_light_direction, modelview_normal.xyz);
    surface_to_camera = normalize(vec3(view_matrix * vec4(camera_position, 1) - view_matrix * model_matrix * instance_model_matrix * vec4(xyz_position, 1))); //normalized vector from surface position to camera position
    if (gl_FrontFacing) temp_00796058_0 = normalize(reflect(point_light_direction, vec3(modelview_normal))); //light direction reflected across the normal
    else temp_00796058_0 = normalize(reflect(point_light_direction, vec3(-modelview_normal)));
    specular_light_component = reflection_coefficient * specular_light_color * pow(clamp(dot(temp_00796058_0, -surface_to_camera), 0.0, 1.0), shininess); //specular light calculation
    if (!gl_FrontFacing) diffuse_component_intensity = -diffuse_component_intensity;
    diffuse_light_component = reflection_coefficient * diffuse_light_color * clamp(diffuse_component_intensity, 0.0, 1.0);
    temp_00794638_0 = dot(-point_light_direction, (view_matrix * vec4(spotlight_direction, 0)).xyz);
    if (temp_00794638_0 > cos(spotlight_cutoff_angle)) spotlight_spot_factor = pow(temp_00794638_0, spotlight_attenuation);
    else spotlight_spot_factor = 0;
    diffuse_light_component = diffuse_light_component * spotlight_spot_factor;
    specular_light_component = specular_light_component * spotlight_spot_factor;
    light_color = ambient_light_color + diffuse_light_component + specular_light_component;
    color = vec4(light_color, 1) * base_color;
    temp_007956B8_0 = clamp((fog_dist_to_camera - fog_min_distance) / (fog_max_distance - fog_min_distance), 0.0, 1.0) * fog_color.a;
    color = vec4(mix(color.xyz, fog_color.xyz, temp_007956B8_0), color.a);

/* BEGIN OUTPUT IDENTITIES */
    out_color = color;
/* END OUTPUT IDENTITIES */
}
)raw";

std::map<unsigned, GlEngine::ShaderFactory::ShaderProp*> instancedPhongFogProps = {
    { 0, &prop_ViewMatrix },
    { 1, &prop_ModelMatrix },
    { 2, &prop_ProjectionMatrix },
    { 3, &prop_CameraPosition },
    { 4, &prop_Texture },
    { 5, &prop_PointLightPosition },
    { 6, &prop_ReflectionCoefficient },
    { 7, &prop_SpecularLightColor },
    { 8, &prop_Shininess },
    { 9, &prop_DiffuseLightColor },
    { 10, &prop_SpotlightDirection },
    { 11, &prop_SpotlightAttenuation },
    { 12, &prop_SpotlightCutoffAngle },
    { 13, &prop_AmbientLightColor },
    { 14, &prop_FogMinDistance },
    { 15, &prop_FogMaxDistance },
    { 16, &prop_FogColor }
};

ShaderSource instancedPhongFogSource = {
    &instancedPhongFogVertex,
    nullptr,
    nullptr,
    nullptr,
    &instancedPhongFogFragment
};
