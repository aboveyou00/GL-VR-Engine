#pragma once

namespace GlEngine
{
	namespace ShaderFactory
	{
		class ENGINE_SHARED Property
		{
		public:
			Property(std::string name, std::string datatype, int arraylength = -1);
			~Property();

			std::string name;
			std::string datatype;
			int arraylength;

			std::string	DeclerationString(std::string prefix = "");
		};

		extern ENGINE_SHARED Property propColor("color", "vec4");
		
		extern ENGINE_SHARED Property propPosition("position", "vec4");
		extern ENGINE_SHARED Property propNormal("normal", "vec4");
		extern ENGINE_SHARED Property propUV("uv", "vec4");

		extern ENGINE_SHARED Property propLightColor("light_color", "vec4");
	}
}