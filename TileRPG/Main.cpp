#include "stdafx.h"
#include "TileRPGGame.h"

int main(int argc, char **argv)
{
    argc; argv;
    //TODO: Parse arguments

    this_thread_name() = "main";
    this_thread_type() = ThreadType::WndProc;

    TileRPG::TileRPGGame game;

    if (!game.Initialize()) return -1;
    game.MessageLoop();
    game.Shutdown();    
}

//#include "CfbFile.h"
//
//int main()
//{
//    const char *file_path = "test_cfb.cfb";
//
//
//}
