#pragma once

#include "Shader.h"

namespace GlEngine
{
	static const unsigned glsl_version = 430;

	class ShaderFactory
	{
	public:
		static ShaderFactory Build(ShaderAttribs attribs, std::string vertexSource = "", std::string fragmentSource = "", std::string tessControlSource = "", std::string tessEvaluationSource = "", std::string geometrySource = "");

	private:
		static const int maxLayouts = 32;
		
		static ShaderAttrib uniformLayouts[maxLayouts], inLayouts[maxLayouts], vertexOutLayouts[maxLayouts], tesscOutLayouts[maxLayouts], tesseOutLayouts[maxLayouts], geometryOutLayouts[maxLayouts], fragmentOutLayouts[maxLayouts];
		static unsigned uniformLayoutsCount, inLayoutsCount, vertexOutLayoutsCount, tesscOutLayoutsCount, tesseOutLayoutsCount, geometryOutLayoutsCount, fragmentOutLayoutsCount;

		static void SetupLayouts(ShaderAttribs attribs);
		
		static std::string BuildLayouts(ShaderAttrib * uniformLayouts, unsigned uniformLayoutsCount, ShaderAttrib * inLayouts, unsigned inLayoutsCount, ShaderAttrib * outLayouts, unsigned outLayoutsCount);

		static std::string BuildVertex(ShaderAttribs attribs);
		static std::string BuildFragment(ShaderAttribs attribs);
		static std::string BuildTessControl(ShaderAttribs attribs);
		static std::string BuildTessEvaluation(ShaderAttribs attribs);
		static std::string BuildGeometry(ShaderAttribs attribs);

		static std::string LoadShaderSource(const const char * path, const char * const name, const char *suffix, bool required);
		static void Clear();
	};
}