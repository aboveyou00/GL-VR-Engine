#include "stdafx.h"
#include "Environment.h"
#include "TimeUtils.h"
#include "Property.h"
#include "MatrixStack.h"
#include "ShaderFactory.h"

namespace GlEngine::ShaderFactory
{
    Environment::Environment()
        : _cameraPos(_cameraPos)
    {
    }
    Environment::~Environment()
    {
    }

    Environment &Environment::GetInstance()
    {
        static Environment _instance;
        return _instance;
    }

    std::vector<ShaderProp*> Environment::properties()
    {
        return {
            &prop_ModelMatrix,
            &prop_ViewMatrix,
            &prop_ProjectionMatrix,
#ifdef _DEBUG
            &prop_ModelViewMatrix,
            &prop_ModelViewProjectionMatrix,
#endif
            &prop_CameraPosition,
            &prop_GameTime
        };
    }
    void Environment::Push(ShaderFactory &factory)
    {
        factory.ProvideProperty(prop_ModelMatrix, MatrixStack::Model.head());
        factory.ProvideProperty(prop_ViewMatrix, MatrixStack::View.head());
        factory.ProvideProperty(prop_ProjectionMatrix, MatrixStack::Projection.head());
#ifdef _DEBUG
        auto modelView = MatrixStack::View.head() * MatrixStack::Model.head();
        factory.ProvideProperty(prop_ModelViewMatrix, modelView);
        factory.ProvideProperty(prop_ModelViewProjectionMatrix, MatrixStack::Projection.head() * modelView);
#endif
        factory.ProvideProperty(prop_CameraPosition, _cameraPos);
        factory.ProvideProperty(prop_GameTime, GetGameTime());
    }

    float Environment::GetGameTime()
    {
        return Util::getGameMillis() / 1000.0f;
    }

    void Environment::SetCameraPosition(Vector<3> position)
    {
        _cameraPos = position;
    }
    Vector<3> Environment::cameraPosition() const
    {
        return _cameraPos;
    }
}
