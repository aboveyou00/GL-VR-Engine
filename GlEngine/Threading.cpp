#include "stdafx.h"

const char *&this_thread_name()
{
    static thread_local const char *ttn = "unknown";
    return ttn;
}

ThreadType &this_thread_type()
{
    static thread_local ThreadType type = ThreadType::Unknown;
    return type;
}
