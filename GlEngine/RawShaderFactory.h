#pragma once

#include "ShaderFactory.h"
#include "IGraphicsComponent.h"
#include "Shader.h"

namespace GlEngine::ShaderFactory
{
    class ENGINE_SHARED RawShaderFactory : public ShaderFactory
    {
    public:
        RawShaderFactory(ShaderSource* shaderSource, std::map<size_t, ShaderProp*>* uniforms = nullptr);
        ~RawShaderFactory();

        virtual bool Initialize() override;
        virtual void Shutdown() override;

        virtual bool InitializeGraphics() override;
        virtual void ShutdownGraphics() override;

        virtual void Recompile() override;

        virtual std::string name() override;

    private:
        ShaderSource* _shaderSource;
        std::map<size_t, ShaderProp*>* uniforms;
    };
}
