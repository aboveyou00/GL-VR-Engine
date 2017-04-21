#pragma once

#include "VboGraphicsObject.h"
#include "ObjGraphicsObject.h"
#include <fstream>
#include <vector>
#include <unordered_map>
#include "Vector.h"
#include <array>
#include "MeshComponent.h"
#include "ObjLoaderFlag.h"
#include "MeshFaces.h"
#include "MtlLibMtl.h"

namespace GlEngine
{
    class ENGINE_SHARED ObjLoader : public GameComponent
    {
    public:
        ObjLoader(std::string filename, std::vector<ShaderFactory::IPropertyProvider*> providers, ObjLoaderFlag flags = ObjLoaderFlag::None);
        ObjLoader(std::string filename, std::vector<ShaderFactory::IPropertyProvider*> providers, CreateFactoryFn factory, ObjLoaderFlag flags = ObjLoaderFlag::None);
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

        CreateFactoryFn _createFactory;

        ObjLoaderFlag _flags;
        MeshComponent* _mesh;
        Material* _material;
        GraphicsObject* _graphicsObject;

        std::string _filename, _basePath;
        std::istream* stream;

        std::vector<Vector<3>> positions;
        std::vector<Vector<3>> normals;
        std::vector<Vector<2>> texCoords;
        
        //std::vector<std::tuple<Vector<3>, Vector<2>, Vector<3>>> glVertices;
        std::vector<Vector<3>> *glPositions;
        std::vector<Vector<3>> *glNormals;
        std::vector<Vector<2>> *glTexCoords;

        MtlNameMap *materials;
        MtlFacesMap *faces;
        MeshFaces *_getFaces(std::string name);
        MeshFaces *_getFaces(Material *mat);

        bool _LoadMesh();
        int ParseVertex(std::string faceString);
        //int ObjLoader::FindOrAddGlVertex(Vector<3> position, Vector<2> texCoord, Vector<3> normal);
        bool CreateMeshFromData();

        MtlNameMap *_LoadMtllib(std::string mtllib);
        MtlNameMap *_ParseMtllib(std::istream *stream);
    };
}
