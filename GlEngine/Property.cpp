#include "stdafx.h"
#include "Property.h"

namespace GlEngine
{
    namespace ShaderFactory
    {
        Property<Vector<3>> prop_RgbColor("rgb_color");
        Property<Vector<4>> prop_RgbaColor("color");

        Property<Vector<3>> prop_Position("xyz_position");
        Property<Vector<3>> prop_Normal("normal");
        Property<Vector<2>> prop_UV("uv_coords");
        Property<Vector<3>> prop_ReflectionCoefficient("reflection_coefficient");
        
        Property<Vector<4>> prop_GlPosition("gl_Position", true);

        Property<Matrix<4, 4>> prop_ModelMatrix("model_matrix");
        Property<Matrix<4, 4>> prop_ViewMatrix("view_matrix");
        Property<Matrix<4, 4>> prop_ProjectionMatrix("projection_matrix");

        Property<Matrix<4, 4>> prop_ModelViewMatrix("model_view_matrix");
        Property<Matrix<4, 4>> prop_ModelViewProjectionMatrix("model_view_projection_matrix");

        //Should these be vec4 or vec3?
        Property<Vector<4>> prop_LightColor("light_color");
        Property<Vector<4>> prop_AmbientLightColor("ambient_light_color");

        Property<Vector<4>> prop_DiffuseLightColor("diffuse_light_color");
        Property<Vector<3>> prop_DiffuseLightPosition("diffuse_light_position");
        Property<Vector<4>> prop_DiffuseLightDirection("diffuse_light_direction");
    }
}
