#pragma once

#include "ShaderGraphicsObject.h"
#include "VbObject.h"

namespace GlEngine
{
    template <VboType type, typename... TArgs>
    class VboFactory;

	class ENGINE_SHARED VboGraphicsObject : public GraphicsObject
	{
	public:
		VboGraphicsObject();
		VboGraphicsObject(VbObject arrayVbo, VbObject elementVbo);
		VboGraphicsObject(VbObject arrayVbo, VbObject elementVbo, Shader shader);
		~VboGraphicsObject();

        //TODO: Make this class immutable, or at least encapsulate these fields:
        VboFactory<VboType::Float, Vector<3>, Vector<2>, Vector<3>> *verticesFactory;
        VboFactory<VboType::UnsignedShort, Vector<3, uint16_t>> *trianglesFactory;
		VbObject arrayVbo, elementVbo;
		Shader shader;

		int triCount;
		int quadCount;

		bool Initialize() override;
		void Shutdown() override;
        bool InitializeGraphics() override;
        void ShutdownGraphics() override;

		void PreRender() override;
		void Render() override;

        operator bool() override;
	};
}
