#include "stdafx.h"
#include "ObjLoader.h"

#include <sstream>
#include <algorithm>
#include "StringUtils.h"
#include "ObjGraphicsObject.h"
#include "VboFactory.h"
#include "GameObject.h"
#include "MeshMaterialGraphicsObject.h"
#include "PhongMaterial.h"

namespace GlEngine
{
    ObjLoader::ObjLoader(std::string filename, std::vector<ShaderFactory::IPropertyProvider*> providers, ObjLoaderFlag flags)
        : ObjLoader(filename, providers, [](Material*) { return nullptr; }, flags)
    {
    }
    ObjLoader::ObjLoader(std::string filename, std::vector<ShaderFactory::IPropertyProvider*> providers, CreateFactoryFn createFactory, ObjLoaderFlag flags)
        : GameComponent("ObjLoader"), providers(providers), _flags(flags), _filename(filename), stream(nullptr), _mesh(nullptr), _material(nullptr), _graphicsObject(nullptr), _createFactory(createFactory), materials(nullptr), faces(new MtlFacesMap())
    {
        size_t lastSepIdx = _filename.rfind("/");
        if (lastSepIdx == std::string::npos) lastSepIdx = _filename.rfind("\\");
        if (lastSepIdx != std::string::npos && lastSepIdx != 0) _basePath = _filename.substr(0, lastSepIdx);
        if (_basePath.length() > 0) _basePath += "/";

        glPositions = new std::vector<Vector<3>>();
        glNormals = new std::vector<Vector<3>>();
        glTexCoords = new std::vector<Vector<2>>();
    }
    ObjLoader::ObjLoader(std::istream& in)
        : GameComponent("ObjLoader"), _filename(""), stream(&in)
    {
        //Don't use this! If you do, initialize everything correctly first
        assert(false);
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
        //assert(_material);
        if (_material == nullptr) _material = new PhongMaterial({ 1.f, .2f, .2f }, { .4f, .4f, .4f }, 10.f);

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

    MeshFaces *ObjLoader::_getFaces(std::string name)
    {
        if (materials == nullptr) return _getFaces(nullptr);
        auto found = materials->find(name);
        if (found != materials->end()) return _getFaces((*materials)[name]);
        return _getFaces(nullptr);
    }
    MeshFaces *ObjLoader::_getFaces(Material *mat)
    {
        auto found = faces->find(mat);
        if (found != faces->end()) return (*faces)[mat];
        return (*faces)[mat] = new MeshFaces();
    }

    bool ObjLoader::_LoadMesh()
    {
        assert(this_thread_type() == ThreadType::ResourceLoader);
        std::string line, mtllib;
        MeshFaces *currentFaces = _getFaces(nullptr);
        while (std::getline(*stream, line))
        {
            std::istringstream iss(line);

            std::string first;
            iss >> first;
            if (first.length() == 0 || first[0] == '#')
            {
                //This is a comment. Ignore
            }
            else if (first == "mtllib")
            {
                if (materials != nullptr)
                {
                    Util::Log(LogType::ErrorC, "The ObjLoader doesn't know how to load from multiple material libraries. [%s]", line.c_str());
                    continue;
                }
                if (line.length() <= 8)
                {
                    Util::Log(LogType::ErrorC, "The ObjLoader can't load from an empty material library. [%s]", line.c_str());
                    continue;
                }
                mtllib = line.substr(7);
                materials = _LoadMtllib(mtllib);
            }
            else if (first == "usemtl")
            {
                if (materials == nullptr)
                {
                    Util::Log(LogType::ErrorC, "The ObjLoader can't use a material until you have specified a material library. [%s]", line.c_str());
                    continue;
                }
                if (line.length() <= 8)
                {
                    Util::Log(LogType::ErrorC, "The ObjLoader can't use an empty material. [%s]", line.c_str());
                    continue;
                }
                std::string matName = line.substr(7);
                auto findMat = materials->find(matName);
                if (findMat == materials->end())
                {
                    Util::Log(LogType::ErrorC, "The ObjLoader can't use a material that isn't in the material library. [%s]", line.c_str());
                    continue;
                }
                Material *mat;
                std::tie(matName, mat) = *findMat;
                currentFaces = _getFaces(mat);
            }
            else if (first == "o" || first == "g")
            {
                //Named objects and groups are not supported.
            }
            else if (first == "s")
            {
                //Smooth shading is not supported. Just use normals, for heaven's sake!
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
                    currentFaces->triangleIndices->push_back({
                        ParseVertex(s0),
                        ParseVertex(s1),
                        ParseVertex(s2)
                    });
                }
                else
                {
                    currentFaces->quadIndices->push_back({
                        ParseVertex(s0),
                        ParseVertex(s1),
                        ParseVertex(s2),
                        ParseVertex(s3)
                    });
                }
            }
            else
            {
                //TODO: vp, p, o, g, s
                Util::Log(LogType::ErrorC, "The ObjLoader doesn't know how to handle [%s]", line.c_str());
            }
        }
        SafeDelete(materials);
        return CreateMeshFromData();
    }

    bool ObjLoader::CreateMeshFromData()
    {
        _mesh = new MeshComponent(glPositions, glTexCoords, glNormals, faces);
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

    MtlNameMap *ObjLoader::_LoadMtllib(std::string mtllib)
    {
        std::ifstream in;
        in.open(_basePath + mtllib);
        if (!in) return nullptr;
        auto map = _ParseMtllib(&in);
        in.close();
        return map;
    }
    MtlNameMap *ObjLoader::_ParseMtllib(std::istream *stream)
    {
        auto mtls = new MtlNameMap();

        std::string line;
        MtlLibMtl *currentMtl = nullptr;
        
        while (std::getline(*stream, line))
        {
            std::istringstream iss(line);

            std::string first;
            iss >> first;
            if (first.length() == 0 || first[0] == '#')
            {
                //This is a comment. Ignore
            }
            else if (first == "newmtl")
            {
                if (currentMtl != nullptr)
                {
                    (*mtls)[currentMtl->name] = currentMtl->CreateMaterial();
                    SafeDelete(currentMtl);
                }
                if (line.length() <= 8)
                {
                    Util::Log(LogType::ErrorC, "The ObjLoader can't create a material with no name. [%s]", line.c_str());
                    continue;
                }
                std::string name = line.substr(7);
                currentMtl = new MtlLibMtl();
                currentMtl->name = name;
            }
            else if (currentMtl == nullptr)
            {
                Util::Log(LogType::ErrorC, "The ObjLoader can't set material properties until one is created using newmtl. [%s]", line.c_str());
                continue;
            }
            else if (first == "Ka")
            {
                float r, g, b;
                iss >> r >> g >> b;
                currentMtl->ambient = { r, g, b };
            }
            else if (first == "Kd")
            {
                float r, g, b;
                iss >> r >> g >> b;
                currentMtl->diffuse = { r, g, b };
            }
            else if (first == "Ks")
            {
                float r, g, b;
                iss >> r >> g >> b;
                currentMtl->specular = { r, g, b };
            }
            else if (first == "Ns")
            {
                float specExp;
                iss >> specExp;
                currentMtl->specularExponent = specExp;
            }
            else if (first == "d")
            {
                float opacity;
                iss >> opacity;
                currentMtl->opacity = opacity;
            }
            else if (first == "Tr")
            {
                float nopacity;
                iss >> nopacity;
                currentMtl->opacity = 1 - nopacity;
            }
            else if (first == "illum")
            {
                unsigned illumMode;
                iss >> illumMode;
                currentMtl->illum = illumMode;
            }
            else if (first == "map_Ka" && line.length() >= 8)
            {
                currentMtl->ambientMap = _basePath + line.substr(7);
            }
            else if (first == "map_Kd" && line.length() >= 8)
            {
                currentMtl->diffuseMap = _basePath + line.substr(7);
            }
            else if (first == "map_Ks" && line.length() >= 8)
            {
                currentMtl->specularMap = _basePath + line.substr(7);
            }
            else if (first == "map_Ns" && line.length() >= 8)
            {
                currentMtl->specularExponentMap = _basePath + line.substr(7);
            }
            else if (first == "map_d" && line.length() >= 7)
            {
                currentMtl->alphaMap = _basePath + line.substr(6);
            }
            else if (first == "map_bump" && line.length() >= 10)
            {
                currentMtl->bumpMap = _basePath + line.substr(9);
            }
            else if (first == "bump" && line.length() >= 6)
            {
                currentMtl->bumpMap = _basePath + line.substr(5);
            }
            else if (first == "disp" && line.length() >= 6)
            {
                currentMtl->displacementMap = _basePath + line.substr(5);
            }
            else if (first == "decal" && line.length() >= 7)
            {
                currentMtl->decal = _basePath + line.substr(6);
            }
            else
            {
                //TODO: map_Ns map_d map_bump bump disp decal refl sharpness d Tf
                Util::Log(LogType::ErrorC, "The ObjLoader doesn't know how to handle material property [%s]", line.c_str());
            }
        }
        if (currentMtl != nullptr)
        {
            (*mtls)[currentMtl->name] = currentMtl->CreateMaterial();
            SafeDelete(currentMtl);
        }

        return mtls;
    }
}
