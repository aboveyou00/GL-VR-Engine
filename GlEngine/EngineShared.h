#ifndef EXPORTHEADER_H
#define EXPORTHEADER_H
#pragma once

#ifdef ENGINE_EXPORTS
#define ENGINE_SHARED __declspec( dllexport )
#define ENGINE_TEMPLATE
#else
#define ENGINE_SHARED __declspec( dllimport )
#define ENGINE_TEMPLATE extern
#endif

#pragma warning (disable: 4251) //Disable warnings about dll-interfaces for private members
//I will never have code where private class members will be accessed directly by users of this DLL

#endif // EXPORTHEADER_H
