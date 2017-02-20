#pragma once

#include "TaskType.h"
#include "TaskState.h"

namespace GlEngine
{
    class IAsyncInitializable;

    class Task
    {
    public:
        Task(TaskType type, IAsyncInitializable *c, TaskState state = TaskState::Unassigned);
        ~Task();

        TaskType type;
        TaskState state;

        IAsyncInitializable &component();

    private:
        IAsyncInitializable *_c;
    };
}
