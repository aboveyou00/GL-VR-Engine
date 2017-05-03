#include "stdafx.h"
#include "PathingNodesController.h"
#include <sstream>
#include "GameObject.h"
#include "PathingNodeObject.h"
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

PathingNodesController::PathingNodesController(std::vector<GlEngine::ShaderFactory::IPropertyProvider*> providers, bool editing, GlEngine::CameraComponent *camera)
    : GlEngine::GameComponent("EditorControllerComponent"), editing(editing), _providers(providers), _camera(camera)
{
    assert(!editing || camera != nullptr);
}
PathingNodesController::~PathingNodesController()
{
}

bool PathingNodesController::InitializeAsync()
{
    if (!GlEngine::GameComponent::InitializeAsync()) return false;

    if (!ExecuteFile("ai-pathing.nodemap"s)) return false;
    _selected = false;

    return true;
}
void PathingNodesController::ShutdownAsync()
{
    if (editing) SaveFile("ai-pathing.nodemap"s);
}

void PathingNodesController::HandleEvent(GlEngine::Events::Event &evt)
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
            Vector<3> translateAmt = {};
            if (kbEvt->GetVirtualKeyCode() == VK_UP)
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
            else if (kbEvt->GetVirtualKeyCode() == VK_DELETE && _selected != nullptr)
            {
                deleteObject(_selected);
            }
            if (_selected != nullptr && translateAmt.LengthSquared() != 0)
            {
                //auto mesh = _selected->gameObject()->component<GlEngine::MeshComponent>();
                //frame()->spatialPartitions->RemoveStaticMesh(mesh);
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
            float distance;
            auto ray = _camera->centerRay();
            auto result = frame()->spatialPartitions->RayCast(ray, &distance);
            if (result != nullptr)
            {
                auto gobj = result->gameObject();
                auto pno = gobj == nullptr ? nullptr : gobj->component<PathingNodeObject>();
                if (mouseEvt->button() == GlEngine::Events::MouseButton::Left)
                {
                    if (pno != nullptr) _selected = pno;
                    else createObject(ray.origin + (ray.direction * distance));
                }
                else if (mouseEvt->button() == GlEngine::Events::MouseButton::Right)
                {
                    if (pno != nullptr)
                    {
                        //...
                    }
                }
            }
            mouseEvt->Handle();
        }
    }
    if (!evt.IsHandled()) GameComponent::HandleEvent(evt);
}

bool PathingNodesController::ExecuteFile(std::string path)
{
    std::ifstream in;
    in.open(path);
    if (!in) return true; //Could not find file; ignore. We'll save it out when we're done
    auto worked = ExecuteStream(in);
    in.close();
    return worked;
}
bool PathingNodesController::ExecuteStream(std::istream &stream)
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

bool PathingNodesController::ExecuteCommand(std::string &command, std::string &line, std::istringstream &stream)
{
    if (command.length() == 0 || command[0] == '#')
    {
        //This is a comment. Ignore
    }
    else if (command == "node")
    {
        unsigned idx;
        float x, y, z;
        stream >> idx >> x >> y >> z;
        createObject(idx, { x, y, z });
    }
    else if (command == "connect")
    {
        unsigned idx1, idx2;
        stream >> idx1 >> idx2;
        connectObjects(idx1, idx2);
    }
    else if (command == "disconnect")
    {
        unsigned idx1, idx2;
        stream >> idx1 >> idx2;
        disconnectObjects(idx1, idx2);
    }
    //else if (command == "autoconnect") //This doesn't work because of the lazy loader
    //{
    //    unsigned idx1;
    //    stream >> idx1;
    //    autoconnectObject(idx1);
    //}
    else if (_selected == nullptr)
    {
        GlEngine::Util::Log(GlEngine::LogType::ErrorC, "The EditorControllerComponent can't set object properties until one is created using newmtl. [%s]", line.c_str());
        return false;
    }
    else
    {
        GlEngine::Util::Log(GlEngine::LogType::ErrorC, "The PathingNodesController doesn't know how to handle command [%s]", line.c_str());
        return false;
    }
    return true;
}

PathingNodeObject *PathingNodesController::createObject(Vector<3> pos)
{
    unsigned idx = 0;
    PathingNodeMap::iterator it;
    while (_objects.find(idx) != _objects.end()) idx++;
    auto pno = createObject(idx, pos);
    autoconnectObject(idx);
    return pno;
}
PathingNodeObject *PathingNodesController::createObject(unsigned idx, Vector<3> pos)
{
    assert(_objects.find(idx) == _objects.end());

    auto gobj = new GlEngine::GameObject(this->frame(), "PathingNodesObject_Object");
    auto pno = new PathingNodeObject(idx, _providers);
    gobj->AddComponent(pno);
    this->_selected = pno;
    this->_objects[idx] = pno;
    gobj->globalTransform()->SetPosition(pos);

    return pno;
}
void PathingNodesController::autoconnectObject(unsigned idx1)
{
    auto pno1 = _objects.find(idx1);
    assert(pno1 != _objects.end());

    //...
}
void PathingNodesController::connectObjects(unsigned idx1, unsigned idx2)
{
    auto pno1 = _objects.find(idx1);
    auto pno2 = _objects.find(idx2);
    assert(pno1 != _objects.end());
    assert(pno2 != _objects.end());

    pno1->second->connections().push_back(pno2->second);
}
void PathingNodesController::disconnectObjects(unsigned idx1, unsigned idx2)
{
    auto pno1 = _objects.find(idx1);
    auto pno2 = _objects.find(idx2);
    assert(pno1 != _objects.end());
    assert(pno2 != _objects.end());

    collection_remove(pno1->second->connections(), pno2->second);
}
void PathingNodesController::deleteObject(PathingNodeObject *obj)
{
    obj->gameObject()->Deactivate();
    _objects.erase(obj->idx());
    for (auto it = _objects.begin(); it != _objects.end(); it++)
    {
        collection_remove(it->second->connections(), obj);
    }
    if (_selected == obj) _selected = nullptr;
}

void PathingNodesController::SaveFile(std::string path)
{
    std::ofstream out;
    out.open(path);
    if (!out) return;
    SaveStream(out);
    out.close();
}
void PathingNodesController::SaveStream(std::ostream &stream)
{
    stream << std::endl;
    stream << std::endl;

    for (auto it = _objects.begin(); it != _objects.end(); it++)
    {
        auto &obj = *it->second;
        auto transform = obj.gameObject()->globalTransform();
        auto pos = transform->position();
        stream << "node " << obj.idx() << " " << pos[0] << " " << pos[1] << " " << pos[2] << std::endl;
    }

    for (auto it = _objects.begin(); it != _objects.end(); it++)
    {
        stream << std::endl;
        auto &obj = *it->second;
        auto conns = obj.connections();
        for (auto connit = conns.begin(); connit != conns.end(); connit++)
        {
            auto &conn = **connit;
            stream << "connect " << obj.idx() << " " << conn.idx() << std::endl;
        }
    }
}
