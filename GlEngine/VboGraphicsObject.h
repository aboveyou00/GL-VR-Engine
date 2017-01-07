#pragma once

#include "GraphicsObject.h"
#include "VaObject.h"
#include "RenderTargetLayer.h"

namespace GlEngine
{
    template <VboType type, typename... TArgs>
    class VboFactory;
    class Material;

    namespace Impl
    {
        class VboGraphicsSection;
    }

    class ENGINE_SHARED VboGraphicsObject : public GraphicsObject
    {
    public:
        VboGraphicsObject();
        VboGraphicsObject(VaObject vao);
        ~VboGraphicsObject();

        void SetMaterial(Material *material);
        int AddVertex(Vector<3> position, Vector<2> texCoord, Vector<3> normal);
        inline void AddTriangle(unsigned idx0, unsigned idx1, unsigned idx2)
        {
            AddTriangle({ idx0, idx1, idx2 });
        }
        inline void AddQuad(unsigned idx0, unsigned idx1, unsigned idx2, unsigned idx3)
        {
            AddQuad({ idx0, idx1, idx2, idx3 });
        }
        void AddTriangle(Vector<3, uint16_t> indices);
        void AddQuad(Vector<4, uint16_t> indices);

        bool Initialize() override;
        void Shutdown() override;
        bool InitializeGraphics() override;
        void ShutdownGraphics() override;

        const char *name() override;

        void BuildVao(VaoFactory &vao) override;

        void PreRender(RenderTargetLayer layer) override;
        void RenderImpl(RenderTargetLayer layer) override;

        void RenderInstancedImpl(RenderTargetLayer layer, unsigned instanceCount) override;

        operator bool() override;

    protected:
        bool finalized;
        rt_mutex mutex;

    private:
        VaObject _vao;
        std::vector<Impl::VboGraphicsSection*> graphicsSections;

        Impl::VboGraphicsSection *currentGraphicsSection;
        int elemIdx;
        VboFactory<VboType::Float, Vector<3>, Vector<2>, Vector<3>> *verticesFactory;
        VboFactory<VboType::UnsignedShort, uint16_t> *facesFactory;
    };
}
