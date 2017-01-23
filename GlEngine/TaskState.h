#pragma once

namespace GlEngine
{
    enum class TaskState : unsigned
    {
        Unassigned,
        Working,
        ThrowAway
    };
}
