#include "stdafx.h"
#include "KeyboardEvent.h"

namespace GlEngine
{
    namespace Events
    {
        KeyboardEvent::KeyboardEvent(unsigned int vkCode, KeyboardEventType type, void *sender)
            : Event(sender), _vkCode(vkCode), _type(type)
        {
        }
        KeyboardEvent::~KeyboardEvent()
        {
        }

        std::ostream &KeyboardEvent::stringify(std::ostream &stream) const
        {
            stream << "TODO(Impl KeyboardEvent::stringify)";
            return stream;
        }
    }
}
