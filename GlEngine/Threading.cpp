#include "stdafx.h"

const char *&this_thread_name()
{
    static thread_local const char *ttn;
    return ttn;
}
