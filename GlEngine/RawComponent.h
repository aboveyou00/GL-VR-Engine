#pragma once

#include "Component.h"

namespace GlEngine
{
	namespace ShaderFactory
	{
		class RawComponent : public Component
		{
		public:
			RawComponent(std::string source);
			~RawComponent();

			virtual std::string Compile() override;

		private:
			std::string source;
		};
	}
}