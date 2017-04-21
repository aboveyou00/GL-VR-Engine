#pragma once

#ifdef ENGINE_EXPORTS

#define ENGINE_SHARED __declspec(dllexport)
#define ADAPTER_SHARED __declspec(dllimport)

#else

#define ENGINE_SHARED __declspec(dllimport)

#ifdef ADAPTER_EXPORTS
#define ADAPTER_SHARED __declspec(dllexport)
#else
#define ADAPTER_SHARED __declspec(dllimport)
#endif

#endif

#pragma warning (disable: 4251) //Disable warnings about dll-interfaces for private members
//I will never have code where private class members will be accessed directly by users of this DLL
