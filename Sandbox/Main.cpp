#include "stdafx.h"
#include "Sandbox.h"

int main(int argc, char **argv)
{
    argc; argv;
    //TODO: Parse arguments

    this_thread_name() = "main";

    Sandbox sandbox;

    if (!sandbox.Initialize()) return -1;
    sandbox.MessageLoop();
    sandbox.Shutdown();
    return 0;
}
