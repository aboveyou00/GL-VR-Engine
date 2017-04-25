#include "stdafx.h"
#include "EditorControllerComponent.h"
#include <sstream>
#include "GameObject.h"
#include "WorldEditorObject.h"
#include "ObjLoader.h"
#include "PhongMaterial.h"
#include "MathUtils.h"
#include "StringUtils.h"

#include "KeyboardEvent.h"
#include "MouseEvent.h"
#include "CameraComponent.h"
#include "Frame.h"
#include "Engine.h"
#include "ServiceProvider.h"
#include "IConfigProvider.h"

EditorControllerComponent::EditorControllerComponent(std::vector<GlEngine::ShaderFactory::IPropertyProvider*> providers, bool editing)
    : GlEngine::GameComponent("EditorControllerComponent"), _providers(providers), editing(editing)
{
}
EditorControllerComponent::~EditorControllerComponent()
{
}

bool EditorControllerComponent::InitializeAsync()
{
    if (!GameComponent::InitializeAsync()) return false;

    if (!ExecuteFile("save-data.scene"s)) return false;
    _selected = false;

    return true;
}
void EditorControllerComponent::ShutdownAsync()
{
    if (editing) SaveFile("save-data.scene"s);
}

void EditorControllerComponent::HandleEvent(GlEngine::Events::Event &evt)
{
    if (evt.IsHandled() || !editing) return;

    auto kbEvt = dynamic_cast<GlEngine::Events::KeyboardEvent*>(&evt);
    if (kbEvt != nullptr)
    {
        if (kbEvt->type() == GlEngine::Events::KeyboardEventType::KeyPressed)
        {
            this->keysDown[kbEvt->GetVirtualKeyCode()] = true;
        }
        if (kbEvt->type() == GlEngine::Events::KeyboardEventType::KeyReleased)
        {
            this->keysDown[kbEvt->GetVirtualKeyCode()] = false;
        }
        if (kbEvt->type() == GlEngine::Events::KeyboardEventType::KeyTyped)
        {
            float rotateAmt = 0;
            float scaleAmt = 1;
            Vector<3> translateAmt = { };
            if (kbEvt->GetVirtualKeyCode() == VK_ALPHANUMERIC<'R'>())
            {
                rotateAmt -= .1f * GlEngine::Util::PI_f;
            }
            else if (kbEvt->GetVirtualKeyCode() == VK_ALPHANUMERIC<'T'>())
            {
                rotateAmt += .1f * GlEngine::Util::PI_f;
            }
            else if (kbEvt->GetVirtualKeyCode() == VK_OEM_PLUS)
            {
                scaleAmt *= 1 / .9f;
            }
            else if (kbEvt->GetVirtualKeyCode() == VK_OEM_MINUS)
            {
                scaleAmt *= .9f;
            }
            else if (kbEvt->GetVirtualKeyCode() == VK_UP)
            {
                translateAmt += { 0, 0, 1 };
            }
            else if (kbEvt->GetVirtualKeyCode() == VK_DOWN)
            {
                translateAmt += { 0, 0, -1 };
            }
            else if (kbEvt->GetVirtualKeyCode() == VK_LEFT)
            {
                translateAmt += { -1, 0, 0 };
            }
            else if (kbEvt->GetVirtualKeyCode() == VK_RIGHT)
            {
                translateAmt += { 1, 0, 0 };
            }
            else if (kbEvt->GetVirtualKeyCode() == VK_ALPHANUMERIC<'L'>())
            {
                translateAmt += { 0, 1, 0 };
            }
            else if (kbEvt->GetVirtualKeyCode() == VK_ALPHANUMERIC<'O'>())
            {
                translateAmt += { 0, -1, 0 };
            }
            else if (kbEvt->GetVirtualKeyCode() >= VK_ALPHANUMERIC<'0'>() && kbEvt->GetVirtualKeyCode() <= VK_ALPHANUMERIC<'9'>())
            {
                auto idx = kbEvt->GetVirtualKeyCode() - VK_ALPHANUMERIC<'0'>();
                auto config = THIS_ENGINE.GetServiceProvider().GetService<GlEngine::IConfigProvider>();
                auto path = std::string(config->GetValue(("Editor.objPath."s + GlEngine::Util::itos(idx)).c_str()));
                createObject(path);
            }
            else if (kbEvt->GetVirtualKeyCode() == VK_DELETE && _selected != nullptr)
            {
                deleteObject(_selected);
            }
            if (_selected != nullptr && (rotateAmt != 0 || translateAmt.LengthSquared() != 0 || scaleAmt != 1))
            {
                //auto mesh = _selected->gameObject()->component<GlEngine::MeshComponent>();
                //frame()->spatialPartitions->RemoveStaticMesh(mesh);
                _selected->gameObject()->globalTransform()->RotateY(rotateAmt);
                _selected->gameObject()->globalTransform()->Scale(scaleAmt);
                _selected->gameObject()->globalTransform()->Translate(translateAmt);
                //frame()->spatialPartitions->AddStaticMesh(mesh);
            }
            kbEvt->Handle();
        }
    }
    auto mouseEvt = dynamic_cast<GlEngine::Events::MouseEvent*>(&evt);
    if (mouseEvt != nullptr)
    {
        if (mouseEvt->type() == GlEngine::Events::MouseEventType::Pressed)
        {
            if (mouseEvt->button() == GlEngine::Events::MouseButton::Left)
            {
                auto camera = gameObject()->component<GlEngine::CameraComponent>();
                float distance;
                auto result = frame()->spatialPartitions->RayCast(camera->centerRay(), &distance);
                if (result != nullptr)
                {
                    auto gobj = result->gameObject();
                    auto weo = gobj == nullptr ? nullptr : gobj->component<WorldEditorObject>();
                    if (weo != nullptr) _selected = weo;
                }
                mouseEvt->Handle();
            }
        }
    }
    if (!evt.IsHandled()) GameComponent::HandleEvent(evt);
}

bool EditorControllerComponent::ExecuteFile(std::string path)
{
    std::ifstream in;
    in.open(path);
    if (!in) return true; //Could not find file; ignore. We'll save it out when we're done
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
        createObject(path);
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
        _selected->gameObject()->globalTransform()->SetPosition({ x, y, z });
    }
    else if (command == "scale")
    {
        float xs, ys, zs;
        stream >> xs >> ys >> zs;
        _selected->gameObject()->globalTransform()->SetScale({ xs, ys, zs });
    }
    else if (command == "orient")
    {
        float real, i, j, k;
        stream >> real >> i >> j >> k;
        _selected->gameObject()->globalTransform()->SetOrientation({ real, i, j, k });
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
    gobj->globalTransform()->SetPosition(gameObject()->globalTransform()->position());
    gobj->globalTransform()->SetOrientation(gameObject()->globalTransform()->orientation());
    return weo;
}
void EditorControllerComponent::deleteObject(WorldEditorObject *obj)
{
    obj->gameObject()->Deactivate();
    collection_remove(_objects, obj);
    if (_selected == obj) _selected = nullptr;
}

void EditorControllerComponent::SaveFile(std::string path)
{
    std::ofstream out;
    out.open(path);
    if (!out) return;
    SaveStream(out);
    out.close();
}
void EditorControllerComponent::SaveStream(std::ostream &stream)
{
    stream << std::endl;
    stream << std::endl;

    for (auto it = _objects.begin(); it != _objects.end(); it++)
    {
        auto &obj = (*it)->objLoader();
        stream << "obj " << obj.filename() << std::endl;

        auto &mat = (*it)->mat();
        auto color = mat.color();
        auto coef = mat.reflectionCoef();
        auto shininess = mat.shininess();
        stream << "default_mat " << color[0] << " " << color[1] << " " << color[2] << " " << coef[0] << " " << coef[1] << " " << coef[2] << " " << shininess << std::endl;

        auto transform = (*it)->gameObject()->globalTransform();
        auto pos = transform->position();
        stream << "pos " << pos[0] << " " << pos[1] << " " << pos[2] << std::endl;
        auto scale = transform->scale();
        stream << "scale " << scale[0] << " " << scale[1] << " " << scale[2] << std::endl;
        auto orient = transform->orientation();
        stream << "orient " << orient.real() << " " << orient.i() << " " << orient.j() << " " << orient.k() << std::endl;

        stream << std::endl;
    }
}
