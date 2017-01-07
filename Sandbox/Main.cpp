#include "stdafx.h"
#include "Sandbox.h"

#include "Program.h"
#include "Attribute.h"
#include "VboPropertySource.h"
#include "UniformPropertySource.h"

using namespace GlEngine::ShaderFactory;

int main(int argc, char **argv)
{
    argc; argv;
    //TODO: Parse arguments

    //this_thread_name() = "main";

    //Sandbox sandbox;

    //if (!sandbox.Initialize()) return -1;
    //sandbox.MessageLoop();
    //sandbox.Shutdown();
    //return 0;

    auto prog = Program(false, false);

    prog.AddPropertySource(new VboPropertySource(&prop_Position, &prop_UV, &prop_Normal));

    prog.AddPropertySource(new UniformPropertySource(&prop_ModelViewProjectionMatrix));
    prog.AddPropertySource(new UniformPropertySource(&prop_DiffuseLightDirection));
    prog.AddPropertySource(new UniformPropertySource(&prop_DiffuseLightColor));

    prog.AddAttribute(&attr_GlPosition);
    prog.AddAttribute(&attr_DiffuseLight);

    prog.Compile();

    prog.WriteToDisk("diffuse");

    return 0;
}
