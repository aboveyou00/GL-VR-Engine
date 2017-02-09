#include "stdafx.h"
#include "LightsAndEffectsSceneFrame.h"

#include "CameraGameObject.h"
#include "Lab3Controls.h"
#include "../CameraTargetObject.h"

#include "Tree.h"
#include "RandomUtils.h"
#include "../LightSourceObject.h"
#include "../TemplateObj.h"
#include "../TemplateMaterial.h"
#include "../TemplateMaterialFactory.h"
#include "StageGraphicsObject.h"
#include "PointLightSource.h"
#include "AmbientLightSource.h"
#include "FogSource.h"
#include "StageGameObject.h"

#include "Property.h"
#include "Attribute.h"
#include "ShaderFactory.h"
#include "SpotlightSource.h"
#include "Environment.h"

#include "../RawGraphicsObject.h"

#include "MultiPhongMaterial.h"

#include "LogUtils.h"

typedef GlEngine::ShaderFactory::IPropertyProvider IPropertyProvider;
typedef GlEngine::PointLightSource PointLightSource;
typedef GlEngine::SpotlightSource SpotlightSource;

#define GLSL(src) "#version 430 \n" #src

std::string vertexSource = GLSL(
    layout(location = 0) uniform mat4 in_view_matrix;
    layout(location = 1) uniform mat4 in_model_matrix;
    layout(location = 2) uniform mat4 in_projection_matrix;
    
    layout(location = 0) in vec3 in_xyz_position;
    layout(location = 1) in vec2 in_uv_coords;
    layout(location = 2) in vec3 in_normal;

    layout(location = 0) out vec3 out_xyz_position;
    layout(location = 1) out vec4 out_modelview_normal;

    void main(void) {
        mat4 model_view_matrix = in_view_matrix * in_model_matrix;
        mat4 model_view_projection_matrix = in_projection_matrix * model_view_matrix;
        gl_Position = model_view_projection_matrix * vec4(in_xyz_position, 1);
        out_modelview_normal = model_view_matrix * vec4(in_normal, 0);
        out_xyz_position = in_xyz_position;
    }
);

std::string fragmentSource = GLSL(
    layout(location = 0) uniform mat4 in_view_matrix;
    layout(location = 1) uniform mat4 in_model_matrix;
    layout(location = 3) uniform vec3 in_rgb_color;
    layout(location = 4) uniform vec3 in_point_light_position;
    layout(location = 5) uniform vec3 in_camera_position;
    layout(location = 6) uniform vec3 in_reflection_coefficient;
    layout(location = 7) uniform vec3 in_specular_light_color;
    layout(location = 8) uniform float in_shininess;
    layout(location = 9) uniform vec3 in_diffuse_light_color;
    layout(location = 10) uniform vec3 in_ambient_light_color;
    layout(location = 11) uniform vec2 in_screen_dimensions;

    layout(location = 0) in vec3 in_xyz_position;
    layout(location = 1) in vec4 in_modelview_normal;

    layout(location = 0) out vec4 out_color;

    // DEBUG GENERATED
    struct DebugResult
    {
        vec4 base_color;
        vec3 light_color;
    };

    layout(location = 12) uniform vec2 debug_position;

    layout(location = 2) flat in uint is_debug_surface;
    layout(location = 3) flat in DebugResult debug_result;

    const uint font[12 * 2] = uint[12 * 2] (
        0x00000000, 0x00000000,
        0x384CC6C6, 0xC6643800,
        0x18381818, 0x18187E00,
        0x7CC60E3C, 0x78E0FE00,
        0x7E0C183C, 0x06C67C00,
        0x1C3C6CCC, 0xFE0C0C00,
        0xFCC0FC06, 0x06C67C00,
        0x3C60C0FC, 0xC6C67C00,
        0xFEC60C18, 0x30303000,
        0x7CC6C67C, 0xC6C67C00,
        0x7CC6C67E, 0x060C7800,
        0x00000000, 0x00303060,
    );
    
    uint GetCharacter(float value, uint idx)
    {
        float val = value;
        uint digits[32];
        uint before_decimal = 0;
        while (val >= 1.0)
        {
            digits[before_decimal] = uint(mod(val, 10.0) + 0.5);
            val /= 10.0;
            before_decimal++;
        }

        if (idx < before_decimal)
        {
            return digits[before_decimal - idx - 1] + 1u;
        }
        else if (idx > before_decimal)
        {
            uint places = idx - before_decimal;
            while (places > 0)
            {
                value *= 10.0;
                places--;
            }
            return uint(mod(value, 10.0) + 0.5);
        }
        else
        {
            return 12u;
        }
    }
    
    void main(void) {
        if (is_debug_surface > 0)
        {
            uint pixel_x = uint(gl_FragCoord.x) - uint(in_screen_dimensions.x * (debug_position.x + 1.0) / 2.0);
            uint pixel_y = uint(in_screen_dimensions.y - gl_FragCoord.y) - uint(in_screen_dimensions.y * (-debug_position.y + 1.0) / 2.0);
                        
            uint char_idx_x = pixel_x / 8u;
            uint char_idx_y = pixel_y / 8u;
            uint char_x = 7 - pixel_x % 8;
            uint char_y = 7 - pixel_y % 8;

            uint character;
            
            if (char_idx_y == 0)
            {
                character = GetCharacter(result.light_color.r, char_idx_x);
            }
            else
            {
                character = 0u;
            }

            //uint character = characters[char_idx_x + 32 * char_idx_y];
            
            uint pixel;
            if (char_y < 4u)
            {
                pixel = (font[2 * character + 1] >> (8u * (char_y - 4u) + char_x)) & 1u;
            }
            else
            {
                pixel = (font[2 * character] >> (8u * char_y + char_x)) & 1u;
            }
            
            if (pixel > 0)
            {
                out_color = vec4(1.0, 1.0, 1.0, 1.0);
            }
            else
            {
                out_color = vec4(0.2, 0.2, 0.2, 1.0);
            }
        }
        else
        {
            vec4 base_color = vec4(in_rgb_color, 1);
            vec4 model_view_position = in_view_matrix * in_model_matrix * vec4(in_xyz_position, 1);
            vec4 model_view_light_position = in_view_matrix * vec4(in_point_light_position, 1);
            vec3 point_light_direction = normalize(model_view_light_position.xyz - model_view_position.xyz);
        
            float diffuse_component_intensity = dot(point_light_direction, in_modelview_normal.xyz);
            if (!gl_FrontFacing) diffuse_component_intensity = -diffuse_component_intensity;
            vec3 diffuse_light_component = in_reflection_coefficient * in_diffuse_light_color * clamp(diffuse_component_intensity, 0.0, 1.0);
        
            // DEBUG_OUTPUT diffuse_component_intensity

            vec3 reflected_direction;
            vec3 surface_to_camera = normalize(vec3(in_view_matrix * vec4(in_camera_position, 1) - in_view_matrix * in_model_matrix * vec4(in_xyz_position, 1)));
            if (gl_FrontFacing) reflected_direction = normalize(reflect(point_light_direction, vec3(in_modelview_normal)));
            else reflected_direction = normalize(reflect(point_light_direction, vec3(-in_modelview_normal)));
            vec3 specular_light_component = in_reflection_coefficient * in_specular_light_color * pow(clamp(dot(reflected_direction, -surface_to_camera), 0.0, 1.0), in_shininess);
        
            vec3 light_color = in_ambient_light_color + diffuse_light_component + specular_light_component;
            out_color = vec4(light_color, 1.0) * base_color;
        }

        // DEBUG_OUTPUT base_color
        // DEBUG_OUTPUT reflected_direction
    }
);

std::string geometrySource = GLSL(
    struct DebugResult
    {
        vec4 base_color;
        vec3 light_color;
    };
    
    layout(triangles) in;
    layout(triangle_strip, max_vertices = 30) out;

    layout(location = 0) in vec3 in_xyz_position_arr[];
    layout(location = 1) in vec4 in_modelview_normal_arr[];

    layout(location = 0) out vec3 out_xyz_position;
    layout(location = 1) out vec4 out_modelview_normal;
    layout(location = 0) uniform mat4 in_view_matrix;
    layout(location = 1) uniform mat4 in_model_matrix;
    layout(location = 2) uniform mat4 in_projection_matrix;
    layout(location = 3) uniform vec3 in_rgb_color;
    layout(location = 4) uniform vec3 in_point_light_position;
    layout(location = 5) uniform vec3 in_camera_position;
    layout(location = 6) uniform vec3 in_reflection_coefficient;
    layout(location = 7) uniform vec3 in_specular_light_color;
    layout(location = 8) uniform float in_shininess;
    layout(location = 9) uniform vec3 in_diffuse_light_color;
    layout(location = 10) uniform vec3 in_ambient_light_color;
    layout(location = 11) uniform vec2 in_screen_dimensions;
    
    layout(location = 12) uniform vec2 debug_position;

    layout(location = 2) flat out uint is_debug_surface;
    layout(location = 3) flat out DebugResult debug_result;

    DebugResult CalculateDebugResult(vec3 barycentric)
    {
        // TODO: THESE ARE NOT PERSPECTIVE CORRECTED
        vec3 in_xyz_position = (barycentric.x * in_xyz_position_arr[0] + barycentric.x * in_xyz_position_arr[1] + barycentric.x * in_xyz_position_arr[2]) / 3.0;
        vec4 in_modelview_normal = (barycentric.x * in_modelview_normal_arr[0] + barycentric.x * in_modelview_normal_arr[1] + barycentric.x * in_modelview_normal_arr[2]) / 3.0;
        vec4 out_color;

        // Begin Fragment Code

        bool BUILTIN_gl_FrontFacing = true;

        vec4 base_color = vec4(in_rgb_color, 1);
        vec4 model_view_position = in_view_matrix * in_model_matrix * vec4(in_xyz_position, 1);
        vec4 model_view_light_position = in_view_matrix * vec4(in_point_light_position, 1);
        vec3 point_light_direction = normalize(model_view_light_position.xyz - model_view_position.xyz);

        float diffuse_component_intensity = dot(point_light_direction, in_modelview_normal.xyz);
        if (!BUILTIN_gl_FrontFacing) diffuse_component_intensity = -diffuse_component_intensity;
        vec3 diffuse_light_component = in_reflection_coefficient * in_diffuse_light_color * clamp(diffuse_component_intensity, 0.0, 1.0);

        vec3 reflected_direction;
        vec3 surface_to_camera = normalize(vec3(in_view_matrix * vec4(in_camera_position, 1) - in_view_matrix * in_model_matrix * vec4(in_xyz_position, 1)));
        if (BUILTIN_gl_FrontFacing) reflected_direction = normalize(reflect(point_light_direction, vec3(in_modelview_normal)));
        else reflected_direction = normalize(reflect(point_light_direction, vec3(-in_modelview_normal)));
        vec3 specular_light_component = in_reflection_coefficient * in_specular_light_color * pow(clamp(dot(reflected_direction, -surface_to_camera), 0.0, 1.0), in_shininess);

        vec3 light_color = in_ambient_light_color + diffuse_light_component + specular_light_component;
        out_color = vec4(light_color, 1.0) * base_color;

        // End Fragment Code

        return DebugResult(base_color, light_color);
    }

    // TODO: return early in certain situations for efficiency
    vec3 Barycentric(vec2 p, vec2 a, vec2 b, vec2 c)
    {
        vec2 v0 = b - a;
        vec2 v1 = c - a;
        vec2 v2 = p - a;
        float d00 = dot(v0, v0);
        float d01 = dot(v0, v1);
        float d11 = dot(v1, v1);
        float d20 = dot(v2, v0);
        float d21 = dot(v2, v1);
        float denom = d00 * d11 - d01 * d01;
        
        float v = (d11 * d20 - d01 * d21) / denom;
        float w = (d00 * d21 - d01 * d20) / denom;
        float u = 1.0f - v - w;
        return vec3(u, v, w);
    }

    void DrawSquare(vec2 pos, float width, DebugResult result) {
        gl_Position = vec4(pos, 0.0, 1.0) + vec4(0.0, -width, 0.0, 0.0);
        is_debug_surface = 1u;
        debug_result = result;
        EmitVertex();

        gl_Position = vec4(pos, 0.0, 1.0) + vec4(width, -width, 0.0, 0.0);
        is_debug_surface = 1u;
        debug_result = result;
        EmitVertex();
        
        gl_Position = vec4(pos, 0.0, 1.0) + vec4(0.0, 0.0, 0.0, 0.0);
        is_debug_surface = 1u;
        debug_result = result;
        EmitVertex();
        
        gl_Position = vec4(pos, 0.0, 1.0) + vec4(width, 0.0, 0.0, 0.0);
        is_debug_surface = 1u;
        debug_result = result;
        EmitVertex();

        EndPrimitive();
    }

    void PassThrough()
    {
        gl_Position = gl_in[0].gl_Position;
        out_xyz_position = in_xyz_position_arr[0];
        out_modelview_normal = in_modelview_normal_arr[0];
        is_debug_surface = 0u;
        EmitVertex();

        gl_Position = gl_in[1].gl_Position;
        out_xyz_position = in_xyz_position_arr[1];
        out_modelview_normal = in_modelview_normal_arr[1];
        is_debug_surface = 0u;
        EmitVertex();

        gl_Position = gl_in[2].gl_Position;
        out_xyz_position = in_xyz_position_arr[2];
        out_modelview_normal = in_modelview_normal_arr[2];
        is_debug_surface = 0u;
        EmitVertex();

        EndPrimitive();
    }

    void main(void) {
        PassThrough();

        vec3 barycentric = Barycentric(debug_position, 
                                       vec2(gl_in[0].gl_Position) / gl_in[0].gl_Position[3], 
                                       vec2(gl_in[1].gl_Position) / gl_in[1].gl_Position[3], 
                                       vec2(gl_in[2].gl_Position) / gl_in[2].gl_Position[3]);
        float z = 0.5;
        //float z = barycentric.x * gl_in[0].gl_Position[2] + barycentric.y * gl_in[1].gl_Position[2];

        if (0.0 <= z && z <= 1.0 && 
            0.0 <= barycentric.x && barycentric.x <= 1.0 && 
            0.0 <= barycentric.y && barycentric.y <= 1.0 && 
            0.0 <= barycentric.z && barycentric.z <= 1.0)
        {
            DebugResult result = CalculateDebugResult(barycentric);
            DrawSquare(debug_position, 0.1, result);
        }

        if (gl_PrimitiveIDIn == 0)
        {
            DrawSquare(debug_position, 0.2, DebugResult(vec4(0,0,0,0), vec3(0,0,0)));
        }
    }
);

LightsAndEffectsSceneFrame::LightsAndEffectsSceneFrame()
{
}
LightsAndEffectsSceneFrame::~LightsAndEffectsSceneFrame()
{
}

bool LightsAndEffectsSceneFrame::Initialize()
{
    auto cameraTarget = this->CreateGameObject<CameraTargetObject>();

    auto cameraObject = this->CreateGameObject<GlEngine::CameraGameObject>();
    cameraObject->SetTargetObject(cameraTarget);
    cameraObject->SetLock(GlEngine::CameraLock::RELATIVE_POSITION);
    cameraObject->SetPosition({ 0, -3.5, 7 });

    CreateGameObject<Lab3Controls>();

    //auto ambientLightSource = new GlEngine::AmbientLightSource({ .1f, .1f, .1f });
    //auto lightGobj = CreateGameObject<LightSourceObject<PointLightSource>>(new PointLightSource());
    //auto fog = new GlEngine::FogSource(10.f, 25.f, { 0.f, 0.f, 0.f, 1.f });
    //lightGobj->lightSource()->SetPosition({ 0, 6.f, -6.f });

    //for (int q = -2; q <= 2; q++)
    //{
    //    for (int w = -2; w <= 2; w++)
    //    {
    //        float rndX = GlEngine::Util::random(2.f) - 1,
    //              rndZ = GlEngine::Util::random(2.f) - 1;
    //        CreateGameObject<Tree>(Vector<3> { (q * 5) + rndX, 0, (w * 5) + rndZ }, std::vector<IPropertyProvider*> { ambientLightSource, lightGobj->lightSource(), fog });
    //    }
    //}

    //ambientLightSource = new GlEngine::AmbientLightSource({ .3f, .3f, .3f });
    //CreateGameObject<StageGameObject>(std::vector<IPropertyProvider*> { ambientLightSource, lightGobj->lightSource(), fog });

    //struct {
    //    Vector<3> color = { 1.0f, 0.2f, 1.0f };
    //    Vector<3> ambient = { 0.1f, 0.1f, 0.1f };
    //    Vector<3> reflectionCoef = { 0.9f, 0.9f, 0.9f };
    //    Vector<3> rotationAxis = { 1, 0, 0 };
    //    float totalDelta = 0.0;
    //    float rotationSpeed = 0.5;
    //    float distance = 3.0;
    //    LightSourceObject<PointLightSource>* lightSource = nullptr;
    //} celData;
    //celData.lightSource = CreateGameObject<LightSourceObject<PointLightSource>>(new PointLightSource());

    //auto cel = CreateGameObject<TemplateObj>(
    //    "Resources/torus.obj",
    //    new TemplateMaterial(
    //        {
    //            &GlEngine::ShaderFactory::prop_RgbColor,
    //            &GlEngine::ShaderFactory::prop_ReflectionCoefficient,
    //            &GlEngine::ShaderFactory::prop_AmbientLightColor,
    //            &GlEngine::ShaderFactory::prop_CelLevels
    //        },
    //        {
    //            &GlEngine::ShaderFactory::attr_GlPosition,
    //            &GlEngine::ShaderFactory::attr_AmbientDiffuse,
    //            &GlEngine::ShaderFactory::attr_RgbBaseColor,
    //            &GlEngine::ShaderFactory::attr_CelShading
    //        },
    //        [celData](TemplateMaterial*, GlEngine::ShaderFactory::ShaderFactory& factory)
    //        {
    //            factory.ProvideProperty(GlEngine::ShaderFactory::prop_RgbColor, celData.color);
    //            factory.ProvideProperty(GlEngine::ShaderFactory::prop_ReflectionCoefficient, celData.reflectionCoef);
    //            factory.ProvideProperty(GlEngine::ShaderFactory::prop_AmbientLightColor, celData.ambient);
    //            factory.ProvideProperty(GlEngine::ShaderFactory::prop_CelLevels, (int)Lab3Controls::celShadingSteps);
    //        }
    //    ), 
    //    std::vector<IPropertyProvider*> {
    //        celData.lightSource->lightSource()
    //    },
    //    [celData](TemplateObj* self, float delta) mutable {
    //        if (LabControls::isPaused) return;
    //        else if (!!celData.rotationAxis[0] && !LabControls::rotateZ) return;
    //        else if (!!celData.rotationAxis[1] && !LabControls::rotateY) return;
    //        else if (!!celData.rotationAxis[2] && !LabControls::rotateX) return;

    //        celData.totalDelta += delta;
    //        auto rotationAmount = celData.totalDelta * celData.rotationSpeed;
    //        auto transformMatrix = !!celData.rotationAxis[0] ? Matrix<4, 4>::TranslateMatrix({ 0, celData.distance, 0 }) * Matrix<4, 4>::RollMatrix(rotationAmount)  * Matrix<4, 4>::TranslateMatrix(self->position) :
    //                               !!celData.rotationAxis[1] ? Matrix<4, 4>::TranslateMatrix({ 0, 0, celData.distance }) * Matrix<4, 4>::YawMatrix(rotationAmount)   * Matrix<4, 4>::TranslateMatrix(self->position) :
    //                                                           Matrix<4, 4>::TranslateMatrix({ celData.distance, 0, 0 }) * Matrix<4, 4>::PitchMatrix(rotationAmount) * Matrix<4, 4>::TranslateMatrix(self->position);
    //        auto transformedPosition = transformMatrix.Transpose() * Vector<4>{ 0, 0, 0, 1 };
    //        celData.lightSource->lightSource()->SetPosition({ transformedPosition[0], transformedPosition[1], transformedPosition[2] });
    //    }
    //);
    //cel->SetPosition({ 100, 5, 0 });

    struct {
        LightSourceObject<PointLightSource> *rotXLight = nullptr,
                                            *rotYLight = nullptr,
                                            *rotZLight = nullptr;
        float rotXDelta = 0,
              rotYDelta = 0,
              rotZDelta = 0,
              rotationSpeed = .5f,
              distance = 3.f;
    } multiPhongData;
    multiPhongData.rotXLight = CreateGameObject<LightSourceObject<PointLightSource>>();
    multiPhongData.rotYLight = CreateGameObject<LightSourceObject<PointLightSource>>();
    multiPhongData.rotZLight = CreateGameObject<LightSourceObject<PointLightSource>>();
    multiPhongData.rotXLight->lightSource()->SetDiffuseColor({ 1.f, 0.f, 0.f });
    multiPhongData.rotYLight->lightSource()->SetDiffuseColor({ 0.f, 1.f, 0.f });
    multiPhongData.rotZLight->lightSource()->SetDiffuseColor({ 0.f, 0.f, 1.f });

    struct {
        Vector<3> ambient = { 0.1f, 0.1f, 0.1f };
        Vector<3> color = { 1.0f, 1.0f, 0.2f };
        Vector<3> floorColor = { 0.6, 0.6, 0.3 };
        Vector<3> reflectionCoef = { 0.9f, 0.9f, 0.9f };
        Vector<3> rotationAxis = { 0, 1, 0 };
        Vector<3> lightPosition = { -120, 0, -15 };
        float totalDelta = 0.0;
        float rotationSpeed = 0.5;
        float distance = 2.0;
        float shininess = 5.0;
        LightSourceObject<SpotlightSource>* lightSource = nullptr;
    } spotData;
    spotData.lightSource = CreateGameObject<LightSourceObject<SpotlightSource>>(new SpotlightSource({ 0, 1, 0 }, { 1.0, 1.0, 1.0 }, 3.0f, { 1, 0, 0 }, 10deg));

    for (int i = 0; i < 250; i++)
    {
        auto spotTorus = CreateGameObject<TemplateObj>(
            "Resources/torus.obj",
            TemplateMaterial::Factory()
                ->Provide(&GlEngine::ShaderFactory::prop_RgbColor, spotData.color)
                ->Provide(&GlEngine::ShaderFactory::prop_ReflectionCoefficient, spotData.reflectionCoef)
                ->Provide(&GlEngine::ShaderFactory::prop_Shininess, spotData.shininess)
                ->Provide(&GlEngine::ShaderFactory::prop_AmbientLightColor, spotData.ambient)
                ->Create(),
            std::vector<IPropertyProvider*> {
                spotData.lightSource->lightSource()
            }
        );
        float rndX = GlEngine::Util::random(2.f) - 1;
        float rndY = GlEngine::Util::random(2.f) - 1;
        float rndZ = GlEngine::Util::random(2.f) - 1;
        float rotX = GlEngine::Util::random(GlEngine::Util::PI_f);
        float rotZ = GlEngine::Util::random(GlEngine::Util::PI_f);

        spotTorus->SetPosition({ -100 + rndX * 15, rndY * 15, rndZ * 15 });
        spotTorus->RotateX(rotX);
        spotTorus->RotateZ(rotZ);
    }

    auto spotFloor = CreateGameObject<TemplateObj>(
        [](TemplateObj* self, GlEngine::GraphicsContext*) -> GlEngine::GraphicsObject*
        {
            auto gobj = new StageGraphicsObject(false);
            for (auto it = self->providers().begin(); it != self->providers().end(); it++)
                gobj->AddPropertyProvider(*it);
            gobj->SetMaterial(&self->material());
            return gobj;
        },
        TemplateMaterial::Factory()
            ->Provide(&GlEngine::ShaderFactory::prop_RgbColor, spotData.floorColor)
            ->Provide(&GlEngine::ShaderFactory::prop_ReflectionCoefficient, spotData.reflectionCoef)
            ->Provide(&GlEngine::ShaderFactory::prop_AmbientLightColor, spotData.ambient)
            ->Provide(&GlEngine::ShaderFactory::prop_Shininess, spotData.shininess)
            ->Create(),
        std::vector<IPropertyProvider*> {
            spotData.lightSource->lightSource()
        },
        [spotData](TemplateObj*, float delta) mutable {
            spotData.lightSource->lightSource()->SetAngleAttenuation(Lab3Controls::spotlightAttenuation);
            spotData.lightSource->lightSource()->SetCutoffTheta(Lab3Controls::spotlightCutoffAngle);

            if (LabControls::isPaused) return;
            else if (!!spotData.rotationAxis[0] && !LabControls::rotateZ) return;
            else if (!!spotData.rotationAxis[1] && !LabControls::rotateY) return;
            else if (!!spotData.rotationAxis[2] && !LabControls::rotateX) return;

            spotData.totalDelta += delta;
            auto rotationAmount = spotData.totalDelta * spotData.rotationSpeed;
            auto transformMatrix = !!spotData.rotationAxis[0] ? Matrix<4, 4>::TranslateMatrix({ 0, spotData.distance, 0 }) * Matrix<4, 4>::RollMatrix(rotationAmount)  * Matrix<4, 4>::TranslateMatrix(spotData.lightPosition) :
                                    !!spotData.rotationAxis[1] ? Matrix<4, 4>::TranslateMatrix({ 0, 0, spotData.distance }) * Matrix<4, 4>::YawMatrix(rotationAmount)   * Matrix<4, 4>::TranslateMatrix(spotData.lightPosition) :
                                                                Matrix<4, 4>::TranslateMatrix({ spotData.distance, 0, 0 }) * Matrix<4, 4>::PitchMatrix(rotationAmount) * Matrix<4, 4>::TranslateMatrix(spotData.lightPosition);
            auto transformedPosition = transformMatrix.Transpose() * Vector<4>{ 0, 0, 0, 1 };
            Vector<3> tPos = { transformedPosition[0], transformedPosition[1], transformedPosition[2] };
            auto relPosition = spotData.lightPosition - tPos;
            auto direction = Vector<3>{ relPosition[0], relPosition[1], relPosition[2] }.Normalized();

            spotData.lightSource->lightSource()->SetPosition({ transformedPosition[0], transformedPosition[1], transformedPosition[2] });
            spotData.lightSource->lightSource()->SetDirection(direction);
        }
    );
    spotFloor->SetPosition({ -100, -10, 0 });

    struct {
        Vector<3> color = { 1.0f, 0.2f, 1.0f };
        Vector<3> ambient = { 0.1f, 0.1f, 0.1f };
        Vector<3> reflectionCoef = { 0.5f, 0.5f, 0.5f };
        Vector<3> rotationAxis = { 1, 0, 0 };
        float shininess = 10.0f;
        float totalDelta = 0.0;
        float rotationSpeed = 0.5;
        float distance = 1.0;
        LightSourceObject<PointLightSource>* lightSource = nullptr;
    } phongData;
    phongData.lightSource = CreateGameObject<LightSourceObject<PointLightSource>>(new PointLightSource());
    //phongData.lightSource = new LightSourceObject<PointLightSource>(new PointLightSource());

    //auto phongTorus = CreateGameObject<TemplateObj>(
    //    [](TemplateObj* self, GlEngine::GraphicsContext*) {
    //        auto gobj = new RawGraphicsObject(
    //        "Resources/torus.obj",
    //        {
    //            &vertexSource,
    //            nullptr,
    //            nullptr,
    //            &geometrySource,
    //            &fragmentSource,
    //        },
    //        {
    //            { 0, &GlEngine::ShaderFactory::prop_ViewMatrix },
    //            { 1, &GlEngine::ShaderFactory::prop_ModelMatrix },
    //            { 2, &GlEngine::ShaderFactory::prop_ProjectionMatrix },
    //            { 3, &GlEngine::ShaderFactory::prop_RgbColor },
    //            { 4, &GlEngine::ShaderFactory::prop_PointLightPosition },
    //            { 5, &GlEngine::ShaderFactory::prop_CameraPosition },
    //            { 6, &GlEngine::ShaderFactory::prop_ReflectionCoefficient },
    //            { 7, &GlEngine::ShaderFactory::prop_SpecularLightColor },
    //            { 8, &GlEngine::ShaderFactory::prop_Shininess },
    //            { 9, &GlEngine::ShaderFactory::prop_DiffuseLightColor },
    //            { 10, &GlEngine::ShaderFactory::prop_AmbientLightColor },
    //            { 11, &GlEngine::ShaderFactory::prop_ScreenDimensions },
    //            { 12, &GlEngine::ShaderFactory::prop_MouseClipPosition }
    //        }
    //        );

    //        for (size_t q = 0; q < self->providers.size(); q++)
    //            gobj->AddPropertyProvider(self->providers[q]);
    //        gobj->SetMaterial(self->templateMat);

    //        return (GlEngine::GraphicsObject*)gobj; // why do I need this?
    //    },
    //    new TemplateMaterial(
    //        {
    //            &GlEngine::ShaderFactory::prop_RgbColor,
    //            &GlEngine::ShaderFactory::prop_ReflectionCoefficient,
    //            &GlEngine::ShaderFactory::prop_AmbientLightColor,
    //            &GlEngine::ShaderFactory::prop_Shininess
    //        },
    //        {
    //            &GlEngine::ShaderFactory::attr_GlPosition,
    //            &GlEngine::ShaderFactory::attr_Phong,
    //            &GlEngine::ShaderFactory::attr_RgbBaseColor,
    //        },
    //        [phongData](TemplateMaterial*, GlEngine::ShaderFactory::ShaderFactory& factory)
    //        {
    //            factory.ProvideProperty(GlEngine::ShaderFactory::prop_RgbColor, phongData.color);
    //            factory.ProvideProperty(GlEngine::ShaderFactory::prop_ReflectionCoefficient, phongData.reflectionCoef);
    //            factory.ProvideProperty(GlEngine::ShaderFactory::prop_Shininess, phongData.shininess);
    //            factory.ProvideProperty(GlEngine::ShaderFactory::prop_AmbientLightColor, phongData.ambient);
    //        }
    //    ),
    //    std::vector<IPropertyProvider*> {
    //        phongData.lightSource->lightSource()
    //    },
    //    [phongData](TemplateObj* self, float) mutable {
    //        phongData.lightSource->lightSource()->SetPosition(self->position + Vector<3>{-2, 0.5, -1});
    //    }
    //);
    //phongTorus->SetPosition({ 0, 0, 0 });

    return true;
}
