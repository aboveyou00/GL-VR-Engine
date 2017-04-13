#pragma once

#include "VboGraphicsObject.h"
#include "ObjGraphicsObject.h"
#include <fstream>
#include <vector>
#include <unordered_map>
#include "Vector.h"
#include <array>
#include "MeshComponent.h"

namespace GlEngine
{
    enum class ENGINE_SHARED ObjLoaderFlag
    {
        None        = 0b0000,
        Mesh        = 0b0001,
        Material    = 0b0010,
        Graphics    = 0b0100
    };

    class ENGINE_SHARED ObjLoader : public GameComponent
    {
    public:
        ObjLoader(std::string filename, std::vector<ShaderFactory::IPropertyProvider*> providers, ObjLoaderFlag flags = ObjLoaderFlag::None);
        ObjLoader(std::istream& in);
        ~ObjLoader();

        std::string filename();

        bool LoadMesh();
        bool LoadGraphics();

        MeshComponent* mesh();
        Material* material();
        GraphicsObject* graphicsObject();

        ObjLoaderFlag flags();
        void SetFlags(ObjLoaderFlag flags);

        void OverrideMesh(MeshComponent* mesh);
        void OverrideMaterial(Material* materail);

        //static bool Load(std::string filename, ObjGraphicsObject *out);
        //static bool Load(std::istream &in, ObjGraphicsObject *out);

        virtual bool InitializeAsync() override;

    private:
        std::vector<ShaderFactory::IPropertyProvider*> providers;

        ObjLoaderFlag _flags;
        MeshComponent* _mesh;
        Material* _material;
        GraphicsObject* _graphicsObject;

        std::string _filename;
        std::istream* stream;

        std::vector<Vector<3>> positions;
        std::vector<Vector<3>> normals;
        std::vector<Vector<2>> texCoords;
        
        //std::vector<std::tuple<Vector<3>, Vector<2>, Vector<3>>> glVertices;
        std::vector<Vector<3>> glPositions;
        std::vector<Vector<3>> glNormals;
        std::vector<Vector<2>> glTexCoords;

        std::vector<Vector<3, unsigned>> triangleIndices;
        std::vector<Vector<4, unsigned>> quadIndices;

        bool _LoadMesh();
        int ParseVertex(std::string faceString);
        //int ObjLoader::FindOrAddGlVertex(Vector<3> position, Vector<2> texCoord, Vector<3> normal);
        bool CreateMeshFromData();
    };
}
