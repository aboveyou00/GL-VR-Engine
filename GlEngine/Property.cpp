#include "stdafx.h"
#include "Property.h"
#include "PointLightInfo.h"

namespace GlEngine::ShaderFactory
{
#pragma region vertex-attributes
    Property<Vector<3>> prop_RgbColor("rgb_color");
    Property<Vector<4>> prop_BaseColor("base_color");
    Property<Vector<4>> prop_RgbaColor("color");

    Property<Vector<3>> prop_Position("xyz_position");
    Property<Vector<3>> prop_Normal("normal");
    Property<Vector<2>> prop_UV("uv_coords");
    Property<Vector<3>> prop_ReflectionCoefficient("reflection_coefficient");
    Property<float> prop_Shininess("shininess");

    Property<Vector<4>> prop_ModelViewNormal("modelview_normal");

    Property<Vector<4>> prop_GlPosition("gl_Position", PropertyFlag::BuiltIn);
    Property<Vector<4>> prop_GlFragCoord("gl_FragCoord", PropertyFlag::BuiltIn | PropertyFlag::Resolved);

    Property<Texture*> prop_Texture("texture");
    Property<Texture*> prop_Texture2("texture2");
    Property<Texture*> prop_AlphaMapTexture("alpha_map_texture");
    Property<Texture*> prop_NormalMapTexture("normal_map");

    Property<Vector<2>> prop_BillboardSize("billboard_size");
#pragma endregion

#pragma region environment
    Property<Matrix<4, 4>> prop_ModelMatrix("model_matrix");
    Property<Matrix<4, 4>> prop_ViewMatrix("view_matrix");
    Property<Matrix<4, 4>> prop_ProjectionMatrix("projection_matrix");

    Property<Matrix<4, 4>> prop_ModelViewMatrix("model_view_matrix");
    Property<Matrix<4, 4>> prop_ModelViewProjectionMatrix("model_view_projection_matrix");

    Property<Vector<3>> prop_CameraPosition("camera_position");

    Property<float> prop_GameTime("game_time_millis");
    Property<Vector<2>> prop_MouseScreenPosition("mouse_screen_position");
    Property<Vector<2>> prop_MouseClipPosition("mouse_clip_position");

    Property<Vector<2>> prop_ScreenDimensions("screen_dimensions");
#pragma endregion

#pragma region instancing
    Property<Matrix<4, 4>> prop_InstanceModelMatrix("instance_model_matrix");
#pragma endregion

#pragma region lighting
    //Should these be vec4 or vec3?
    Property<Vector<3>> prop_LightColor("light_color");

    Property<Vector<3>> prop_SpecularLightComponent("specular_light_component");
    Property<Vector<3>> prop_DiffuseLightComponent("diffuse_light_component");
    Property<Vector<3>> prop_DiffuseLightComponentFlat("diffuse_light_component", PropertyFlag::Flat);

    Property<Vector<3>> prop_SpecularLightColor("specular_light_color");
    Property<Vector<3>> prop_DiffuseLightColor("diffuse_light_color");
    Property<Vector<3>> prop_AmbientLightColor("ambient_light_color");

    Property<Vector<3>> prop_PointLightPosition("point_light_position");
    Property<Vector<3>> prop_PointLightDirection("point_light_direction");
    Property<Vector<3>> prop_DirectionalLightDirection("directional_light_direction");

    Property<Array<PointLightInfo, 4>> prop_PointLightInfo("point_light_info");

    Property<Vector<3>> prop_SurfaceToCamera("surface_to_camera");
    Property<float> prop_DiffuseComponentIntensity("diffuse_component_intensity");

    Property<float> prop_FogMinDistance("fog_min_distance");
    Property<float> prop_FogMaxDistance("fog_max_distance");
    Property<Vector<4>> prop_FogColor("fog_color");

    Property<int> prop_CelLevels("cel_levels");

    Property<Vector<3>> prop_SpotlightPosition("spotlight_position");
    Property<Vector<3>> prop_SpotlightColor("spotlight_color");
    Property<Vector<3>> prop_SpotlightDirection("spotlight_direction");
    Property<float> prop_SpotlightAttenuation("spotlight_attenuation");
    Property<float> prop_SpotlightCutoffAngle("spotlight_cutoff_angle");
#pragma endregion
}
