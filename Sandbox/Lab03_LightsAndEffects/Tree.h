#pragma once

namespace GlEngine
{
    class GameObject;
    class Frame;
}

namespace GlEngine::ShaderFactory
{
    class IPropertyProvider;
}

class Tree
{
private:
    Tree();
    ~Tree();

public:
    GlEngine::GameObject *Create(GlEngine::Frame *frame, std::string name, std::vector<GlEngine::ShaderFactory::IPropertyProvider*> providers);
};
