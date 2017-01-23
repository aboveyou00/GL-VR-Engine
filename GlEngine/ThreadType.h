#pragma once

enum class ThreadType : unsigned
{
    Unknown = 0,
    Graphics = 1,
    Logic = 2,
    ResourceLoader = 3,
    WndProc = 4
};
