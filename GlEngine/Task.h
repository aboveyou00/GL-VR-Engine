#pragma once

#include "TaskType.h"
#include "TaskState.h"

namespace GlEngine
{
    class IComponent;
    class IGraphicsComponent;

    class Task
    {
    public:
        Task(TaskType type, IComponent *c, TaskState state = TaskState::Unassigned);
        ~Task();

        TaskType type;
        TaskState state;

        IComponent &component();
        IGraphicsComponent &graphicsComponent();

    private:
        IComponent *_c;
    };
}
