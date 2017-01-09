#pragma once

#include "IGraphicsComponent.h"

namespace GlEngine
{
    class Material;

    namespace ShaderFactory
    {
        class Shader;

        class ENGINE_SHARED ShaderFactory : public IGraphicsComponent
        {
        public:
            ShaderFactory();
            ~ShaderFactory();

            Material *material();
            void SetMaterial(Material *mat);

            virtual bool Initialize() override;
            virtual void Shutdown() override;

            virtual bool InitializeGraphics() override;
            virtual void ShutdownGraphics() override;

            void Push();
            void Pop();

            virtual operator bool() override;
            
            virtual const char *name() override;
            
        private:
            Material *_mat;
            Shader *_shader;
        };
    }
}
