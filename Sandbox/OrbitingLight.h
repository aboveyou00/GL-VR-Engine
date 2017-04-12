#pragma once

#include "GameObject.h"

namespace GlEngine
{
    class PointLightSource;
    class Material;
}

namespace GlEngine::ShaderFactory
{
    class IPropertyProvider;
}

typedef std::vector<GlEngine::ShaderFactory::IPropertyProvider*> ProviderList;

class OrbitingLight : public GlEngine::GameComponent
{
public:
    OrbitingLight(GlEngine::PointLightSource *lightSource, float distance, Vector<3> rotationAxis);
    ~OrbitingLight();

    static GlEngine::GameObject *Create(GlEngine::Frame *frame, std::string name, Vector<3> color, Vector<3> reflectionCoef, GlEngine::PointLightSource *lightSource, ProviderList providers = {}, float distance = 3.f, float rotationSpeed = .5f);
    static GlEngine::GameObject *Create(GlEngine::Frame *frame, std::string name, Vector<3> color, Vector<3> reflectionCoef, GlEngine::PointLightSource *lightSource, Vector<3> rotationAxis, ProviderList providers = {}, float distance = 3.f, float rotationSpeed = .5f);
    static GlEngine::GameObject *Create(GlEngine::Frame *frame, std::string name, Vector<3> color, Vector<3> reflectionCoef, std::string modelPath, GlEngine::PointLightSource *lightSource, ProviderList providers = {}, float distance = 3.f, float rotationSpeed = .5f);
    static GlEngine::GameObject *Create(GlEngine::Frame *frame, std::string name, Vector<3> color, Vector<3> reflectionCoef, std::string modelPath, GlEngine::PointLightSource *lightSource, Vector<3> rotationAxis, ProviderList providers = {}, float distance = 3.f, float rotationSpeed = .5f);
    static GlEngine::GameObject *Create(GlEngine::Frame *frame, std::string name, GlEngine::Material *mat, GlEngine::PointLightSource *lightSource, ProviderList providers = {}, float distance = 3.f, float rotationSpeed = .5f);
    static GlEngine::GameObject *Create(GlEngine::Frame *frame, std::string name, GlEngine::Material *mat, GlEngine::PointLightSource *lightSource, Vector<3> rotationAxis, ProviderList providers = {}, float distance = 3.f, float rotationSpeed = .5f);
    static GlEngine::GameObject *Create(GlEngine::Frame *frame, std::string name, GlEngine::Material *mat, std::string modelPath, GlEngine::PointLightSource *lightSource, ProviderList providers = {}, float distance = 3.f, float rotationSpeed = .5f);
    static GlEngine::GameObject *Create(GlEngine::Frame *frame, std::string name, GlEngine::Material *mat, std::string modelPath, GlEngine::PointLightSource *lightSource, Vector<3> rotationAxis, ProviderList providers = {}, float distance = 3.f, float rotationSpeed = .5f);

public:
    virtual bool InitializeAsync() override;

    virtual void Tick(float delta) override;

private:
    GlEngine::PointLightSource *_lightSource;
    Vector<3> rotationAxis;
    float distance;
};

class PivotComponent : public GlEngine::GameComponent
{
public:
    PivotComponent(Vector<3> rotationAxis, float rotationSpeed);
    ~PivotComponent();

    virtual void Tick(float delta) override;

    Vector<3> rotationAxis;
    float rotationSpeed, totalDelta;
};
