#include "stdafx.h"

#include "TileRPGGame.h"

int main(int argc, char **argv)
{
    argc; argv;
    //TODO: Parse arguments

    TileRPG::TileRPGGame game;
    
    if (!game.Initialize()) return -1;
    game.MessageLoop();
    game.Shutdown();
    return 0;
}
