#include "stdafx.h"
#include "Engine.h"
#include "WorldEditorFrame.h"
#include "../OpenGlGraphicsAdapter/OpenGlGraphicsAdapter.h"

int main()
{
    auto openGlAdapter = GlEngine::Adapters::OpenGlGraphicsAdapter::Instance();
    THIS_ENGINE.SetGraphicsAdapter(openGlAdapter);

    return THIS_ENGINE.QuickLaunchFrame<WorldEditorFrame>(
        "WorldEditor"s,      //Name of game
        "world-editor.log"s, //Name of log file
        "world-editor.cfg"s, //Name of config file
        200u                 //Target frame rate
    );
}
