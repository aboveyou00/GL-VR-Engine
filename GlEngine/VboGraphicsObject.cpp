#include "stdafx.h"
#include "VboGraphicsObject.h"

#include "OpenGl.h"
#include "VboFactory.h"

namespace GlEngine
{
    VboGraphicsObject::VboGraphicsObject(std::string name, CreateFactoryFn createFactory)
        : VboGraphicsObject(name, VaObject(), createFactory)
    {
    }
    VboGraphicsObject::VboGraphicsObject(std::string name, VaObject vao, CreateFactoryFn createFactory)
        : PosUvNormFactory(
            name,
            vao,
            vao.isReady() ? nullptr : PosUvNormFactory::TFactory::CreateArray(&ShaderFactory::prop_Position, &ShaderFactory::prop_UV, &ShaderFactory::prop_Normal),
            vao.isReady() ? nullptr : PosUvNormFactory::TFacesFactory::CreateElementArray(),
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
