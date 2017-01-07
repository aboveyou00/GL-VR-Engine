#include "stdafx.h"
#include "Sandbox.h"

#include "Program.h"
#include "Attribute.h"
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

    auto modelViewProjectionSource = new UniformPropertySource(&prop_ModelViewProjectionMatrix);
    auto positionSource = new UniformPropertySource(&prop_Position);
    auto normalSource = new UniformPropertySource(&prop_Normal);
    auto diffuseLightDirection = new UniformPropertySource(&prop_DiffuseLightDirection);
    auto diffuseLightColor = new UniformPropertySource(&prop_DiffuseLightColor);

    auto prog = Program(false, false);

    prog.AddAttribute(&attr_GlPosition);
    prog.AddAttribute(&attr_DiffuseLight);
    
    prog.AddPropertySource(modelViewProjectionSource);
    prog.AddPropertySource(positionSource);
    prog.AddPropertySource(normalSource);
    prog.AddPropertySource(diffuseLightDirection);
    prog.AddPropertySource(diffuseLightColor);

    prog.Compile(true);

    return 0;
}
