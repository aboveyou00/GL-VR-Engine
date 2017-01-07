#include "stdafx.h"
#include "KeyboardEvent.h"

namespace GlEngine
{
    namespace Events
    {
        KeyboardEvent::KeyboardEvent(unsigned int vkCode, KeyboardEventType type)
            : _vkCode(vkCode), _type(type)
        {
        }
        KeyboardEvent::~KeyboardEvent()
        {
        }

        unsigned int KeyboardEvent::GetVirtualKeyCode() const
        {
            return _vkCode;
        }
        KeyboardEventType KeyboardEvent::GetEventType() const
        {
            return _type;
        }
        bool KeyboardEvent::IsPressed() const
        {
            return _type == KeyboardEventType::KeyPressed;
        }
        bool KeyboardEvent::IsReleased() const
        {
            return _type == KeyboardEventType::KeyReleased;
        }
        bool KeyboardEvent::IsTyped() const
        {
            return _type == KeyboardEventType::KeyTyped;
        }

        std::ostream &KeyboardEvent::stringify(std::ostream &stream) const
        {
            return stream << _type << ": " << _vkCode;
        }
    }
}
