#include "stdafx.h"
#include "LineSegmentGraphicsObject.h"
#include "LineSegmentMaterial.h"

namespace GlEngine
{
    LineSegmentGraphicsObject::LineSegmentGraphicsObject(std::string name, CreateFactoryFn createFactory, bool is2d)
        : LineSegmentGraphicsObject(name, VaObject(), createFactory, is2d)
    {
    }
    LineSegmentGraphicsObject::LineSegmentGraphicsObject(std::string name, VaObject vao, CreateFactoryFn createFactory, bool is2d)
        : PosColorFactory(
            name,
            vao,
            vao.isReady() ? nullptr : PosColorFactory::TFactory::CreateArray(&ShaderFactory::prop_Position, &ShaderFactory::prop_BaseColor),
            vao.isReady() ? nullptr : PosColorFactory::TFacesFactory::CreateElementArray(),
            createFactory
        )
    {
        SetMaterial(new LineSegmentMaterial(is2d));
    }
    LineSegmentGraphicsObject::~LineSegmentGraphicsObject()
    {
    }

    int LineSegmentGraphicsObject::AddVertex(Vector<3> position, Vector<3> color)
    {
        return AddVertex(position, Vector<4> { color[0], color[1], color[2], 1.f });
    }
    int LineSegmentGraphicsObject::AddVertex(Vector<3> position, Vector<4> color)
    {
        return PosColorFactory::AddVertex(position, color);
    }
}
