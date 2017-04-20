#include "stdafx.h"
#include "Engine.h"

#include "Lab01_Diffuse/DiffuseSceneFrame.h"
#include "Lab02_Features/FeaturesSceneFrame.h"
#include "Lab03_LightsAndEffects/LightsAndEffectsSceneFrame.h"
#include "Lab04_Textures/TexturesSceneFrame.h"
#include "Lab05_Geometry/GeometrySceneFrame.h"
#include "Lab06_Distortion/DistortionSceneFrame.h"
#include "Lab07_Particles/ParticlesSceneFrame.h"
#include "Lab08_Slenderman/SlendermanSceneFrame.h"
#include "Lab08_Slenderman/SlendermanStaticSceneFrame.h"
#include "Lab09_Spatpart/SpatpartSceneFrame.h"

int main(int, char**)
{
    return THIS_ENGINE.QuickLaunchFrame<SpatpartSceneFrame>(
        "Sandbox"s,     //Name of game
        "sandbox.log"s, //Name of log file
        "sandbox.cfg"s, //Name of config file
        200u            //Target frame rate
    );
}
