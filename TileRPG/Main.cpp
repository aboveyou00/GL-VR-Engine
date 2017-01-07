#include "stdafx.h"
#include "TileRPGGame.h"

#include "Program.h"
#include "Attribute.h"
#include "UniformPropertySource.h"

using namespace GlEngine::ShaderFactory;

int main(int argc, char **argv)
{
    argc; argv;
    //TODO: Parse arguments

    //this_thread_name() = "main";

    //TileRPG::TileRPGGame game;

    //if (!game.Initialize()) return -1;
    //game.MessageLoop();
    //game.Shutdown();
    
    auto modelViewSource = new UniformPropertySource(&prop_ModelViewMatrix);
    auto positionSource = new UniformPropertySource(&prop_Position);

    auto prog = Program(false, false);
    prog.AddAttribute(&attr_GlPosition);
    prog.AddPropertySource(modelViewSource);
    prog.AddPropertySource(positionSource);

    prog.Compile(true);

    return 0;
}

//#include "CfbFile.h"
//
//int main()
//{
//    const char *file_path = "test_cfb.cfb";
//
//
//}
