#include "stdafx.h"

std::string &this_thread_name()
{
    static thread_local std::string ttn = "unknown";
    return ttn;
}

ThreadType &this_thread_type()
{
    static thread_local ThreadType type = ThreadType::Unknown;
    return type;
}
