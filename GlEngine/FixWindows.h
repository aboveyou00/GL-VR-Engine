#pragma once

//The entire purpose of this file is to get rid of ridiculus preprocessing directives that only serve to make life hard for everyone.
//There are better alternatives to creating macros for every little thing. Use those instead!

#ifdef min
#undef min
#endif

#ifdef max
#undef max
#endif
