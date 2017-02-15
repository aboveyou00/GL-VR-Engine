#pragma once

namespace GlEngine::ShaderFactory
{
    class ENGINE_SHARED Subroutine
    {
    public:
        Subroutine(std::string name);
        ~Subroutine();

        unsigned glslSubroutineLocation();

        std::string name();

        void Push(unsigned idx);
        void Pop();

    protected:
        unsigned gl_index;

    private:
        bool initialized;
        std::string _name;
    };
}
