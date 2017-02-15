#include "stdafx.h"
#include "Subroutine.h"

namespace GlEngine::ShaderFactory
{
    Subroutine::Subroutine(std::string name)
        : _name(name)
    {
    }
    Subroutine::~Subroutine()
    {
    }

    unsigned Subroutine::glslSubroutineLocation()
    {
        return gl_index;
    }

    std::string Subroutine::name()
    {
        return _name;
    }

    void Subroutine::Push(unsigned idx)
    {
        this->gl_index = idx;
    }
    void Subroutine::Pop()
    {
    }
}
