#pragma once

#include "GraphicsObject.h"
#include "VaObject.h"
#include "RenderTargetLayer.h"
#include "VboFactoryGraphicsObject.h"

namespace GlEngine
{
    typedef VboFactoryGraphicsObject<VboType::Float, Vector<3>, Vector<2>, Vector<3>> PosUvNormFactory;

    class ENGINE_SHARED VboGraphicsObject : public PosUvNormFactory
    {
    public:
        VboGraphicsObject(CreateFactoryFn createFactory = [](Material*) { return nullptr; });
        VboGraphicsObject(VaObject vao, CreateFactoryFn createFactory = [](Material*) { return nullptr; });
        ~VboGraphicsObject();

        virtual int AddVertex(Vector<3> position, Vector<2> texCoord, Vector<3> normal) override;
    };
}
