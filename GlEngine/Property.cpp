#include "stdafx.h"
#include "Property.h"

namespace GlEngine
{
    namespace ShaderFactory
    {
#pragma region vertex-attributes
        Property<Vector<3>> prop_RgbColor("rgb_color");
        Property<Vector<4>> prop_RgbaColor("color");

        Property<Vector<3>> prop_Position("xyz_position");
        Property<Vector<3>> prop_Normal("normal");
        Property<Vector<2>> prop_UV("uv_coords");
        Property<Vector<3>> prop_ReflectionCoefficient("reflection_coefficient");

        Property<Vector<4>> prop_ModelViewNormal("modelview_normal");
        
        Property<Vector<4>> prop_GlPosition("gl_Position", true);
#pragma endregion

#pragma region environment
        Property<Matrix<4, 4>> prop_ModelMatrix("model_matrix");
        Property<Matrix<4, 4>> prop_ViewMatrix("view_matrix");
        Property<Matrix<4, 4>> prop_ProjectionMatrix("projection_matrix");

        Property<Matrix<4, 4>> prop_ModelViewMatrix("model_view_matrix");
        Property<Matrix<4, 4>> prop_ModelViewProjectionMatrix("model_view_projection_matrix");

        Property<float> prop_GameTime("game_time_millis");
#pragma endregion

#pragma region lighting
        //Should these be vec4 or vec3?
        Property<Vector<3>> prop_LightColor("light_color");

        Property<Vector<3>> prop_SpecularLightColor("specular_light_color");
        Property<Vector<3>> prop_DiffuseLightColor("diffuse_light_color");
        Property<Vector<3>> prop_AmbientLightColor("ambient_light_color");

        Property<Vector<3>> prop_PointLightPosition("diffuse_light_position");
        Property<Vector<3>> prop_PointLightDirection("diffuse_light_direction");
#pragma endregion
    }
}
