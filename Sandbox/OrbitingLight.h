#pragma once

#include "GameObject.h"

namespace GlEngine
{
    class PointLightSource;
    class Material;
}

class OrbitingLight : public GlEngine::GameComponent
{
public:
    OrbitingLight(GlEngine::PointLightSource *lightSource, Vector<3> rotationAxis, float distance, float rotationSpeed);
    ~OrbitingLight();

    static GlEngine::GameObject *Create(GlEngine::Frame *frame, std::string name, Vector<3> color, Vector<3> reflectionCoef, GlEngine::PointLightSource *lightSource, float distance = 3.f, float rotationSpeed = .5f);
    static GlEngine::GameObject *Create(GlEngine::Frame *frame, std::string name, Vector<3> color, Vector<3> reflectionCoef, GlEngine::PointLightSource *lightSource, Vector<3> rotationAxis, float distance = 3.f, float rotationSpeed = .5f);
    static GlEngine::GameObject *Create(GlEngine::Frame *frame, std::string name, Vector<3> color, Vector<3> reflectionCoef, std::string modelPath, GlEngine::PointLightSource *lightSource, float distance = 3.f, float rotationSpeed = .5f);
    static GlEngine::GameObject *Create(GlEngine::Frame *frame, std::string name, Vector<3> color, Vector<3> reflectionCoef, std::string modelPath, GlEngine::PointLightSource *lightSource, Vector<3> rotationAxis, float distance = 3.f, float rotationSpeed = .5f);
    static GlEngine::GameObject *Create(GlEngine::Frame *frame, std::string name, GlEngine::Material *mat, GlEngine::PointLightSource *lightSource, float distance = 3.f, float rotationSpeed = .5f);
    static GlEngine::GameObject *Create(GlEngine::Frame *frame, std::string name, GlEngine::Material *mat, GlEngine::PointLightSource *lightSource, Vector<3> rotationAxis, float distance = 3.f, float rotationSpeed = .5f);
    static GlEngine::GameObject *Create(GlEngine::Frame *frame, std::string name, GlEngine::Material *mat, std::string modelPath, GlEngine::PointLightSource *lightSource, float distance = 3.f, float rotationSpeed = .5f);
    static GlEngine::GameObject *Create(GlEngine::Frame *frame, std::string name, GlEngine::Material *mat, std::string modelPath, GlEngine::PointLightSource *lightSource, Vector<3> rotationAxis, float distance = 3.f, float rotationSpeed = .5f);

public:
    virtual bool InitializeAsync() override;

    virtual void Tick(float delta) override;

private:
    GlEngine::PointLightSource *_lightSource;

    Vector<3> rotationAxis;
    float distance, totalDelta, rotationSpeed;

    static Vector<3> randomRotateAxis();
};
