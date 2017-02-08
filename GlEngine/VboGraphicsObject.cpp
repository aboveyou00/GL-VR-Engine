#include "stdafx.h"
#include "VboGraphicsObject.h"

#include "OpenGl.h"
#include "VboFactory.h"

namespace GlEngine
{
    VboGraphicsObject::VboGraphicsObject(CreateFactoryFn createFactory)
        : VboGraphicsObject(VaObject(), createFactory)
    {
    }
    VboGraphicsObject::VboGraphicsObject(VaObject vao, CreateFactoryFn createFactory)
        : PosUvNormFactory(
            vao,
            !!vao ? nullptr : new PosUvNormFactory::TFactory(BufferMode::Array),
            !!vao ? nullptr : new PosUvNormFactory::TFacesFactory(BufferMode::ElementArray),
            createFactory
          )
    {
    }
    VboGraphicsObject::~VboGraphicsObject()
    {
    }

    int VboGraphicsObject::AddVertex(Vector<3> position, Vector<2> texCoord, Vector<3> normal)
    {
        return PosUvNormFactory::AddVertex(position, texCoord, normal);
    }
}
