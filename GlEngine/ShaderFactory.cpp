#include "stdafx.h"

#include "ShaderFactory.h"
#include "PathUtils.h"
#include "LogUtils.h"

#include "Program.h"
#include "VboPropertySource.h"
#include "UniformPropertySource.h"
#include "Material.h"

#include "Shader.h"

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

            Program prog(false, false);

            prog.AddPropertySource(new VboPropertySource(&prop_Position, &prop_Normal, &prop_UV));

            prog.AddPropertySource(new UniformPropertySource(mat->properties()));

            for (auto *attr : mat->attributes())
                prog.AddAttribute(attr);
            auto *source = prog.Compile();

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

            /* Use environment here */

            //MatrixStack::Projection.tell_gl();
            //MatrixStack::ModelView.tell_gl();

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
