#pragma once

#include "GameComponent.h"

namespace GlEngine {
    class ObjLoader;
    class PhongMaterial;
}

namespace GlEngine::ShaderFactory {
    class IPropertyProvider;
}

class WorldEditorObject : public GlEngine::GameComponent {
public:
    WorldEditorObject(std::string objPath, std::vector<GlEngine::ShaderFactory::IPropertyProvider*> providers);
    ~WorldEditorObject();

    virtual bool InitializeAsync() override;

    GlEngine::ObjLoader &objLoader();
    GlEngine::PhongMaterial &mat();

    virtual void GameObjectChanged() override;

private:
    GlEngine::ObjLoader *_objLoader;
    GlEngine::PhongMaterial *_mat;
};
