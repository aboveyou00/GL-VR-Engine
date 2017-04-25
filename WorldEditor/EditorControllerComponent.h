#pragma once

#include "GameComponent.h"

namespace GlEngine::ShaderFactory {
    class IPropertyProvider;
}

class WorldEditorObject;

class EditorControllerComponent : public GlEngine::GameComponent {
public:
    EditorControllerComponent(std::vector<GlEngine::ShaderFactory::IPropertyProvider*> providers);
    ~EditorControllerComponent();

    virtual bool InitializeAsync() override;

    virtual void HandleEvent(GlEngine::Events::Event &evt) override;

    bool ExecuteFile(std::string path);
    bool ExecuteStream(std::istream &stream);

    bool ExecuteCommand(std::string &command, std::string &line, std::istringstream &stream);

private:
    std::map<unsigned, bool> keysDown;
    Vector<2> mouseDelta;

    std::vector<GlEngine::ShaderFactory::IPropertyProvider*> _providers;
    std::vector<WorldEditorObject*> _objects;

    WorldEditorObject *_selected;
    WorldEditorObject *createObject(std::string &path);
};
