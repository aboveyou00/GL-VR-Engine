#include "stdafx.h"

#include "ShaderFactory.h"
#include "PathUtils.h"
#include "LogUtils.h"

#include "Program.h"
#include "VboPropertySource.h"
#include "UniformPropertySource.h"
#include "Material.h"

#include "Shader.h"
#include "Property.h"
#include "MatrixStack.h"

namespace GlEngine
{
    namespace ShaderFactory
    {
        ShaderFactory::ShaderFactory()
            : _mat(nullptr), _shader(nullptr)
        {
        }
        ShaderFactory::~ShaderFactory()
        {
            Shutdown();
        }

        Material *ShaderFactory::material()
        {
            return _mat;
        }
        void ShaderFactory::SetMaterial(Material *mat)
        {
            if (mat == this->_mat) return;

            this->_mat = mat;
            this->_program = nullptr;
            this->_shader = nullptr;
            if (mat == nullptr) return;

            this->_program = new Program(false, false);

            this->_program->AddPropertySource(new VboPropertySource(&prop_Position, &prop_UV, &prop_Normal));

            this->_program->AddPropertySource(new UniformPropertySource(mat->properties()));

            for (auto *attr : mat->attributes())
                this->_program->AddAttribute(attr);
            auto *source = this->_program->Compile();

            this->_shader = Shader::Create(source);
        }

        bool ShaderFactory::Initialize()
        {
            return true;
        }
        void ShaderFactory::Shutdown()
        {
        }
        bool ShaderFactory::InitializeGraphics()
        {
            return true;
        }
        void ShaderFactory::ShutdownGraphics()
        {
        }

        void ShaderFactory::Push()
        {
            assert(!!*this);
            _shader->Push();

            ProvideProperty(prop_ModelMatrix, MatrixStack::Model.head());
            ProvideProperty(prop_ViewMatrix, MatrixStack::View.head());
            ProvideProperty(prop_ProjectionMatrix, MatrixStack::Projection.head());

            _mat->Push(*this);

            /* Use environment here */

            //ProvideProperty(prop_DiffuseLightDirection, {0, 0, 1.0} );
            ProvideProperty(prop_DiffuseLightPosition, { 0.0, 0.0, 10.0 });
            ProvideProperty(prop_DiffuseLightColor, { 1.0, 1.0, 1.0 });

            //Vector<3> lightDir = { 1, 1.5, 1 };
            //lightDir = lightDir.Normalized();
            //glUniform3f(2, lightDir[0], lightDir[1], lightDir[2]);
            //glUniform3f(3, .4f, .6f, 1.f);
            //glUniform3f(4, .4f, .4f, .4f);

            //theta += .01f;
            //glUniform1f(6, theta);
        }
        void ShaderFactory::Pop()
        {
            if (_shader != nullptr) _shader->Pop();
        }

        ShaderFactory::operator bool()
        {
            return _shader != nullptr && !!*_shader;
        }

        const char *ShaderFactory::name()
        {
            return "ShaderFactory";
        }
    }
}
