#pragma once

#include "EngineShared.h"

#include <SDKDDKVer.h>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <windowsx.h>

#include "FixWindows.h"

#include <iostream>
#include <fstream>

#include <chrono>
using namespace std::chrono_literals;
#include <functional>
#include <vector>
#include <assert.h>

#include "vbo_attribs_Vector.h"
#include "vbo_attribs_Matrix.h"

#include "Threading.h"
#include "Memory.h"

//#pragma warning (disable: 4239)
#pragma warning (disable: 4458) //declaration of 'x' hides class member
#pragma warning (disable: 4455)
