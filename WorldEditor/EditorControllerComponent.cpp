#include "stdafx.h"
#include "EditorControllerComponent.h"
#include <sstream>
#include "GameObject.h"
#include "WorldEditorObject.h"
#include "PhongMaterial.h"

EditorControllerComponent::EditorControllerComponent(std::vector<GlEngine::ShaderFactory::IPropertyProvider*> providers)
    : GlEngine::GameComponent("EditorControllerComponent"), _providers(providers)
{
}
EditorControllerComponent::~EditorControllerComponent()
{
}

bool EditorControllerComponent::InitializeAsync()
{
    if (!GameComponent::InitializeAsync()) return false;

    if (!ExecuteFile("save-data.scene"s)) return false;

    return true;
}
bool EditorControllerComponent::ExecuteFile(std::string path)
{
    std::ifstream in;
    in.open(path);
    if (!in) return false;
    auto worked = ExecuteStream(in);
    in.close();
    return worked;
}
bool EditorControllerComponent::ExecuteStream(std::istream &stream)
{
    std::string line;
    while (std::getline(stream, line))
    {
        std::istringstream iss(line);

        std::string first;
        iss >> first;
        ExecuteCommand(first, line, iss);
    }
    
    return true;
}

bool EditorControllerComponent::ExecuteCommand(std::string &command, std::string &line, std::istringstream &stream)
{
    if (command.length() == 0 || command[0] == '#')
    {
        //This is a comment. Ignore
    }
    else if (command == "obj")
    {
        if (line.length() <= 5)
        {
            GlEngine::Util::Log(GlEngine::LogType::ErrorC, "The EditorControllerComponent can't create an obj with no path. [%s]", line.c_str());
            return false;
        }
        std::string path = line.substr(4);
        auto weo = createObject(path);
        //TODO: set initial position and orientation
    }
    else if (_selected == nullptr)
    {
        GlEngine::Util::Log(GlEngine::LogType::ErrorC, "The EditorControllerComponent can't set object properties until one is created using newmtl. [%s]", line.c_str());
        return false;
    }
    else if (command == "default_mat")
    {
        float r, g, b, ir, ig, ib, se;
        stream >> r >> g >> b >> ir >> ig >> ib >> se;
        auto &phong = _selected->mat();
        phong.SetColor({ r, g, b });
        phong.SetReflectionCoef({ ir, ig, ib });
        phong.SetShininess(se);
    }
    else if (command == "pos")
    {
        float x, y, z;
        stream >> x >> y >> z;
        _selected->gameObject()->localTransform()->SetPosition({ x, y, z });
    }
    else if (command == "orient")
    {
        float real, i, j, k;
        stream >> real >> i >> j >> k;
        _selected->gameObject()->localTransform()->SetOrientation({ real, i, j, k });
    }
    else
    {
        GlEngine::Util::Log(GlEngine::LogType::ErrorC, "The EditorControllerComponent doesn't know how to handle command [%s]", line.c_str());
        return false;
    }
    return true;
}

WorldEditorObject *EditorControllerComponent::createObject(std::string &path)
{
    auto gobj = new GlEngine::GameObject(this->frame(), "WorldEditorObject_Object");
    auto weo = new WorldEditorObject(path, _providers);
    gobj->AddComponent(weo);
    this->_selected = weo;
    this->_objects.push_back(weo);
    return weo;
}
