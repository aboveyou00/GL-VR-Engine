#pragma once

#include "VboGraphicsObject.h"
#include "Mesh.h"

namespace GlEngine
{
    namespace ShaderFactory
    {
        class IPropertyProvider;
    }

    class ENGINE_SHARED ObjGraphicsObject : public VboGraphicsObject
    {
    public:
        ObjGraphicsObject(std::string name, std::string filename, std::function<ShaderFactory::ShaderFactory*(Material*)> createFactory = [](Material*) { return nullptr; });

        static ObjGraphicsObject *Create(std::string name, std::string filename, Material *mat, std::vector<ShaderFactory::IPropertyProvider*> providers);

        virtual bool InitializeAsync() override;

        virtual int AddVertex(Vector<3> position, Vector<2> texCoord, Vector<3> normal) override;
        virtual void AddTriangle(Vector<3, uint_16t> vertices) override;

    private:
        std::string filename;
        Mesh* mesh;
    };
}
