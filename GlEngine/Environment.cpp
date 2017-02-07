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
        auto modelView = MatrixStack::Model.head() * MatrixStack::View.head();
        factory.ProvideProperty(prop_ModelViewMatrix, modelView);
        factory.ProvideProperty(prop_ModelViewProjectionMatrix, modelView * MatrixStack::Projection.head());
#endif
        factory.ProvideProperty(prop_CameraPosition, _cameraPos);
        factory.ProvideProperty(prop_GameTime, GetGameTime());

        factory.ProvideProperty(prop_MouseClipPosition, mouseClipPosition());
        factory.ProvideProperty(prop_MouseScreenPosition, _mouseScreenPosition);
        factory.ProvideProperty(prop_ScreenDimensions, _screenDimensions);
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
    void Environment::SetScreenDimensions(Vector<2> dimensions)
    {
        _screenDimensions = dimensions;
    }
    Vector<2> Environment::screenDimensions()
    {
        return _screenDimensions;
    }
    void Environment::SetMouseScreenPosition(Vector<2> position)
    {
        _mouseScreenPosition = position;
    }
    Vector<2> Environment::mouseScreenPosition()
    {
        return _mouseScreenPosition;
    }
    void Environment::SetMouseClipPosition(Vector<2> position)
    {
        _mouseScreenPosition = { _screenDimensions[0] * (position[0] + 1.0) / 2.0, _screenDimensions[1] * (position[1] + 1.0) / 2.0 };
    }
    Vector<2> Environment::mouseClipPosition()
    {
        return { 2.0 * _mouseScreenPosition[0] / _screenDimensions[0] - 1.0, -2.0 * _mouseScreenPosition[1] / _screenDimensions[1] + 1.0 };
    }
}
