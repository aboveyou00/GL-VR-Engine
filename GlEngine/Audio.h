#pragma once

#pragma push_macro("CALLBACK")
#undef CALLBACK //This is defined in some Windows and OpenGL contexts, but it breaks yse.hpp

#pragma warning(push)
#pragma warning(disable: 4458)
#pragma warning(disable: 4267)
#include "yse.hpp"
#pragma warning(pop)

#pragma pop_macro("CALLBACK")
