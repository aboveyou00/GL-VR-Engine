#include "stdafx.h"
#include "PathingNodesController.h"
#include <sstream>
#include "GameObject.h"
#include "PathingNodeObject.h"
#include "ObjLoader.h"
#include "PhongMaterial.h"
#include "MathUtils.h"
#include "StringUtils.h"
#include "PathingNodesGraphicsObject.h"

#include "KeyboardEvent.h"
#include "MouseEvent.h"
#include "CameraComponent.h"
#include "Frame.h"
#include "Engine.h"
#include "ServiceProvider.h"
#include "IConfigProvider.h"

PathingNodesController::PathingNodesController(std::vector<GlEngine::ShaderFactory::IPropertyProvider*> providers, bool editing, GlEngine::CameraComponent *camera)
    : GlEngine::GameComponent("EditorControllerComponent"),
      editing(editing),
      _providers(providers),
      _camera(camera),
      _selected(nullptr),
      _currentSelection(nullptr),
      _hoverSelection(nullptr),
      _currentGfx(nullptr)
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
    queueUpdate();

    return true;
}
void PathingNodesController::ShutdownAsync()
{
    if (editing) SaveFile("ai-pathing.nodemap"s);
}

void PathingNodesController::Tick(float delta)
{
    GlEngine::GameComponent::Tick(delta);

    float distance;
    auto ray = _camera->centerRay();
    auto result = frame()->spatialPartitions->RayCast(ray, &distance);
    PathingNodeObject *pno = nullptr;
    if (result != nullptr)
    {
        auto gobj = result->gameObject();
        pno = gobj == nullptr ? nullptr : gobj->component<PathingNodeObject>();
    }

    if (isUpdateQueued)
    {
        isUpdateQueued = false;
        if (_currentGfx != nullptr) _currentGfx->Deactivate();
        _currentGfx = new PathingNodesGraphicsObject(_objects);
        gameObject()->AddComponent(_currentGfx);
    }

    if (_currentSelection != nullptr)
    {
        if (_selected != nullptr)
        {
            _currentSelection->gameObject()->SetParent(_selected->gameObject());
            _currentSelection->Activate();
        }
        else _currentSelection->Deactivate();

        if (pno != _selected || pno == nullptr)
        {
            if (pno != nullptr)
            {
                _hoverSelection->gameObject()->SetParent(pno->gameObject());
                _hoverSelection->gameObject()->localTransform()->SetPosition({ 0, 0, 0 });
                _hoverSelection->Activate();
            }
            else if (result != nullptr)
            {
                _hoverSelection->gameObject()->SetParent(nullptr);
                _hoverSelection->gameObject()->globalTransform()->SetPosition(ray.origin + (ray.direction * distance));
                _hoverSelection->Activate();
            }
            else _hoverSelection->Deactivate();
        }
        else _hoverSelection->Deactivate();
    }
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
                queueUpdate();
            }
            if (_selected != nullptr && translateAmt.LengthSquared() != 0)
            {
                //auto mesh = _selected->gameObject()->component<GlEngine::MeshComponent>();
                //frame()->spatialPartitions->RemoveStaticMesh(mesh);
                _selected->gameObject()->globalTransform()->Translate(translateAmt);
                //frame()->spatialPartitions->AddStaticMesh(mesh);
                queueUpdate();
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
                    if (_selected != nullptr && _selected != pno && pno != nullptr)
                    {
                        if (!collection_remove(_selected->connections(), pno)) _selected->connections().push_back(pno);
                        queueUpdate();
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

void PathingNodesController::GameObjectChanged()
{
    if (gameObject() != nullptr && (_currentSelection == nullptr))
    {
        _currentSelection = new NodeSelectionGraphicsObject({ 1, 0, 0, 1 });
        _hoverSelection = new NodeSelectionGraphicsObject({ 1, .5f, .5f, .5f });
        (new GlEngine::GameObject(frame(), "CurrentNodeSelectionObject"))->AddComponent(_currentSelection);
        (new GlEngine::GameObject(frame(), "HoverNodeSelectionObject"))->AddComponent(_hoverSelection);
    }
}

PathingNodeObject *PathingNodesController::createObject(Vector<3> pos)
{
    unsigned idx = 0;
    PathingNodeMap::iterator it;
    while (_objects.find(idx) != _objects.end()) idx++;
    auto pno = createObject(idx, pos);
    autoconnectObject(idx, true);
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
void PathingNodesController::autoconnectObject(unsigned idx1, bool update)
{
    auto pnoIt = _objects.find(idx1);
    assert(pnoIt != _objects.end());
    auto pno = pnoIt->second;
    auto radius = 1.f;

    bool addedConnections = false;
    auto autoconnectOffset = Vector<3> { 0, 1.2f, 0 };

    for (auto it = _objects.begin(); it != _objects.end(); it++)
    {
        auto checkPno = it->second;
        if (checkPno == pno) continue;

        auto center = pno->gameObject()->globalTransform()->position() + autoconnectOffset;
        auto otherCenter = checkPno->gameObject()->globalTransform()->position() + autoconnectOffset;
        auto forwardUnnormalized = otherCenter - center;
        auto dist = forwardUnnormalized.Length();
        auto forward = forwardUnnormalized.Normalized();
        auto up = Vector<3> { 0, 1, 0 };
        auto side = forward.Cross(up);

        float distance;
        GlEngine::MeshComponent *result;

        result = frame()->spatialPartitions->RayCast({ center + side * radius, forward }, &distance);
        if (result && distance < dist - 1.f) continue;
        result = frame()->spatialPartitions->RayCast({ center - side * radius, forward }, &distance);
        if (result && distance < dist - 1.f) continue;
        result = frame()->spatialPartitions->RayCast({ center, forward }, &distance);
        if (result && distance < dist - 1.f) continue;

        addedConnections = true;
        pno->connections().push_back(checkPno);
        checkPno->connections().push_back(pno);
    }

    if (addedConnections && update) queueUpdate();
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

void PathingNodesController::queueUpdate()
{
    if (editing) isUpdateQueued = true;
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
