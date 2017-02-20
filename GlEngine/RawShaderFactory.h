#pragma once

#include "ShaderFactory.h"
#include "Shader.h"

namespace GlEngine::ShaderFactory
{
    class ENGINE_SHARED RawShaderFactory : public ShaderFactory
    {
    public:
        RawShaderFactory(ShaderSource* shaderSource, std::map<size_t, ShaderProp*>* uniforms = nullptr);
        ~RawShaderFactory();

        virtual bool InitializeAsync() override;
        virtual void ShutdownAsync() override;

        virtual bool InitializeGraphics() override;
        virtual void ShutdownGraphics() override;

        virtual void Recompile() override;

        virtual std::string name() override;

    private:
        ShaderSource* _shaderSource;
        std::map<size_t, ShaderProp*>* uniforms;
    };
}
