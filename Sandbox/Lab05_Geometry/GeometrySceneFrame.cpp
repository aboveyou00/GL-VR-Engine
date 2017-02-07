#include "stdafx.h"
#include "GeometrySceneFrame.h"

#include "../CameraTargetObject.h"
#include "CameraGameObject.h"
#include "../LabControls.h"
#include "AmbientLightSource.h"
#include "../LightSourceObject.h"
#include "../RawGraphicsObject.h"
#include "../TemplateObj.h"

std::string wireframeVertex = R"raw(
#version 430 core

layout(location = 0) in vec3 xyz_position;
layout(location = 1) in vec2 uv_coords;
layout(location = 2) in vec3 normal;

layout(location = 0) out vec3 color;

layout(location = 0) uniform mat4 model_matrix;
layout(location = 1) uniform mat4 view_matrix;
layout(location = 2) uniform mat4 projection_matrix;

void main(void) {
    color = xyz_position;
    gl_Position = projection_matrix * view_matrix * model_matrix * vec4(xyz_position, 1.f);
}
)raw";

std::string wireframeGeometry = R"raw(
#version 430 core
layout(triangles) in;
layout(triangle_strip,  max_vertices = 3) out;

layout(location = 0) in vec3 in_color[];

layout(location = 0) out vec3 out_color;
layout(location = 1) out vec3 orthocentric_squared;

float distance_squared(vec4 a, vec4 b) {
    vec4 diff = a - b;
    return dot(diff, diff);
}

void main() {
    float a_sqr = distance_squared(gl_in[1].gl_Position, gl_in[2].gl_Position);
    float b_sqr = distance_squared(gl_in[0].gl_Position, gl_in[2].gl_Position);
    float c_sqr = distance_squared(gl_in[0].gl_Position, gl_in[1].gl_Position);

    vec3 crs = cross(gl_in[1].gl_Position.xyz - gl_in[0].gl_Position.xyz, gl_in[2].gl_Position.xyz - gl_in[0].gl_Position.xyz);
    float area_sqr = dot(crs, crs);

    float ha_sqr = sqrt(area_sqr / a_sqr);
    float hb_sqr = sqrt(area_sqr / b_sqr);
    float hc_sqr = sqrt(area_sqr / c_sqr);

    gl_Position = gl_in[0].gl_Position;
    out_color = in_color[0];
    orthocentric_squared = vec3(ha_sqr, 0, 0);
    EmitVertex();

    gl_Position = gl_in[1].gl_Position;
    out_color = in_color[1];
    orthocentric_squared = vec3(0, hb_sqr, 0);
    EmitVertex();

    gl_Position = gl_in[2].gl_Position;
    out_color = in_color[2];
    orthocentric_squared = vec3(0, 0, hc_sqr);
    EmitVertex();

    EndPrimitive();
}

)raw";

std::string wireframeFragment = R"raw(
#version 430 core

layout(location = 0) in vec3 in_color;
layout(location = 1) in vec3 orthocentric_squared;

layout(location = 0) out vec4 out_color;

void main(void) {
    float threshold_sqr = 0.002;
    if (orthocentric_squared.x < threshold_sqr || orthocentric_squared.y < threshold_sqr || orthocentric_squared.z < threshold_sqr) {
        out_color = vec4(1.0, 0.0, 0.0, 1.0);
    }
    else {
        out_color = vec4(0.0, 1.0, 0.0, 1.0);
    }
    //out_color = vec4(orthocentric_squared, 1.f);
    //out_color = vec4(in_color, 1.f);
}
)raw";

std::string hairVertex = R"raw(
#version 430 core

layout(location = 0) in vec3 xyz_position;
layout(location = 1) in vec2 uv_coords;
layout(location = 2) in vec3 in_normal;

layout(location = 0) out vec3 color;
layout(location = 1) out vec4 out_normal;

layout(location = 0) uniform mat4 model_matrix;
layout(location = 1) uniform mat4 view_matrix;
layout(location = 2) uniform mat4 projection_matrix;

void main(void) {
    color = xyz_position;
    gl_Position = projection_matrix * view_matrix * model_matrix * vec4(xyz_position, 1.f);
    out_normal = projection_matrix * view_matrix * model_matrix * vec4(in_normal, 0.f);
}
)raw";

std::string hairGeometry = R"raw(
#version 430 core
layout(triangles) in;
layout(triangle_strip, max_vertices = 15) out;

layout(location = 0) in vec3 in_color[];
layout(location = 1) in vec4 in_normal[];

layout(location = 0) flat out vec3 out_color;

void DrawNormal(vec4 position, vec3 normal, vec3 color) 
{
    gl_Position = position + vec4(-0.01, 0, 0, 0);
    out_color = color;
    EmitVertex();

    gl_Position = position + vec4(0.01, 0, 0, 0);
    out_color = color;
    EmitVertex();

    gl_Position = position + vec4(normal * 0.5, 0.0);
    out_color = color;
    EmitVertex();

    EndPrimitive();
}

void main() {
    vec4 mid = (gl_in[0].gl_Position + gl_in[1].gl_Position) / 2.f;
    vec4 centroid_pos = gl_in[2].gl_Position + (mid - gl_in[2].gl_Position) * 2.f / 3.f;

    gl_Position = gl_in[0].gl_Position;
    out_color = in_color[0];
    EmitVertex();

    gl_Position = gl_in[1].gl_Position;
    out_color = in_color[1];
    EmitVertex();

    gl_Position = gl_in[2].gl_Position;
    out_color = in_color[2];
    EmitVertex();

    EndPrimitive();

    vec3 normal = normalize(cross(gl_in[2].gl_Position.xyz - gl_in[0].gl_Position.xyz, gl_in[1].gl_Position.xyz - gl_in[0].gl_Position.xyz));
    DrawNormal(centroid_pos, normal, vec3(1.0, 0.0, 0.0));

    EndPrimitive();

    for (int n = 0; n < 3; n++)
    {
        DrawNormal(gl_in[n].gl_Position, in_normal[n].xyz, vec3(0.0, 0.0, 1.0));
    }
}
)raw";

std::string hairFragment = R"raw(
#version 430 core

layout(location = 0) flat in vec3 in_color;

layout(location = 0) out vec4 out_color;

void main(void) {
    out_color = vec4(in_color, 1.f);
}
)raw";

GeometrySceneFrame::GeometrySceneFrame()
{
}
GeometrySceneFrame::~GeometrySceneFrame()
{
}

bool GeometrySceneFrame::Initialize()
{
    if (!Frame::Initialize()) return false;

    auto cameraTarget = this->CreateGameObject<CameraTargetObject>();

    auto cameraObject = this->CreateGameObject<GlEngine::CameraGameObject>();
    cameraObject->SetTargetObject(cameraTarget);
    cameraObject->SetLock(GlEngine::CameraLock::RELATIVE_POSITION);
    cameraObject->SetPosition({ 0, -3.5, 7 });

    auto controls = CreateGameObject<LabControls>();

    auto ambient = new GlEngine::AmbientLightSource({ .25f, .25f, .25f });
    auto pointLight = CreateGameObject<PointLightSourceObject>();
    controls->SetControllingLight(pointLight->lightSource());
    pointLight->lightSource()->SetPosition({ 0, 2.5, -2.5 });

    ambient;

    auto wireframeSource = new GlEngine::ShaderFactory::ShaderSource {
        &wireframeVertex,
        nullptr,
        nullptr,
        &wireframeGeometry,
        &wireframeFragment,
    };

    auto hairSource = new GlEngine::ShaderFactory::ShaderSource{
        &hairVertex,
        nullptr,
        nullptr,
        &hairGeometry,
        &hairFragment,
    };

    auto props = new std::map<size_t, ShaderProp*> {
        { 0, &GlEngine::ShaderFactory::prop_ViewMatrix },
        { 1, &GlEngine::ShaderFactory::prop_ModelMatrix },
        { 2, &GlEngine::ShaderFactory::prop_ProjectionMatrix }
    };
    auto phongTorus = CreateGameObject<TemplateObj>(
        [wireframeSource, hairSource, props](TemplateObj* self, GlEngine::GraphicsContext*) {
            auto gobj = new RawGraphicsObject(
                "Resources/torus.obj",
                hairSource,
                props
            );
            for (size_t q = 0; q < self->providers.size(); q++)
                gobj->AddPropertyProvider(self->providers[q]);
            gobj->SetMaterial(self->templateMat);

            return (GlEngine::GraphicsObject*)gobj; // why do I need this?
        },
        new TemplateMaterial(
            {
            },
            {
            },
            [](TemplateMaterial*, GlEngine::ShaderFactory::ShaderFactory&)
            {
                //factory.ProvideProperty(GlEngine::ShaderFactory::prop_RgbColor, phongData.color);
            }
        ),
        std::vector<IPropertyProvider*> {
        },
        [](TemplateObj*, float) mutable {
        }
    );
    phongTorus->SetPosition({ 0, 0, 0 });

    //auto crateTex = GlEngine::Texture::FromFile("Textures/crate.png");
    //auto cube1 = CreateGameObject<GlEngine::CubeGameObject>(Vector<3> { 3, 3, 3 }, crateTex);
    //cube1->graphicsObject()->AddPropertyProvider(ambient);
    //cube1->graphicsObject()->AddPropertyProvider(pointLight->lightSource());
    //cube1->SetPosition({ -7.5f, 0, 0 });
    //cube1->SetRotationSpeed({ 0, 45deg, 0 });

    //auto brickTex = GlEngine::Texture::FromFile("Textures/bricks.png");
    //auto mossOverlayTex = GlEngine::Texture::FromFile("Textures/moss-overlay.png", GlEngine::TextureFlag::Translucent);
    //auto cube2 = CreateGameObject<GlEngine::CubeGameObject>(Vector<3> { 3, 3, 3 }, brickTex, mossOverlayTex);
    //cube2->graphicsObject()->AddPropertyProvider(ambient);
    //cube2->graphicsObject()->AddPropertyProvider(pointLight->lightSource());
    //cube2->SetPosition({ -2.5f, 0, 0 });
    //cube2->SetRotationSpeed({ 0, 45deg, 0 });

    //auto cube3 = CreateGameObject<FrameBufferCubeGameObject>(Vector<3> { 3, 3, 3 });
    //cube3->graphicsObject()->AddPropertyProvider(ambient);
    //cube3->graphicsObject()->AddPropertyProvider(pointLight->lightSource());
    //cube3->SetPosition({ 2.5f, 0, 0 });
    //cube3->SetRotationSpeed({ 0, 45deg, 0 });

    //auto leafMaskTex = GlEngine::Texture::FromFile("Textures/leaf-mask.png", GlEngine::TextureFlag::AlphaMap);
    //auto cube4 = CreateGameObject<GlEngine::CubeGameObject>(Vector<3> { 3, 3, 3 }, crateTex, leafMaskTex);
    //cube4->graphicsObject()->AddPropertyProvider(ambient);
    //cube4->graphicsObject()->AddPropertyProvider(pointLight->lightSource());
    //cube4->SetPosition({ 7.5f, 0, 0 });
    //cube4->SetRotationSpeed({ 0, 45deg, 0 });

    //auto crateNormalMask = GlEngine::Texture::FromFile("Textures/crate-normals.png", GlEngine::TextureFlag::NormalMask);
    //auto plane1 = CreateGameObject<GlEngine::PlaneGameObject>(Vector<2> { 16, 16 }, Vector<2> { 1, 1 }, crateTex, crateNormalMask);
    //plane1->graphicsObject()->AddPropertyProvider(ambient);
    //plane1->graphicsObject()->AddPropertyProvider(pointLight->lightSource());
    //plane1->SetPosition({ 0, -3.f, 0 });

    return true;
}
