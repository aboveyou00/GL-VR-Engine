#include "stdafx.h"
#include "Sandbox.h"

#include "Program.h"
#include "Attribute.h"
#include "VboPropertySource.h"
#include "UniformPropertySource.h"

using namespace GlEngine::ShaderFactory;

int main(int, char**)
{
    this_thread_name() = "main";
    this_thread_type() = ThreadType::WndProc;

    Sandbox sandbox;

    if (!sandbox.Initialize()) return -1;
    sandbox.MessageLoop();
    sandbox.Shutdown();
    return 0;

}
