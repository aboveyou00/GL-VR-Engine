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
#include <assert.h>

#include "Threading.h"
#include "Memory.h"

#pragma warning (disable: 4239)
