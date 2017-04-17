#include "stdafx.h"
#include "ObjLoader.h"

#include <sstream>
#include <algorithm>
#include "StringUtils.h"
#include "ObjGraphicsObject.h"
#include "VboFactory.h"
#include "GameObject.h"
#include "MeshMaterialGraphicsObject.h"

namespace GlEngine
{
    ObjLoader::ObjLoader(std::string filename, std::vector<ShaderFactory::IPropertyProvider*> providers, ObjLoaderFlag flags)
        : ObjLoader(filename, providers, [](Material*) { return nullptr; }, flags)
    {
    }
    ObjLoader::ObjLoader(std::string filename, std::vector<ShaderFactory::IPropertyProvider*> providers, CreateFactoryFn createFactory, ObjLoaderFlag flags)
        : GameComponent("ObjLoader"), providers(providers), _flags(flags), _filename(filename), stream(nullptr), _mesh(nullptr), _material(nullptr), _graphicsObject(nullptr), _createFactory(createFactory)
    {
        glPositions = new std::vector<Vector<3>>();
        glNormals = new std::vector<Vector<3>>();
        glTexCoords = new std::vector<Vector<2>>();

        triangleIndices = new std::vector<Vector<3, unsigned>>();
        quadIndices = new std::vector<Vector<4, unsigned>>();
    }
    ObjLoader::ObjLoader(std::istream& in)
        : GameComponent("ObjLoader"), _filename(""), stream(&in)
    {
    }
    ObjLoader::~ObjLoader()
    {
    }

    std::string ObjLoader::filename()
    {
        return _filename;
    }

    bool ObjLoader::LoadMesh()
    {
        if (_mesh) return true;

        //TODO: cache mesh

        if (stream == nullptr)
        {
            std::ifstream in;
            in.open(filename());
            if (!in)
                return false;
            stream = &in;
            auto worked = _LoadMesh();
            in.close();
            return worked;
        }
        else
        {
            return !_LoadMesh();
        }
    }

    MeshComponent * ObjLoader::mesh()
    {
        return _mesh;
    }

    Material * ObjLoader::material()
    {
        return _material;
    }

    GraphicsObject * ObjLoader::graphicsObject()
    {
        return _graphicsObject;
    }

    ObjLoaderFlag ObjLoader::flags()
    {
        return _flags;
    }

    void ObjLoader::SetFlags(ObjLoaderFlag flags)
    {
        _flags = flags;
        // TODO: requeue if necessary? prevent changing flags after load?
    }

    void ObjLoader::OverrideMesh(MeshComponent* mesh)
    {
        _mesh = mesh;
    }

    void ObjLoader::OverrideMaterial(Material* material)
    {
        _material = material;
    }

    bool ObjLoader::InitializeAsync()
    {
        if ((unsigned)_flags & (unsigned)ObjLoaderFlag::Graphics)
        {
            return LoadGraphics();
        }
        if ((unsigned)_flags & (unsigned)ObjLoaderFlag::Mesh && !LoadMesh())
        {
            return false;
        }
        //if ((unsigned)_flags & (unsigned)ObjLoaderFlag::Material && !LoadMaterial())
        //{
        //    return false;
        //}
        return true;
    }

    bool ObjLoader::LoadGraphics()
    {
        if (_graphicsObject) return true;

        if (!LoadMesh())
            return false;
        //if (!LoadMaterial())
        //    return false;
        assert(_material);

        _graphicsObject = new MeshMaterialGraphicsObject(_mesh, _material, _createFactory);
        for (auto provider : providers)
            _graphicsObject->AddPropertyProvider(provider);
        gameObject()->AddComponent(_graphicsObject);
        return true;
    }

    //bool ObjLoader::Load(std::string filename, ObjGraphicsObject *out)
    //{
    //    //TODO: cache mesh data
    //    std::ifstream in;
    //    in.open(filename);
    //    if (!in)
    //        return false;
    //    if (!Load(in, out))
    //        return false;
    //    in.close();
    //    return true;
    //}
    //bool ObjLoader::Load(std::istream &in, ObjGraphicsObject *out)
    //{
    //    ObjLoader loader;
    //    return loader._Load(in, out);
    //}

    bool ObjLoader::_LoadMesh()
    {
        assert(this_thread_type() == ThreadType::ResourceLoader);
        std::string line;
        while (std::getline(*stream, line))
        {
            std::istringstream iss(line);

            std::string first;
            iss >> first;
            if (first == "p")
            {
            }
            else if (first == "v")
            {
                float x, y, z;
                iss >> x >> y >> z;
                positions.push_back({ x, y, z });
            }
            else if (first == "vt")
            {
                float u, v;
                iss >> u >> v;
                texCoords.push_back({ u, v });
            }
            else if (first == "vn")
            {
                float nx, ny, nz;
                iss >> nx >> ny >> nz;
                normals.push_back({ nx, ny ,nz });
            }
            else if (first == "f")
            {
                std::string s0, s1, s2, s3;
                iss >> s0 >> s1 >> s2;
                if (!(iss >> s3))
                {
                    triangleIndices->push_back({
                        ParseVertex(s0),
                        ParseVertex(s1),
                        ParseVertex(s2)
                    });
                }
                else
                {
                    quadIndices->push_back({
                        ParseVertex(s0),
                        ParseVertex(s1),
                        ParseVertex(s2),
                        ParseVertex(s3)
                    });
                }
            }
        }
        return CreateMeshFromData();
    }

    bool ObjLoader::CreateMeshFromData()
    {
        _mesh = new MeshComponent(glPositions, triangleIndices, quadIndices, glTexCoords, glNormals);
        gameObject()->AddComponent(_mesh);

        //for (auto vertex : glVertices)
        //{
        //    Vector<3> position; Vector<2> texCoord; Vector<3> normal;
        //    std::tie(position, texCoord, normal) = vertex;
        //    out->AddVertex(position, texCoord, normal);
        //}

        ////TODO: dynamically choose VboType based on size
        //for (unsigned i = 0; i < triangleIndices.size(); i += 3)
        //{
        //    out->AddTriangle({ triangleIndices[i + 2], triangleIndices[i + 1], triangleIndices[i] });
        //}
        //for (unsigned i = 0; i < quadIndices.size(); i += 4)
        //{
        //    out->AddTriangle({ quadIndices[i + 2], quadIndices[i + 1], quadIndices[i] });
        //    out->AddTriangle({ quadIndices[i], quadIndices[i + 3], quadIndices[i + 2] });
        //}

        return true;
    }

    int ObjLoader::ParseVertex(std::string faceString)
    {
        Vector<3> position;
        Vector<2> texCoord;
        Vector<3> normal;

        std::string current;
        int idx = 0;
        for (unsigned i = 0; i <= faceString.length(); i++)
        {
            if (faceString[i] == '/' || i == faceString.length())
            {
                if (current.empty())
                {
                    idx++;
                    continue;
                }

                switch (idx)
                {
                case 0:
                    int positionIndex;
                    if (!Util::stoi(current.c_str(), positionIndex))
                        positionIndex = 0;
                    positionIndex += positionIndex < 0 ? positions.size() : -1;
                    position = positions[positionIndex];
                    break;
                case 1:
                    int texCoordIndex;
                    if (!Util::stoi(current.c_str(), texCoordIndex))
                        texCoordIndex = 0;
                    texCoordIndex += texCoordIndex < 0 ? texCoords.size() : -1;
                    texCoord = texCoords[texCoordIndex];
                    break;
                case 2:
                    int normalIndex;
                    if (!Util::stoi(current.c_str(), normalIndex))
                        normalIndex = 0;
                    normalIndex += normalIndex < 0 ? normals.size() : -1;
                    normal = normals[normalIndex];
                    break;
                }
                current = "";
                idx++;
            }
            else
                current += faceString[i];
        }

        glPositions->push_back(position);
        glTexCoords->push_back(texCoord);
        glNormals->push_back(normal);
        return glPositions->size() - 1;

        //return FindOrAddGlVertex(position, texCoord, normal);
    }

    //int ObjLoader::FindOrAddGlVertex(Vector<3> vertex, Vector<2> texCoord, Vector<3> normal)
    //{
    //    std::tuple<Vector<3>, Vector<2>, Vector<3>> glVertex(vertex, texCoord, normal);
    //    
    //    glVertices.push_back(glVertex);
    //    return glVertices.size() - 1;
    //}
}
