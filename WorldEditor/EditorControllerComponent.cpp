#include "stdafx.h"
#include "EditorControllerComponent.h"
#include <sstream>
#include "GameObject.h"
#include "WorldEditorObject.h"
#include "PhongMaterial.h"
#include "MathUtils.h"

#include "KeyboardEvent.h"
#include "MouseEvent.h"

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

void EditorControllerComponent::HandleEvent(GlEngine::Events::Event &evt)
{
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
            Vector<3> translateAmt = { };
            if (kbEvt->GetVirtualKeyCode() == VK_ALPHANUMERIC<'R'>())
            {
                rotateAmt -= .1f * GlEngine::Util::PI_f;
            }
            else if (kbEvt->GetVirtualKeyCode() == VK_ALPHANUMERIC<'T'>())
            {
                rotateAmt += .1f * GlEngine::Util::PI_f;
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
            if (_selected != nullptr)
            {
                if (rotateAmt != 0) _selected->gameObject()->globalTransform()->RotateY(rotateAmt);
                if (translateAmt.LengthSquared() != 0) _selected->gameObject()->globalTransform()->Translate(translateAmt);
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
                //TODO: raycast to select object
                //auto ray = cameraComponent->rayToPoint(testPoints[q]);
                //auto result = spatialPartitions->RayCast(ray, &distance);
                //if (result != nullptr)
                //{
                //    raytraceDebugObjects[q]->Activate();
                //    raytraceDebugObjects[q]->localTransform()->SetPosition(ray.origin + distance * ray.direction);
                //}
                //else raytraceDebugObjects[q]->Deactivate();
                //hitFlag = hitFlag || (result != nullptr && result->gameObject() == flagGobj);

                //mouseEvt->Handle();
            }
        }
    }
    if (!evt.IsHandled()) GameComponent::HandleEvent(evt);
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
    gobj->globalTransform()->SetPosition(gameObject()->globalTransform()->position());
    gobj->globalTransform()->SetOrientation(gameObject()->globalTransform()->orientation());
    return weo;
}
