#include "stdafx.h"
#include "Task.h"

namespace GlEngine
{
    Task::Task(TaskType type, IAsyncInitializable *c, TaskState state)
        : type(type), _c(c), state(state)
    {
    }
    Task::~Task()
    {
    }

    IAsyncInitializable &Task::component()
    {
        return *_c;
    }
}
