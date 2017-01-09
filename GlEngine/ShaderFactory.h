#pragma once

#include "IGraphicsComponent.h"
#include "Property.h"
#include "Program.h"
#include "PropertyType_attribs.h"

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

            template <typename T>
            void ProvideProperty(Property<T> &prop, const T &val)
            {
                assert(!!this);
                auto uniformLocation = _program->FindUniform(&prop);
                if (uniformLocation != -1) PropertyType_attribs<T>::set_gl_uniform(uniformLocation, val);
            }

            virtual operator bool() override;
            
            virtual const char *name() override;
            
        private:
            Material *_mat;
            Program *_program;
            Shader *_shader;
        };
    }
}
