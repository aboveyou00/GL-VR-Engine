#pragma once
#include "VboFactoryGraphicsObject.h"

namespace GlEngine
{
    typedef VboFactoryGraphicsObject<VboType::Float, Vector<3>, Vector<4>> PosColorFactory;

    class ENGINE_SHARED LineSegmentGraphicsObject : public PosColorFactory
    {
    public:
        LineSegmentGraphicsObject(std::string name, CreateFactoryFn createFactory, bool is2d = false);
        LineSegmentGraphicsObject(std::string name, VaObject vao, CreateFactoryFn createFactory, bool is2d = false);
        ~LineSegmentGraphicsObject();

        virtual int AddVertex(Vector<3> position, Vector<3> color);
        virtual int AddVertex(Vector<3> position, Vector<4> color) override;
    };
}
