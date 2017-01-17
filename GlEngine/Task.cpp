#include "stdafx.h"
#include "Task.h"
#include "IGraphicsComponent.h"

namespace GlEngine
{
    Task::Task(TaskType type, IComponent *c, TaskState state)
        : type(type), _c(c), state(state)
    {
    }
    Task::~Task()
    {
    }

    IComponent &Task::component()
    {
        return *_c;
    }
    IGraphicsComponent &Task::graphicsComponent()
    {
        return *dynamic_cast<IGraphicsComponent*>(_c);
    }
}
