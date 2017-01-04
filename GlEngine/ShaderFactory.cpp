#include "stdafx.h"

//#include "ShaderFactory.h"
//#include "PathUtils.h"
//#include "LogUtils.h"
//
//namespace GlEngine
//{
//    Shader ShaderFactory::Build(ShaderAttribs attribs, std::string vertexSource, std::string fragmentSource, std::string tessControlSource, std::string tessEvaluationSource, std::string geometrySource)
//    {
//        Clear();
//        SetupLayouts(attribs);
//
//        if (vertexSource == "")
//            vertexSource = ShaderFactory::BuildVertex(attribs);
//        if (fragmentSource == "")
//            fragmentSource = ShaderFactory::BuildFragment(attribs);
//        if (tessControlSource == "")
//            tessControlSource = ShaderFactory::BuildTessControl(attribs);
//        if (tessEvaluationSource == "")
//            tessEvaluationSource = ShaderFactory::BuildTessEvaluation(attribs);
//        if (geometrySource == "")
//            geometrySource = ShaderFactory::BuildGeometry(attribs);
//
//        return Shader(vertexSource, fragmentSource, tessControlSource, tessEvaluationSource, geometrySource);
//    }
//
//    void ShaderFactory::Clear()
//    {
//        uniformLayoutsCount = 0;
//        inLayoutsCount = 0;
//        vertexOutLayoutsCount = 0;
//        tesscOutLayoutsCount = 0;
//        tesseOutLayoutsCount = 0;
//        geometryOutLayoutsCount = 0;
//        fragmentOutLayoutsCount = 0;
//    }
//
//    void ShaderFactory::SetupLayouts(ShaderAttribs attribs)
//    {
//        for (unsigned type = (unsigned)std::numeric_limits<ShaderAttribType>::min(); type < (unsigned)std::numeric_limits<ShaderAttribType>::max(); type++)
//        {
//            if (attribs[type].cls == ShaderAttribClass::Uniform)
//                uniformLayouts[uniformLayoutsCount++] = attribs[type];
//            else if (attribs[type].cls == ShaderAttribClass::Buffered)
//                inLayouts[inLayoutsCount++] = attribs[type];
//        }
//
//        for (unsigned i = 0; i < inLayoutsCount; i++)
//        {
//            vertexOutLayouts[vertexOutLayoutsCount++] = inLayouts[i];
//        }
//        for (unsigned i = 0; i < vertexOutLayoutsCount; i++)
//        {
//            tesscOutLayouts[tesscOutLayoutsCount++] = vertexOutLayouts[i];
//        }
//        for (unsigned i = 0; i < tesscOutLayoutsCount; i++)
//        {
//            // TODO: preraster to postraster
//        }
//        fragmentOutLayouts[fragmentOutLayoutsCount++] = { ShaderAttribClass::Buffered, ShaderAttribType::color };
//    }
//
//    std::string ShaderFactory::BuildLayouts(ShaderAttrib * uniformLayouts, unsigned uniformLayoutsCount, ShaderAttrib * inLayouts, unsigned inLayoutsCount, ShaderAttrib * outLayouts, unsigned outLayoutsCount)
//    {
//        std::string result = "";
//        for (int i = 0; i < uniformLayoutsCount; i++)
//        {
//            result += sprintf("layout(location = %d) uniform %s %s;\n");
//        }
//    }
//
//    std::string ShaderFactory::BuildVertex(ShaderAttribs attribs)
//    {
//
//    }
//
//    std::string ShaderFactory::BuildFragment(ShaderAttribs attribs)
//    {
//        return std::string();
//    }
//
//    std::string ShaderFactory::BuildTessControl(ShaderAttribs attribs)
//    {
//        return std::string();
//    }
//
//    std::string ShaderFactory::BuildTessEvaluation(ShaderAttribs attribs)
//    {
//        return std::string();
//    }
//
//    std::string ShaderFactory::BuildGeometry(ShaderAttribs attribs)
//    {
//        return std::string();
//    }
//
//    std::string ShaderFactory::LoadShaderSource(const const char * path, const char * const name, const char *suffix, bool required)
//    {
//        static const int NAME_BUFFER_SIZE = 64;
//        static thread_local char nameBuff[NAME_BUFFER_SIZE];
//        sprintf_s(nameBuff, "%s.%s.shader", name, suffix);
//        auto fullPath = Util::combinePath(path, nameBuff);
//
//        std::ifstream file(fullPath, std::ios::in | std::ifstream::ate | std::ifstream::binary);
//        if (file.fail() || !file)
//        {
//            if (required)
//            {
//                auto &logger = *GlEngine::Engine::GetInstance().GetServiceProvider().GetService<GlEngine::ILogger>();
//                logger.Log(LogType::Warning, "Could not open shader file [%s]", fullPath);
//            }
//            return false;
//        }
//
//        auto len = (int)file.tellg();
//        file.seekg(0);
//
//        char *buff = new char[len + 1];
//        file.read(buff, len);
//        buff[len] = '\0';
//        return std::string(buff);
//    }
//}